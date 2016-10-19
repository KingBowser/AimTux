#pragma once

#include "component.h"
#include "../settings.h"
#include <math.h>

#define ROUNDF(f, c) (((float)((int)((f) * (c))) / (c)))

class Slider : public Component
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color background_color = Color (160, 160, 160, 80);

private:
	float* value;
	const float MIN;
	const float MAX;

public:
	std::wstring text = L"slider";
	
	Slider (std::wstring text, Vector2D position, Vector2D size, float* value, float MIN, float MAX)
			: Component(position, size)
            , text(text)
            , value(value)
            , MIN (MIN)
            , MAX (MAX)
	{
	}
	
	void MouseTick (PositionContext context);
	void Draw ();
	void Input ();
};
