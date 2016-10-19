#pragma once

#include "panel.h"
#include "button.h"
#include "../settings.h"

#define LB_ELEMENT_HEIGHT 30
#define LB_ELEMENT_SEPARATOR_WIDTH 10

struct LB_Element
{
	std::wstring name;
	unsigned int value;
	
	LB_Element (std::wstring name, unsigned int value)
        : name(name)
        , value(value)
	{
	}
};

template<typename T>
class LB_Button : public Button
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color background_color = Color (160, 160, 160, 7);
	Color background_color_hovered = Color (160, 160, 160, 12);
public:
	LB_Element* element;
	T* setting;
	
	void OnClicked ()
	{
		*static_cast<unsigned int*>((void*)setting) = element->value;
	}
	
	LB_Button (std::wstring text, Vector2D position, Vector2D size, T* setting, LB_Element* element)
		: Button (text, position, size)
        , element(element)
        , setting(setting)
	{
		this->OnClickedEvent = MFUNC (&LB_Button::OnClicked, this);
	}
	
	void Draw ()
	{
		Clear (isHovered ? background_color_hovered : background_color);
		
		if (*static_cast<unsigned int*>((void*)setting) == element->value)
		{
			DrawRectangle (LOC (0, 0), size, Settings::UI::mainColor);
		}
		
		DrawCenteredString (text, normal_font, text_color, LOC (size.x / 2, size.y / 2));
	}
};

template<typename E>
class LBBase : public Panel
{
protected:
    Color background_color = Color(160, 160, 160, 4);

public:
    std::wstring text = "listbox";
    std::vector<LB_Element> elements;
    E* setting;

    LBBase<E> (std::wstring text, Vector2D position, E* setting, std::vector<LB_Element> elements)
        : Panel(position)
        , text(text)
        , elements(elements)
        , setting(setting)
    {
    }

    void Draw ()
    {
        Clear (background_color);

        DrawRectangle (LOC (0, 0), this->size, Settings::UI::mainColor);

        Panel::Draw ();
    }
};

template<typename E>
class ListBox : public LBBase<E>
{
public:
	
	ListBox<E> (std::wstring text, Vector2D position, int width, E* setting, std::vector<LB_Element> elements)
        : LBBase<E> (text, position, setting, elements)
	{
		for (int i = 0; i < elements.size(); i++)
		{
			LB_Element* element = &this->elements[i];
			
			LB_Button<E>* new_button = new LB_Button<E> (element->name, LOC (10, 10 + (i * LB_ELEMENT_HEIGHT) + (i * LB_ELEMENT_SEPARATOR_WIDTH)), LOC (width - 20, LB_ELEMENT_HEIGHT), this->setting, element);
            Panel::AddComponent (new_button);
		}
		
		this->size = Vector2D (width, (elements.size() * LB_ELEMENT_HEIGHT) + (10 + (elements.size() * LB_ELEMENT_SEPARATOR_WIDTH)));
	}
	
};

template<typename E>
class StackedListBox : public LBBase<E>
{
public:
	
	StackedListBox<E> (std::wstring text, Vector2D position, int width, int elements_x, E* setting, std::vector<LB_Element> elements)
        : LBBase<E> (text, position, setting, elements)
	{
		int elementWidth = ((width - (10 + (elements_x * 10))) / elements_x);
		
		int x = 0, y = 0;
		for (int i = 0; i < elements.size(); i++)
		{
			if (x == elements_x)
			{
				++y;
				x = 0;
			}
			
			LB_Element* element = &this->elements[i];
			
			LB_Button<E>* new_button = new LB_Button<E> (
				element->name,
				LOC ((x * elementWidth) + (10 + (x * 10)), (y * LB_ELEMENT_HEIGHT) + (10 + (y * 10))),
				LOC (elementWidth - 20, LB_ELEMENT_HEIGHT),
				this->setting,
				element
			);

            Panel::AddComponent (new_button);
			
			++x;
		}
		
		this->size = Vector2D (width, ((y+1) * LB_ELEMENT_HEIGHT) + (10 + ((y+1) * LB_ELEMENT_SEPARATOR_WIDTH)));
	}
};
