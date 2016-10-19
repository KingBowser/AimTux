#include "main_window.h"

MainWindow* main_window = nullptr;

MainWindow::MainWindow (std::wstring title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, false)
{
	
	int tab_height = 60;
	pl_aimbot = new Panel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_triggerbot = new Panel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_visuals = new Panel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_hvh = new Panel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_misc = new Panel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	
	std::vector<TabElement> tabs
	(
		{
			TabElement (L"Aimbot", pl_aimbot),
			TabElement (L"Triggerbot", pl_triggerbot),
			TabElement (L"Visuals", pl_visuals),
			TabElement (L"HVH", pl_hvh),
			TabElement (L"Misc", pl_misc)
		}
	);
	
	tabSelector = new TabSelector (LOC (0, 0), LOC (size.x, tab_height), tabs);
	AddComponent (tabSelector);
	
	Hide ();
}
