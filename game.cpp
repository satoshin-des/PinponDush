#include "game.h"

int Game::titleScreen()
{
    m_house.resized(150).drawAt(Vec2{ m_time_count, 450 });
    m_house.resized(150).drawAt(Vec2{ m_time_count, 150 });

    m_font(U"Pinpon Dush  \n  Challenge").drawAt(Scene::Center(), Palette::Black);

    if (SimpleGUI::Button(U"Start", Vec2{ 100, 500 }, 100))
    {
        m_time_count = 0;
        return GAME_SCREEN;
    }

    if (SimpleGUI::Button(U"Option", Vec2{ WIDTH_X - 200, 500 }, 100))
    {
        return GAME_SCREEN;
    }

    m_time_count -= 3;
    if (m_time_count <= -150)
    {
        m_time_count = WIDTH_X + 150;
    }

	return TITLE_SCREEN;
}


int Game::mainScreen()
{   
    house.setPos(m_time_count, 300);

    if (house.isClicked())
    {
        return TITLE_SCREEN;
    }

    m_time_count -= 3;
    if (m_time_count <= -150)
    {
        m_time_count = WIDTH_X + 150;
    }

    return GAME_SCREEN;
}
