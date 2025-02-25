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
    m_house_buttons[0].setPos(m_time_count, WIDTH_Y_HALF + HOUSE_SIZE);
    m_house_buttons[1].setPos(m_time_count, WIDTH_Y_HALF - HOUSE_SIZE);
    m_house_buttons[0].isClicked(false);
    m_house_buttons[1].isClicked(false);

    m_font(U"Pinpon Dush  \n  Challenge").drawAt(Scene::Center(), Palette::Black);

    if (SimpleGUI::Button(U"Start", Vec2{ 100, 500 }, 100))
    {
        m_time_count = WIDTH_X + HOUSE_SIZE;
        return GAME_SCREEN;
    }

    if (SimpleGUI::Button(U"Option", Vec2{ WIDTH_X - 200, 500 }, 100))
    {
        m_time_count = WIDTH_X + HOUSE_SIZE;
        return OPTION_SCREEN;
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

        if (m_house_buttons[i].isClicked(true) && (!m_is_pinponed))
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

    m_time_count -= m_house_spd;
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
    m_house_buttons[0].setPos(m_time_count, WIDTH_Y_HALF + HOUSE_SIZE);
    m_house_buttons[1].setPos(m_time_count, WIDTH_Y_HALF - HOUSE_SIZE);
    m_house_buttons[0].isClicked(false);
    m_house_buttons[1].isClicked(false);

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

    m_time_count -= m_house_spd;
    if (m_time_count <= -HOUSE_SIZE)
    {
        m_time_count = WIDTH_X + HOUSE_SIZE;
    }

    return GAME_OVER_SCREEN;
}

int Game::optionScreen()
{
    // 家の表示
    m_house_buttons[0].setPos(m_time_count, WIDTH_Y_HALF + HOUSE_SIZE);
    m_house_buttons[1].setPos(m_time_count, WIDTH_Y_HALF - HOUSE_SIZE);
    m_house_buttons[0].isClicked(false);
    m_house_buttons[1].isClicked(false);

    m_font(U"Pinpon Dush  \n  Challenge").drawAt(Scene::Center(), Palette::Black);

    // 家の動く速度の調整
    SimpleGUI::Slider(U"{:.2f}"_fmt(m_house_spd), m_house_spd, 3.0, WIDTH_X_HALF / 2.0, Vec2{ 200, 40 }, 80, 150);

    if (SimpleGUI::Button(U"House Design", Vec2{ 200, 120 }))
    {
        for (int i = 0; i < 100; ++i)
        {
            m_house_buttons[i].setDesign();
        }
    }

    if (SimpleGUI::Button(U"Title", Vec2{ WIDTH_X_HALF, 500 }, 100))
    {
        m_time_count = WIDTH_X + HOUSE_SIZE;
        return TITLE_SCREEN;
    }

    // 家を動かす為のパラメタの更新
    m_time_count -= m_house_spd;
    if (m_time_count <= -HOUSE_SIZE)
    {
        m_time_count = WIDTH_X + HOUSE_SIZE;
    }

    return OPTION_SCREEN;
}
