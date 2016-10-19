#pragma once

#include "component.h"
#include "../settings.h"
#include "../util.h"
#include <algorithm>

class TextBox : public Component
{
protected:
	Color text_color	   = Color (255, 255, 255, 200);
	Color background_color = Color (160, 160, 160, 5);
	bool s_showCaret = false;
	int s_caret_stamp;
	Vector2D font_size;

private:
	std::vector<ButtonCode_t> lastPressedKeys;
	
public:
	
	std::wstring* strp;
	std::wstring shadow_text = L"textbox"; 
	
	TextBox (std::wstring shadow, std::wstring* textref, Vector2D position, Vector2D size)
		: Component(position, size)
        , shadow_text(shadow)
		, strp(textref)
	{
		// Get the width if the monospaced font
		font_size = Draw::GetTextSize (L"j", mono_font);
		
		// set the default caret_stamp to the current tick_count
		s_caret_stamp = globalvars->tickcount;
	}
	
	void Draw ()
	{
		Clear (background_color);
		
		if (isHovered)
		{
			DrawRectangle (LOC (0, 0), size, Settings::UI::mainColor);
		}
		
		
		int text_max_fit = (size.x-20) / font_size.x;
	
        const wchar_t* sectioned_text = (strp->size() > text_max_fit ? &strp->c_str()[strp->size() - text_max_fit] : strp->c_str());
        size_t sectioned_text_size = wcslen(sectioned_text);

        DrawString (sectioned_text, mono_font, text_color, LOC (10, (size.y / 2) - (font_size.y / 2)));
		
		int current_tick = globalvars->tickcount;
		
		if (current_tick > s_caret_stamp + 40)
		{
			s_caret_stamp = current_tick;
			s_showCaret = !s_showCaret;
		}
		
		// Draw caret
		if (s_showCaret && isHovered)
		{
			DrawFilledRectangle (LOC (12 + (sectioned_text_size * font_size.x), (size.y / 4)), LOC (14 + (sectioned_text_size * font_size.x), (size.y / 4) * 3), text_color);
		}
	}
	
	bool GetPressedKeys (std::vector<ButtonCode_t>& pressedKeys)
	{
		bool _isKeyPressed = false;
		
		for (int i = KEY_0; i <= KEY_RIGHT; i++)
		{
			ButtonCode_t key = (ButtonCode_t)i;
			
			if (input->IsButtonDown (key))
			{
				_isKeyPressed = true;
				pressedKeys.push_back (key);
			}
		}
		
		return _isKeyPressed;
	}

	void Input ()
	{
		if (!isHovered)
		{
			return;
		}
		
		std::vector<ButtonCode_t> pressedKeys;
		bool isKeyPressed = GetPressedKeys (pressedKeys);
		bool shift = input->IsButtonDown (KEY_LSHIFT) || input->IsButtonDown (KEY_RSHIFT);
		
		for (int i = 0; i < pressedKeys.size(); i++)
		{
			ButtonCode_t key = (ButtonCode_t)pressedKeys[i];
			
			if (std::find(lastPressedKeys.begin(), lastPressedKeys.end(), key) != lastPressedKeys.end() || key > KEY_EQUAL)
			{
				continue;
			}
			
			char character = Util::GetButtonString(key);
			
			if (shift)
			{
				character = Util::GetUpperValueOf(key);
			}
			
			strp->operator+=(character);
		}
		
		if (strp->size() > 0 &&
			std::find(pressedKeys.begin(), pressedKeys.end(), KEY_BACKSPACE) != pressedKeys.end() &&
			std::find(lastPressedKeys.begin(), lastPressedKeys.end(), KEY_BACKSPACE) == lastPressedKeys.end()
			)
		{
			strp->pop_back ();
		}
		
		if (strp->size() > 0 &&
			std::find(pressedKeys.begin(), pressedKeys.end(), KEY_SPACE) != pressedKeys.end() &&
			std::find(lastPressedKeys.begin(), lastPressedKeys.end(), KEY_SPACE) == lastPressedKeys.end()
			)
		{
			strp->operator+=(L" ");
		}
		
		lastPressedKeys = pressedKeys;
	}
};

class ValueTextBox : public TextBox
{
public:
	pstring text;

	ValueTextBox(std::wstring shadow, std::wstring val, Vector2D pos, Vector2D size)
		: text(val)
		, TextBox(shadow, &text, pos, size)
	{
	}
};
