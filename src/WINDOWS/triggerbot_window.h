#pragma once

class TriggerbotWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class TriggerbotWindow : public Window
{
private:
	ToggleSwitch* ts_triggerbot_enabled;
	ToggleSwitch* ts_delay;
	Slider*	sl_delay;
	ToggleSwitch* ts_hitchance;
	Slider*	sl_hitchance;
	Banner* ba_filter;
	ToggleSwitch* ts_friendly;
	ToggleSwitch* ts_head;
	ToggleSwitch* ts_chest;
	ToggleSwitch* ts_arms;
	ToggleSwitch* ts_legs;

public:
	TriggerbotWindow (std::wstring title, Vector2D size, Vector2D position, Color backgroundColor);
};
