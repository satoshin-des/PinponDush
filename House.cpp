#include "house.h"

void House::setPos(const double x, const double y)
{
	m_x = x;
	m_y = y;
}

bool House::isClicked()
{
	if (SimpleGUI::Button(U"Start", Vec2{ m_x - 75, m_y }, 100))
	{
		return true;
	}

	m_house.resized(150).drawAt(Vec2{ m_x, m_y });

	return false;
}
