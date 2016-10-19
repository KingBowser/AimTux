#include "esp_window.h"

ESPWindow* esp_window = nullptr;

ESPWindow::ESPWindow (std::wstring title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_esp_enabled = new ToggleSwitch (L"esp", LOC (10, 10), 33, &Settings::ESP::enabled);
	AddComponent (ts_esp_enabled);
	
	ba_player_info = new Banner (L"Player Visuals", BELOW (ts_esp_enabled), size.x - 20);
	AddComponent (ba_player_info);
	
	ts_walls = new ToggleSwitch (L"walls", BELOW (ba_player_info), 33, &Settings::ESP::Walls::enabled);
	AddComponent (ts_walls);
	
	ts_tracer = new ToggleSwitch (L"tracer", BELOW (ts_walls), 33, &Settings::ESP::Tracer::enabled);
	AddComponent (ts_tracer);
	
	ts_name = new ToggleSwitch (L"show name", BELOW (ts_tracer), 33, &Settings::ESP::Info::showName);
	AddComponent (ts_name);
	
	ts_health = new ToggleSwitch (L"show health", BELOW (ts_name), 33, &Settings::ESP::Info::showHealth);
	AddComponent (ts_health);
	
	ts_bones = new ToggleSwitch (L"show bones", BELOW (ts_health), 33, &Settings::ESP::Bones::enabled);
	AddComponent (ts_bones);
	
	ts_visibility_check = new ToggleSwitch (L"visibility check", BELOW (ts_bones), 33, &Settings::ESP::visibility_check);
	AddComponent (ts_visibility_check);
	
	ba_chams = new Banner (L"Chams", BELOW (ts_visibility_check), size.x - 20);
	AddComponent (ba_chams);
	
	ts_chams_players = new ToggleSwitch (L"players", BELOW (ba_chams), 33, &Settings::ESP::Chams::players);
	AddComponent (ts_chams_players);
	
	ts_chams_arms = new ToggleSwitch (L"arms", STACK (ts_chams_players), 33, &Settings::ESP::Chams::arms);
	AddComponent (ts_chams_arms);

	ts_rainbow_chams_hands = new ToggleSwitch (L"rainbow arms", STACK (ts_chams_arms), 33, &Settings::ESP::Chams::rainbow_arms);
	AddComponent (ts_rainbow_chams_hands);

	ts_visibility_check_chams = new ToggleSwitch (L"visibility check", STACK (ts_rainbow_chams_hands), 33, &Settings::ESP::Chams::visibility_check);
	AddComponent (ts_visibility_check_chams);
	
	ba_crosshair = new Banner (L"Crosshair", BELOW (ts_visibility_check_chams), size.x - 20);
	AddComponent (ba_crosshair);
	
	ts_recoil_crosshair = new ToggleSwitch (L"recoil crosshair", BELOW (ba_crosshair), 33, &Settings::Recoilcrosshair::enabled);
	AddComponent (ts_recoil_crosshair);
	
	ts_fov_crosshair = new ToggleSwitch (L"fov crosshair", STACK (ts_recoil_crosshair), 33, &Settings::ESP::FOVCrosshair::enabled);
	AddComponent (ts_fov_crosshair);
	
	ba_other = new Banner (L"Other", BELOW (ts_fov_crosshair), size.x - 20);
	AddComponent (ba_other);
	
	ts_bomb = new ToggleSwitch (L"bomb esp", BELOW (ba_other), 33, &Settings::ESP::Bomb::enabled);
	AddComponent (ts_bomb);

	ts_weapons = new ToggleSwitch (L"weapons esp", STACK (ts_bomb), 33, &Settings::ESP::Weapons::enabled);
	AddComponent (ts_weapons);
	
	Hide ();
}
