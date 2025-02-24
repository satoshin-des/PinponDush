#include "game.h"

void Game::setNumHouse(const int n)
{
    m_num_house = n;
    m_house_buttons.resize(n);
}

void Game::setNGHouse()
{
    std::uniform_int_distribution<uint64_t> get_rand_uni_int(0, m_num_house - 1);

    ngHouseIndex = get_rand_uni_int(mt64);
}

int Game::titleScreen()
{
    m_house.resized(HOUSE_SIZE).drawAt(Vec2{ m_time_count, WIDTH_Y_HALF + HOUSE_SIZE });
    m_house.resized(HOUSE_SIZE).drawAt(Vec2{ m_time_count, WIDTH_Y_HALF - HOUSE_SIZE });

    m_font(U"Pinpon Dush  \n  Challenge").drawAt(Scene::Center(), Palette::Black);

    if (SimpleGUI::Button(U"Start", Vec2{ 100, 500 }, 100))
    {
        m_time_count = WIDTH_X + HOUSE_SIZE;
        return GAME_SCREEN;
    }

    if (SimpleGUI::Button(U"Option", Vec2{ WIDTH_X - 200, 500 }, 100))
    {
        m_time_count = WIDTH_X + HOUSE_SIZE;
        return GAME_SCREEN;
    }

    m_time_count -= 3;
    if (m_time_count <= -HOUSE_SIZE)
    {
        m_time_count = WIDTH_X + HOUSE_SIZE;
    }

	return TITLE_SCREEN;
}

int Game::mainScreen()
{   
    for (int i = 0; i < m_num_house; ++i)
    {
        m_house_buttons[i].setPos(m_time_count, (i + 1.0) * WIDTH_X / (2.0 * m_num_house));

        if (m_house_buttons[i].isClicked())
        {
            if (i == ngHouseIndex)
            {
                return TITLE_SCREEN;
            }
        }
    }

    m_time_count -= 3;
    if (m_time_count <= -HOUSE_SIZE)
    {
        setNGHouse();
        m_time_count = WIDTH_X + HOUSE_SIZE;
    }

    return GAME_SCREEN;
}
