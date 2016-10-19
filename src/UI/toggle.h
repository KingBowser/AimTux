#pragma once

#include "component.h"
#include "button.h"
#include "../settings.h"

class ToggleSwitchBase
{ 
protected:
	Color text_color            = Color (255, 255, 255, 255);
	Color background_color      = Color (40, 40, 40, 150);

public:
    std::wstring text = L"toggle switch";
    bool* setting;

    ToggleSwitchBase(std::wstring text, bool* setting)
        : text(text)
        , setting(setting)
    {
    }

    void* Toggle()
    {
        *setting = !*setting;
    }
};


class ToggleSwitch : public ToggleSwitchBase, public Component
{
private:

	/*
     * Component Interaction CBs
     */

	bool clickStarted = false;
	void Event_OnClickStart ()
	{
		clickStarted = true;
	}
	
	void Event_OnClickEnd ()
	{
		if (clickStarted)
		{
            ToggleSwitchBase::Toggle ();
		}
	}
	
	void Event_OnMouseLeave ()
	{
		clickStarted = false;
	}

protected: 
    Color background_color_hovered = Color (160, 160, 160, 10);

public:
	
	ToggleSwitch (std::wstring text, Vector2D position, Vector2D size, bool* setting)
        : ToggleSwitchBase(text, setting)
        , Component(position, size)
	{
		this->onMouseClickEndEvent		= MFUNC (&ToggleSwitch::Event_OnClickEnd, this);
		this->onMouseClickStartEvent	= MFUNC (&ToggleSwitch::Event_OnClickStart, this);
		this->onMouseLeaveEvent			= MFUNC (&ToggleSwitch::Event_OnMouseLeave, this);
	}
	
	ToggleSwitch (std::wstring text, Vector2D position, int height, bool* setting)
		: ToggleSwitch (text, position, LOC (height + 25 + Draw::GetTextSize (text.c_str(), normal_font).x, height), setting) 
    { 
    }
	

	void Draw ()
	{
		Clear (isHovered ? background_color_hovered : background_color);
		
		int sep = size.y / 4;
		
		if (!*setting)
		{
			DrawRectangle (LOC (sep, sep), LOC ((size.y / 4) * 3, (size.y / 4) * 3), Settings::UI::mainColor);
		}
		else
		{
			DrawRectangle (LOC (sep, sep), LOC ((size.y / 4) * 3, (size.y / 4) * 3), Settings::UI::mainColor);
			DrawFilledRectangle (LOC (sep + 2, sep + 2), LOC (((size.y / 4) * 3) - 2, ((size.y / 4) * 3) - 2), Settings::UI::mainColor);
		}
		
		Vector2D textSize = Draw::GetTextSize (text.c_str(), normal_font);
		
		DrawString (text, normal_font, text_color, LOC (size.x-textSize.x-(sep*2), (size.y/2)-(textSize.y/2)));
	}
};

class ToggleButton : public ToggleSwitchBase, public Button
{
protected: 
	Color hovered_outline_color = Color (200, 200, 200, 20);

public:

	ToggleButton (std::wstring text, Vector2D position, Vector2D size, bool* setting)
        : ToggleSwitchBase(text, setting)
        , Button (text, position, size)
	{
		this->setting = setting;
		this->OnClickedEvent = MFUNC (&ToggleSwitchBase::Toggle, this);
	}
	
	void Draw ()
	{
		Clear (background_color);
		
		if (*setting)
		{
			DrawRectangle (LOC (0, 0), size, Settings::UI::mainColor);
		}
		else if (isHovered)
		{
			DrawRectangle (LOC (0, 0), size, hovered_outline_color);
		}
		
		DrawCenteredString (reinterpret_cast<ToggleSwitchBase*>(this)->text, normal_font, text_color, LOC (size.x / 2, size.y / 2));
	}
};
