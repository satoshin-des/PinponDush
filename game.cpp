#include "game.h"

void Game::setSuccessfulHouse()
{
    successful_house_index = Random(m_num_house - 1);
}

void Game::incrHouse()
{
    if (m_num_dushed_houses % 3 == 0)
    {
        m_num_house = std::min(m_num_house + 1, 100);
    }
}

bool Game::failurePinponDush()
{
    m_house_x = WIDTH_X + HOUSE_SIZE - 300 * m_house_spd * m_house_pos_param.sF();

    for (int i = 0; i < m_num_house; ++i)
    {
        m_house_buttons[i].setPos(m_house_x, (i + 1.0) * WIDTH_X / (2 * m_num_house));

        if (m_house_buttons[i].isClicked(true) && (!m_is_pinponed))
        {
            if (i == successful_house_index)
            {
                ++m_num_dushed_houses;

                incrHouse();

                m_is_pinponed = true;

                m_font_size_param.restart();
            }
            else
            {
                m_house_pos_param.restart();

                m_num_house = 2;
                setSuccessfulHouse();

                m_font_size_param.restart();

                return true;
            }
        }
    }

    if (m_house_x <= -HOUSE_SIZE)
    {
        if (!m_is_pinponed)
        {
            m_house_pos_param.restart();

            m_num_house = 2;
            setSuccessfulHouse();

            m_font_size_param.restart();

            return true;
        }

        m_house_pos_param.restart();

        setSuccessfulHouse();
        m_is_pinponed = false;
    }

    return false;
}

void Game::jumpOutStr(const String str)
{
    m_font_MSDF(str).drawAt(std::min(std::pow(10 * m_font_size_param.sF(), 2.0), 100.0), Scene::Center(), Palette::Red);
}

int Game::titleScreen()
{
    m_house_x = WIDTH_X + HOUSE_SIZE - 300 * m_house_spd * m_house_pos_param.sF();

    // 家の表示
    m_house_buttons[0].setPos(m_house_x, WIDTH_Y_HALF + HOUSE_SIZE);
    m_house_buttons[1].setPos(m_house_x, WIDTH_Y_HALF - HOUSE_SIZE);
    m_house_buttons[0].isClicked(false);
    m_house_buttons[1].isClicked(false);

    m_font(m_title_str).drawAt(Scene::Center(), Palette::Black);

    if (SimpleGUI::Button(U"Start", Vec2{ 100, 500 }, 100))
    {
        srand(0);

        m_house_pos_param.restart();
        return GAME_SCREEN;
    }

    if (SimpleGUI::Button(U"Option", Vec2{ WIDTH_X - 200, 500 }, 100))
    {
        m_house_pos_param.restart();
        return OPTION_SCREEN;
    }

    if (m_house_x <= -HOUSE_SIZE)
    {
        m_house_pos_param.restart();
    }

	return TITLE_SCREEN;
}

int Game::mainScreen()
{   
    m_score_font(U"Score: {}"_fmt(m_num_dushed_houses)).draw(0, 0, Palette::Black);
    
    if (failurePinponDush())
    {
        return GAME_OVER_SCREEN;
    }
    
    if (m_is_pinponed)
    {
        jumpOutStr(m_clear_str);
    }
    
    return GAME_SCREEN;
}

int Game::gameOverScreen()
{
    m_house_x = WIDTH_X + HOUSE_SIZE - 300 * m_house_spd * m_house_pos_param.sF();

    // 家の表示
    m_house_buttons[0].setPos(m_house_x, WIDTH_Y_HALF + HOUSE_SIZE);
    m_house_buttons[1].setPos(m_house_x, WIDTH_Y_HALF - HOUSE_SIZE);
    m_house_buttons[0].isClicked(false);
    m_house_buttons[1].isClicked(false);

    jumpOutStr(m_failure_str);
    m_font(U"Score:{}"_fmt(m_num_dushed_houses)).drawAt(Scene::Center(), Palette::Black);

    if (SimpleGUI::Button(m_retry_button_label, Vec2{ 100, 500 }, 100))
    {
        srand(0);

        m_house_pos_param.restart();
        m_num_dushed_houses = 0;
        return GAME_SCREEN;
    }

    if (SimpleGUI::Button(m_title_button_label, Vec2{ WIDTH_X - 200, 500 }, 100))
    {
        m_house_pos_param.restart();
        m_num_dushed_houses = 0;
        return TITLE_SCREEN;
    }

    if (m_house_x <= -HOUSE_SIZE)
    {
        m_house_pos_param.restart();
    }

    return GAME_OVER_SCREEN;
}

int Game::optionScreen()
{
    m_house_x = WIDTH_X + HOUSE_SIZE - static_cast<long>(300 * m_house_spd * m_house_pos_param.sF()) % (WIDTH_X + 2 * HOUSE_SIZE);

    // 家の表示
    m_house_buttons[0].setPos(m_house_x, WIDTH_Y_HALF + HOUSE_SIZE);
    m_house_buttons[1].setPos(m_house_x, WIDTH_Y_HALF - HOUSE_SIZE);
    m_house_buttons[0].isClicked(false);
    m_house_buttons[1].isClicked(false);

    m_font(m_title_str).drawAt(Scene::Center(), Palette::Black);

    // 家の動く速度の調整
    SimpleGUI::Slider(U"{:.2f}"_fmt(m_house_spd), m_house_spd, 1.0, 10.0, Vec2{ 200, 40 }, 80, 150);

    if (SimpleGUI::Button(m_change_house_button_label, Vec2{200, 120}))
    {
        for (int i = 0; i < 100; ++i)
        {
            m_house_buttons[i].setDesign();
        }
    }

    if (SimpleGUI::Button(m_title_button_label, Vec2{ WIDTH_X_HALF, 500 }, 100))
    {
        m_house_pos_param.restart();
        return TITLE_SCREEN;
    }

    return OPTION_SCREEN;
}
