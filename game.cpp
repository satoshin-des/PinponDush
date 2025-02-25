#include "game.h"

void Game::setNumHouse(const int n)
{
    m_num_house = n;
}

void Game::setNGHouse()
{
    okHouseIndex = rand() % m_num_house;
}

void Game::jumpOutStr(const String str)
{
    m_font_MSDF(str).drawAt(std::min(std::pow(10 * test_stopwatch.sF(), 2.0), 100.0), Scene::Center(), Palette::Red);
}

int Game::titleScreen()
{
    m_house_x = WIDTH_X + HOUSE_SIZE - static_cast<long>(300 * m_house_spd * stopwatch.sF()) % (WIDTH_X + 2 * HOUSE_SIZE);

    // 家の表示
    m_house_buttons[0].setPos(m_house_x, WIDTH_Y_HALF + HOUSE_SIZE);
    m_house_buttons[1].setPos(m_house_x, WIDTH_Y_HALF - HOUSE_SIZE);
    m_house_buttons[0].isClicked(false);
    m_house_buttons[1].isClicked(false);

    m_font(U"Pinpon Dush  \n  Challenge").drawAt(Scene::Center(), Palette::Black);

    if (SimpleGUI::Button(U"Start", Vec2{ 100, 500 }, 100))
    {
        srand(0);

        stopwatch.restart();
        return GAME_SCREEN;
    }

    if (SimpleGUI::Button(U"Option", Vec2{ WIDTH_X - 200, 500 }, 100))
    {
        stopwatch.restart();
        return OPTION_SCREEN;
    }

	return TITLE_SCREEN;
}

int Game::mainScreen()
{   
    m_score_font(U"Score: {}"_fmt(m_num_dushed_houses)).draw(0, 0, Palette::Black);

    m_house_x = WIDTH_X + HOUSE_SIZE - static_cast<long>(300 * m_house_spd * stopwatch.sF()) % (WIDTH_X + 2 * HOUSE_SIZE);

    for (int i = 0; i < m_num_house; ++i)
    {
        m_house_buttons[i].setPos(m_house_x, (i + 1.0) * WIDTH_X / (2 * m_num_house));

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

                test_stopwatch.restart();
            }
            else
            {
                stopwatch.restart();
                return GAME_OVER_SCREEN;
            }
        }
    }
    
    if (m_is_pinponed)
    {
        jumpOutStr(U"CLEAR");
    }

    if (m_house_x <= -HOUSE_SIZE / 2)
    {
        setNGHouse();
        m_is_pinponed = false;
    }

    return GAME_SCREEN;
}

int Game::gameOverScreen()
{
    m_house_x = WIDTH_X + HOUSE_SIZE - static_cast<long>(300 * m_house_spd * stopwatch.sF()) % (WIDTH_X + 2 * HOUSE_SIZE);

    // 家の表示
    m_house_buttons[0].setPos(m_house_x, WIDTH_Y_HALF + HOUSE_SIZE);
    m_house_buttons[1].setPos(m_house_x, WIDTH_Y_HALF - HOUSE_SIZE);
    m_house_buttons[0].isClicked(false);
    m_house_buttons[1].isClicked(false);

    m_font(U"Game Over\nScore:{}"_fmt(m_num_dushed_houses)).drawAt(Scene::Center(), Palette::Black);

    if (SimpleGUI::Button(U"Restart", Vec2{ 100, 500 }, 100))
    {
        srand(0);

        setNumHouse(2);

        stopwatch.restart();
        m_num_dushed_houses = 0;
        return GAME_SCREEN;
    }

    if (SimpleGUI::Button(U"Finish", Vec2{ WIDTH_X - 200, 500 }, 100))
    {
        setNumHouse(2);

        stopwatch.restart();
        m_num_dushed_houses = 0;
        return TITLE_SCREEN;
    }

    return GAME_OVER_SCREEN;
}

int Game::optionScreen()
{
    m_house_x = WIDTH_X + HOUSE_SIZE - static_cast<long>(300 * m_house_spd * stopwatch.sF()) % (WIDTH_X + 2 * HOUSE_SIZE);

    // 家の表示
    m_house_buttons[0].setPos(m_house_x, WIDTH_Y_HALF + HOUSE_SIZE);
    m_house_buttons[1].setPos(m_house_x, WIDTH_Y_HALF - HOUSE_SIZE);
    m_house_buttons[0].isClicked(false);
    m_house_buttons[1].isClicked(false);

    m_font(U"Pinpon Dush  \n  Challenge").drawAt(Scene::Center(), Palette::Black);

    // 家の動く速度の調整
    SimpleGUI::Slider(U"{:.2f}"_fmt(m_house_spd), m_house_spd, 1.0, WIDTH_X_HALF / 2.0, Vec2{ 200, 40 }, 80, 150);

    if (SimpleGUI::Button(U"House Design", Vec2{ 200, 120 }))
    {
        for (int i = 0; i < 100; ++i)
        {
            m_house_buttons[i].setDesign();
        }
    }

    if (SimpleGUI::Button(U"Title", Vec2{ WIDTH_X_HALF, 500 }, 100))
    {
        stopwatch.restart();
        return TITLE_SCREEN;
    }

    return OPTION_SCREEN;
}
