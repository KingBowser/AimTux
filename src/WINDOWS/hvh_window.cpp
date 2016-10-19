#include "hvh_window.h"

HVHWindow* hvh_window = nullptr;

HVHWindow::HVHWindow (std::wstring title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_antiaim_x = new ToggleSwitch (L"x axis", LOC (10, 10), 33, &Settings::AntiAim::enabled_X);
	AddComponent (ts_antiaim_x);
	
	
	lb_antiaim_x = new ListBox<AntiAimType_X> (L"anti aim type", LOC (10, ts_antiaim_x->position.y + ts_antiaim_x->size.y + 10), 170, &Settings::AntiAim::type_X, std::vector<LB_Element>
		{
			LB_Element (L"UP", STATIC_UP),
			LB_Element (L"DOWN", STATIC_DOWN)
		}
	);
	AddComponent (lb_antiaim_x);
	
	
	
	lb_antiaim_y = new ListBox<AntiAimType_Y> (L"anti aim type", LOC (lb_antiaim_x->position.x + lb_antiaim_x->size.x + 10, lb_antiaim_x->position.y), 170, &Settings::AntiAim::type_Y, std::vector<LB_Element>
		{
			LB_Element (L"SLOW SPIN", SPIN_SLOW),
			LB_Element (L"FAST SPIN", SPIN_FAST),
			LB_Element (L"JITTER", JITTER),
			LB_Element (L"SIDE", SIDE),
			LB_Element (L"BACKWARDS", BACKWARDS)
		}
	);
	AddComponent (lb_antiaim_y);
	
	ts_antiaim_y = new ToggleSwitch (L"y axis", LOC (lb_antiaim_x->position.x + lb_antiaim_x->size.x + 10, lb_antiaim_y->position.y - 45), 33, &Settings::AntiAim::enabled_Y);
	AddComponent (ts_antiaim_y);
	
	Hide ();
}
