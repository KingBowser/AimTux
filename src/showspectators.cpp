#include "showspectators.h"

#include <locale>
#include <codecvt>

bool Settings::ShowSpectators::enabled = true;

std::list<std::wstring> GetObservervators(C_BaseEntity* pEntity)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> strconv;

	std::list<std::wstring> list; 

	for (int i = 0; i < engine->GetMaxClients(); ++i)
	{
		C_BaseEntity *entity = entitylist->GetClientEntity(i);
		if (!entity)
			continue;

		if (entity->GetLifeState() == LIFE_ALIVE || entity->GetDormant() || entity->GetHealth() > 0)
			continue;

		if (*entity->GetObserverMode() != ObserverMode_t::OBS_MODE_IN_EYE)
			continue;

		C_BaseEntity *target = entitylist->GetClientEntityFromHandle(entity->GetObserverTarget());
		if (pEntity != target)
			continue;

		IEngineClient::player_info_t entityInformation;
		engine->GetPlayerInfo(i, &entityInformation);

		if (strcmp(entityInformation.guid, "BOT") == 0)
			continue;

		list.push_back(strconv.from_bytes(entityInformation.name));
	}

	return list;
}

void ShowSpectators::PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (!Settings::ShowSpectators::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (localplayer->GetLifeState() != LIFE_ALIVE || localplayer->GetHealth() == 0)
		return;

	std::list<std::wstring> observators = GetObservervators(localplayer);
	if (observators.size() == 0)
		return;

	int index = 1;
	pstring text;
	text << "Spectators (" << observators.size() << "):";

	Draw::DrawString(text, LOC(10, 400), Color(255, 255, 255), normal_font);

	for (std::wstring name : observators)
	{
		Draw::DrawString(name.c_str(), LOC(10, 400 + 20 * index), Color(255, 255, 255), normal_font);
		index++;
	}
}
