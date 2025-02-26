#include "house.h"

void House::setDesign()
{
	m_house_label = Random(2);

	if (m_house_label == 0)
	{
		m_house = Texture{ U"🏠"_emoji };
	}
	else if (m_house_label == 1)
	{
		m_house = Texture{ U"🏘"_emoji };
	}
	else if (m_house_label == 2)
	{
		m_house = Texture{ U"🏡"_emoji };
	}
}

void House::setPos(const double x, const double y)
{
	m_x = x;
	m_y = y;
}

bool House::isClicked(const bool canClick)
{
	if (canClick)
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

		RectF{ m_x - 60, m_y - 30, HOUSE_SIZE, HOUSE_SIZE }.draw(ColorF{ SKY_BLUE });
	}

	m_house.resized(HOUSE_SIZE).drawAt(Vec2{ m_x, m_y });

	return false;
}
