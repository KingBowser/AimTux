#pragma once

class MiscWindow;

#include "../UI/stdui.h"
#include "../atgui.h"
#include "../util.h"

class MiscWindow : public Window
{
private:
	ToggleSwitch* ts_bhop;
	ToggleSwitch* ts_autostrafe;
	ToggleSwitch* ts_spammer;
	ToggleSwitch* ts_spammer_kill;
	ToggleSwitch* ts_airstuck;
	ToggleSwitch* ts_showranks;
	ToggleSwitch* ts_showspectators;
	ToggleSwitch* ts_noflash;
	Slider* sl_noflash_value;
	ToggleSwitch* ts_clantag;
	TextBox* tb_clantag;
	ToggleSwitch* ts_clantag_animation;
public:
	MiscWindow (std::wstring title, Vector2D size, Vector2D position, Color backgroundColor);
	void SetClanTag ();
};
