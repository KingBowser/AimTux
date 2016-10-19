#include "aimbot_window.h"

TriggerbotWindow* triggerbot_window = nullptr;

TriggerbotWindow::TriggerbotWindow (std::wstring title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_triggerbot_enabled = new ToggleSwitch (L"triggerbot", LOC (10, 10), 33, &Settings::Triggerbot::enabled);
	AddComponent (ts_triggerbot_enabled);

	ts_delay = new ToggleSwitch (L"delay", BELOW (ts_triggerbot_enabled), 33, &Settings::Triggerbot::Delay::enabled);
	AddComponent (ts_delay);

	sl_delay = new Slider (L"", STACK (ts_delay), LOC (size.x - ts_delay->size.x - 30, 33), &Settings::Triggerbot::Delay::value, 0.0f, 1000.0f);
	AddComponent (sl_delay);

	ba_filter = new Banner (L"Filter", BELOW (ts_delay), size.x - 20);
	AddComponent (ba_filter);

	ts_friendly = new ToggleSwitch (L"friendly", BELOW (ba_filter), 33, &Settings::Triggerbot::Filter::friendly);
	AddComponent (ts_friendly);

	ts_head = new ToggleSwitch (L"head", BELOW (ts_friendly), 33, &Settings::Triggerbot::Filter::head);
	AddComponent (ts_head);

	ts_chest = new ToggleSwitch (L"chest", BELOW (ts_head), 33, &Settings::Triggerbot::Filter::chest);
	AddComponent (ts_chest);

	ts_arms = new ToggleSwitch (L"arms", BELOW (ts_chest), 33, &Settings::Triggerbot::Filter::arms);
	AddComponent (ts_arms);

	ts_legs = new ToggleSwitch (L"legs", BELOW (ts_arms), 33, &Settings::Triggerbot::Filter::legs);
	AddComponent (ts_legs);

	Hide ();
}
