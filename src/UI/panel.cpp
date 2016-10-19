#include "panel.h"


Panel::Panel (Vector2D position, Vector2D size, Color backgroundColor) 
    : Component (position, size)
    , backGroundColor(backGroundColor)
{
}


Panel::Panel (Vector2D position, Vector2D size) 
    : Component(position, size)
{
}

Panel::Panel (Vector2D position) 
    : Component(position)
{
}

Panel::Panel ()
{
}

void Panel::Draw ()
{
	if (shown)
	{
		this->Clear (backGroundColor);
		
		
		for (int i = 0; i < childComponents.size(); i++)
		{
			Component* childComponent = childComponents[i];
			
			// Update the childs context
			childComponent->context = this->context + childComponent->position;
			
			// Draw the component
			childComponent->Draw ();
		}
	}
}

void Panel::OnMouseClickStart (PositionContext mouseContext)
{
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		
		int x = mouseContext.x;
		int y = mouseContext.y;
		
		if	(x >= childComponent->position.x && x <= childComponent->position.x + childComponent->size.x &&
				y >= childComponent->position.y && y <= childComponent->position.y + childComponent->size.y)
		{
			childComponent->OnMouseClickStart (mouseContext - childComponent->position);
			
			childComponent->isMouseDown = true;
			
			if (childComponent->onMouseClickStartEvent != NULL)
			{
				childComponent->onMouseClickStartEvent ();
			}
		}
	}
}

void Panel::OnMouseClickEnd (PositionContext mouseContext)
{
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		
		int x = mouseContext.x;
		int y = mouseContext.y;
		
		if	(x >= childComponent->position.x && x <= childComponent->position.x + childComponent->size.x &&
				y >= childComponent->position.y && y <= childComponent->position.y + childComponent->size.y)
		{
			childComponent->OnMouseClickEnd (mouseContext - childComponent->position);
			
			childComponent->isMouseDown = false;
			
			if (childComponent->onMouseClickEndEvent != NULL)
			{
				childComponent->onMouseClickEndEvent ();
			}
		}
	}
}

void Panel::Input ()
{
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		childComponent->Input ();
	}
}

void Panel::MouseTick (PositionContext mouseContext)
{
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		
		int x = mouseContext.x;
		int y = mouseContext.y;
		
		if	(
				x >= childComponent->position.x && x <= childComponent->position.x + childComponent->size.x &&
				y >= childComponent->position.y && y <= childComponent->position.y + childComponent->size.y
			)
		{
			if (!childComponent->isHovered)
			{
				childComponent->isHovered = true;
				if (childComponent->onMouseEnterEvent != NULL)
				{
					childComponent->onMouseEnterEvent();
				}
			}
			
			childComponent->MouseTick (mouseContext - childComponent->position);
		}
		else
		{
			if (childComponent->isHovered)
			{
				childComponent->isHovered = false;
				childComponent->isMouseDown = false;
				if (childComponent->onMouseLeaveEvent != NULL)
				{
					childComponent->onMouseLeaveEvent();
				}
			}
		}
	}
}
