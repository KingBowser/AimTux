#include "draw.h"

/*
 * Draw::CreateFont()
 */

FONT Draw::CreateFont(const char* fontName, int size, int flag)
{
	FONT newFont = surface->CreateFont();

	surface->SetFontGlyphSet(newFont, fontName, size, 0, 0, 0, flag);

	return newFont;
}

FONT Draw::CreateFont(const char* fontName, int size)
{
	return Draw::CreateFont(fontName, size, 0x80);
}

/*
 * Draw::GetTextSize()
 */

Vector2D Draw::GetTextSize(const wchar_t* text, FONT font)
{
	int x = 0;
	int y = 0;
	
	surface->GetTextSize(font, text, x, y);

	return LOC(x, y);
}

Vector2D Draw::GetTextSize(std::wstring text, FONT font)
{
	return Draw::GetTextSize(text.c_str(), font);
}

/*
 * Draw::DrawString()
 * Draw::DrawCenteredString()
 */

void Draw::DrawString(std::wstring text, Vector2D location, Color color, FONT font)
{
	surface->DrawSetTextColor(color.r, color.g, color.b, color.a);
	surface->DrawSetTextFont(font);
	surface->DrawSetTextPos((int) location.x, (int) location.y);

	surface->DrawPrintText(text.c_str(), text.length());
}

void Draw::DrawCenteredString(std::wstring text, Vector2D location, Color color, FONT font)
{
	Vector2D textSize = GetTextSize(text, font);
	location.x -= textSize.x / 2;
	location.y -= textSize.y / 2;

    Draw::DrawString(text, location, color, font);
}

/*
 * Draw::DrawCircle()
 * Draw::DrawRect()
 * Draw::DrawBox()
 * Draw::DrawOutlinedBox()
 * Draw::DrawPolygon()
 * Draw::DrawPolygonOutline()
 * Draw::DrawLine()
 * Draw::DrawPolyLine()
 * etc...
 */

void Draw::DrawCircle(Vector2D position, float points, float radius, Color color)
{
	float step = M_PI * 2.0 / points;

	for (float a = 0; a < ( M_PI * 2.0 ); a += step)
	{
		Vector2D start (radius * cos(a) + position.x, radius * sin(a) + position.y);
		Vector2D end ( radius * cos(a + step) + position.x, radius * sin(a + step) + position.y);
		DrawLine(start, end, color);
	}
}

void Draw::DrawRect(Vector2D start, Vector2D end, Color color)
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawFilledRect((int) start.x, (int) start.y, (int) end.x, (int) end.y);
}

void Draw::DrawBox(Vector2D start, Vector2D end, Color color)
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawOutlinedRect((int) start.x, (int) start.y, (int) end.x, (int) end.y);
}

void Draw::DrawLine(Vector2D start, Vector2D end, Color color)
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawLine((int) start.x, (int) start.y, (int) end.x, (int) end.y);
}

void Draw::DrawOutlinedBox(float x, float y, float w, float h, Color color )
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawOutlinedRect((int) (x - w), (int) y, (int) (x + w), (int) (y + h));

	int div = 3;
	surface->DrawSetColor(color.r / div, color.g / div, color.b / div, 255);
	surface->DrawOutlinedRect((int) (x - w - 1), (int) (y - 1), (int) (x + w + 1), (int) (y + h + 1));
	surface->DrawOutlinedRect((int) (x - w + 1), (int) (y + 1), (int) (x + w - 1), (int) (y + h - 1));
}

void Draw::DrawPolygon(int count, Vertex_t* Vertexs, Color color)
{
	static int Texture = surface->CreateNewTextureID(true);
	unsigned char buffer[4] = { 255, 255, 255, 255 };

	surface->DrawSetTextureRGBA(Texture, buffer, 1, 1);
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawSetTexture(Texture);

	surface->DrawTexturedPolygon(count, Vertexs);
}

void Draw::DrawPolygonOutline(int count, Vertex_t* Vertexs, Color color, Color colorLine)
{
	static int x[128];
	static int y[128];

	Draw::DrawPolygon(count, Vertexs, color);

	for (int i = 0; i < count; i++)
	{
		x[i] = Vertexs[i].m_Position.x;
		y[i] = Vertexs[i].m_Position.y;
	}

	Draw::DrawPolyLine(x, y, count, colorLine);
}

void Draw::DrawPolyLine(int *x, int *y, int count, Color color)
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawPolyLine(x, y, count);
}

void Draw::DrawPolyLine(int count, Vertex_t* Vertexs, Color colorLine)
{
	static int x[128];
	static int y[128];

	for (int i = 0; i < count; i++)
	{
		x[i] = Vertexs[i].m_Position.x;
		y[i] = Vertexs[i].m_Position.y;
	}

	Draw::DrawPolyLine(x, y, count, colorLine);
}
