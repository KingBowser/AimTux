#include "misc_window.h"

MiscWindow* misc_window = nullptr;

MiscWindow::MiscWindow (std::wstring title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_bhop = new ToggleSwitch (L"bhop", LOC (10, 10), 33, &Settings::BHop::enabled);
	AddComponent (ts_bhop);
	
	ts_autostrafe = new ToggleSwitch (L"auto strafe", BELOW (ts_bhop), 33, &Settings::AutoStrafe::enabled);
	AddComponent (ts_autostrafe);
	
	ts_spammer = new ToggleSwitch (L"chat spammer", BELOW (ts_autostrafe), 33, &Settings::Spammer::NormalSpammer::enabled);
	AddComponent (ts_spammer);
	
	ts_spammer_kill = new ToggleSwitch (L"kill spammer", STACK (ts_spammer), 33, &Settings::Spammer::KillSpammer::enabled);
	AddComponent (ts_spammer_kill);

	ts_airstuck = new ToggleSwitch (L"airstuck", BELOW (ts_spammer), 33, &Settings::Airstuck::enabled);
	AddComponent (ts_airstuck);

	ts_showranks = new ToggleSwitch (L"show ranks", BELOW (ts_airstuck), 33, &Settings::ShowRanks::enabled);
	AddComponent (ts_showranks);

	ts_showspectators = new ToggleSwitch (L"show spectators", STACK (ts_showranks), 33, &Settings::ShowSpectators::enabled);
	AddComponent (ts_showspectators);

	ts_noflash = new ToggleSwitch (L"no flash", BELOW (ts_showranks), 33, &Settings::Noflash::enabled);
	AddComponent (ts_noflash);
	
	sl_noflash_value = new Slider (L"", STACK (ts_noflash), LOC (size.x - ts_noflash->size.x - 30, 33), &Settings::Noflash::value, 0.0f, 255.0f);
	AddComponent (sl_noflash_value);

    // clantag

	ts_clantag = new ToggleSwitch (L"custom clantag", BELOW (ts_noflash), LOC (155, 30), &Settings::ClanTagChanger::enabled);
	AddComponent (ts_clantag);

	tb_clantag = new TextBox (L"clantag", &Settings::ClanTagChanger::value, STACK (ts_clantag), LOC (270, 30));
	AddComponent (tb_clantag);
	
	
	ts_clantag_animation = new ToggleSwitch (L"clantag animation", BELOW (tb_clantag), 33, &Settings::ClanTagChanger::animation);
	AddComponent (ts_clantag_animation);
	
	Hide ();
}
