#pragma once

class Window;
class TitleBar;

#include "component.h"
#include "panel.h"
#include "ui_container.h"

class Window : public Panel
{
private:
	TitleBar* titleBar;
	Panel* mainPanel;

public:
	bool draggable = true;
	std::wstring title;

	Window (std::wstring title, Vector2D size, Vector2D position, Color backgroundColor, bool draggable = true);
	Window (std::wstring title, Vector2D size, Vector2D position); 
	Window (std::wstring title, Vector2D size);
	Window (std::wstring title);
	
	
	void AddComponent (Component* component)
	{
		mainPanel->AddComponent (component);
	}
	
	void RemoveComponent (Component* component)
	{
		mainPanel->RemoveComponent (component);
	}
	
	void Toggle ()
	{
		shown = !shown;
	}
	
	void Draw ();
};

class TitleBar : public Component
{
private:
	Vector2D mouseClickStartPosition = LOC (0, 0);

public:
	bool _isDown = false;
	
	Window* parentWindow;
	
	Color foreColor = Color (255, 255, 255);
	
	void OnMouseClickStart (PositionContext mouseContext);
	void OnMouseClickEnd (PositionContext mouseContext);
	
	TitleBar (Window* window, Vector2D position)
        : Component(position)
        , parentWindow(window)
	{
	}
	
	void Draw ();
};
