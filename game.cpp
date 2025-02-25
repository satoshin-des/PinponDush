#include "game.h"

void Game::setNumHouse(const int n)
{
    m_num_house = n;
}

void Game::setNGHouse()
{
    okHouseIndex = rand() % m_num_house;
}

int Game::titleScreen()
{
    // 家の表示
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

    // 家を動かす為のパラメタの更新
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
        m_house_buttons[i].setPos(m_time_count, (i + 1.0) * WIDTH_X / (2 * m_num_house));

        if (m_house_buttons[i].isClicked() && (!m_is_pinponed))
        {
            if (i == okHouseIndex)
            {
                ++m_num_dushed_houses;

                if (m_num_dushed_houses % 3 == 0)
                {
                    ++m_num_house;
                }

                m_is_pinponed = true;
            }
            else
            {
                return GAME_OVER_SCREEN;
            }
        }
    }

    m_time_count -= 3;
    if (m_time_count <= -HOUSE_SIZE)
    {
        setNGHouse();
        m_time_count = WIDTH_X + HOUSE_SIZE;
        m_is_pinponed = false;
    }

    return GAME_SCREEN;
}

int Game::gameOverScreen()
{
    m_house.resized(HOUSE_SIZE).drawAt(Vec2{ m_time_count, WIDTH_Y_HALF + HOUSE_SIZE });
    m_house.resized(HOUSE_SIZE).drawAt(Vec2{ m_time_count, WIDTH_Y_HALF - HOUSE_SIZE });

    m_font(U"Score:{}"_fmt(m_num_dushed_houses)).drawAt(Scene::Center(), Palette::Black);

    if (SimpleGUI::Button(U"Restart", Vec2{ 100, 500 }, 100))
    {
        setNumHouse(2);

        m_num_dushed_houses = 0;
        m_time_count = WIDTH_X + HOUSE_SIZE;
        return GAME_SCREEN;
    }

    if (SimpleGUI::Button(U"Finish", Vec2{ WIDTH_X - 200, 500 }, 100))
    {
        setNumHouse(2);

        m_num_dushed_houses = 0;
        m_time_count = WIDTH_X + HOUSE_SIZE;
        return TITLE_SCREEN;
    }

    m_time_count -= 3;
    if (m_time_count <= -HOUSE_SIZE)
    {
        m_time_count = WIDTH_X + HOUSE_SIZE;
    }

    return GAME_OVER_SCREEN;
}
