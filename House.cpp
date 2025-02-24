#include "house.h"

void House::setPos(const double x, const double y)
{
	m_x = x;
	m_y = y;
}

bool House::isClicked()
{
	if (SimpleGUI::Button(U"house", Vec2{ m_x - 50, m_y }, 100))
	{
		return true;
	}
	if (SimpleGUI::Button(U"house", Vec2{ m_x - 50, m_y + 20 }, 100))
	{
		return true;
	}
	if (SimpleGUI::Button(U"house", Vec2{ m_x - 50, m_y - 20 }, 100))
	{
		return true;
	}

	m_house.resized(HOUSE_SIZE).drawAt(Vec2{ m_x, m_y });

	return false;
}
