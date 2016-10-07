#include "hooker.h"

IBaseClientDLL* client = nullptr;
ISurface* surface = nullptr;
IVPanel* panel = nullptr;
IEngineClient* engine = nullptr;
IClientEntityList* entitylist = nullptr;
IVDebugOverlay* debugOverlay = nullptr;
IVModelInfo* modelInfo = nullptr;
IVModelRender* modelRender = nullptr;
IClientMode* clientMode = nullptr;
IEngineTrace* trace = nullptr;
IInputSystem* input = nullptr;
IMaterialSystem* material = nullptr;

VMT* panel_vmt = nullptr;
VMT* client_vmt = nullptr;
VMT* modelRender_vmt = nullptr;
VMT* clientMode_vmt = nullptr;

void Hooker::HookInterfaces()
{
	client = GetInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", CLIENT_DLL_INTERFACE_VERSION);
	engine = GetInterface<IEngineClient>("./bin/linux64/engine_client.so", VENGINE_CLIENT_INTERFACE_VERSION);
	entitylist = GetInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", VCLIENTENTITYLIST_INTERFACE_VERSION);
	surface = GetInterface<ISurface>("./bin/linux64/vguimatsurface_client.so", SURFACE_INTERFACE_VERSION);
	panel = GetInterface<IVPanel>("./bin/linux64/vgui2_client.so", PANEL_INTERFACE_VERSION);
	debugOverlay = GetInterface<IVDebugOverlay>("./bin/linux64/engine_client.so", DEBUG_OVERLAY_VERSION);
	modelInfo = GetInterface<IVModelInfo>("./bin/linux64/engine_client.so", VMODELINFO_CLIENT_INTERFACE_VERSION);
	modelRender = GetInterface<IVModelRender>("./bin/linux64/engine_client.so", VMODELRENDER_CLIENT_INTERFACE_VERSION);
	trace = GetInterface<IEngineTrace>("./bin/linux64/engine_client.so", ENGINETRACE_CLIENT_INTERFACE_VERSION);
	input = GetInterface<IInputSystem>("./bin/linux64/inputsystem_client.so", INPUTSYSTEM_CLIENT_INTERFACE_VERSION);
	material = GetInterface<IMaterialSystem>("./bin/linux64/materialsystem_client.so", MATERIALSYSTEM_CLIENT_INTERFACE_VERSION);
}

void Hooker::HookVMethods()
{
	panel_vmt = new VMT(panel);
	client_vmt = new VMT(client);
	modelRender_vmt = new VMT(modelRender);
}

uintptr_t GetClientClientAddress()
{
	uintptr_t client_client = 0;
	// enumerate through loaded shared libraries
	dl_iterate_phdr([] (struct dl_phdr_info* info, size_t size, void* data) {
		// check for 'client_client.so' in name
		if (strcasestr(info->dlpi_name, "client_client.so")) {
			// write the address and break out of the loop
			*reinterpret_cast<uintptr_t*>(data) = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
			return 1;
		}

		// haven't found it yet, keep going..
		return 0;
	}, &client_client);
	return client_client;
}

void Hooker::HookIClientMode()
{
	uintptr_t client_client = GetClientClientAddress();

	uintptr_t init_address = FindPattern(client_client, 0xFFFFFFFFF, (unsigned char*) CCSMODEMANAGER_INIT_SIGNATURE, CCSMODEMANAGER_INIT_MASK);

	if (!init_address)
		return;

	uint32_t offset = *reinterpret_cast<uint32_t*>(init_address + 3);
	clientMode = reinterpret_cast<IClientMode*>(init_address + offset + 7);
	
	clientMode_vmt = new VMT(clientMode);
}




