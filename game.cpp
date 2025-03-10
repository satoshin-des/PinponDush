#include "game.h"

void Game::preloadFonts()
{
    // ルールのプリロード
	m_score_font.preload(m_text_data[U"rule"].getString().sorted_and_uniqued());
	// スコアのプリロード
	m_score_font.preload(U"Score: 0123456789.");
	// 成功と失敗のプリロード
	m_font_MSDF.preload(m_text_data[U"success"].getString().sorted_and_uniqued());
	m_font_MSDF.preload(m_text_data[U"failure"].getString().sorted_and_uniqued());
}

void Game::setSuccessfulHouse()
{
    successful_house_index = Random(m_num_house - 1);
}

void Game::incrHouse()
{
    if (m_score % 3 == 0)
    {
        m_num_house = std::min(m_num_house + 1, MAX_NUM_HOUSE);
    }
}

bool Game::failurePinponDush()
{
    m_house_x = WIDTH_X + HOUSE_SIZE - 300 * m_house_spd * m_house_pos_param.sF();

    for (int i = 0; i < m_num_house; ++i)
    {
        m_house_buttons[i].setPos(m_house_x, (2 * i + 1.0) * (WIDTH_Y) / (2 * m_num_house));

        if (m_house_buttons[i].isClicked(CAN_CLICK) && (!m_is_pinponed))
        {
            if (i == successful_house_index)
            {
                m_score += static_cast<int>(m_house_spd);

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

void Game::moveBackGroundHouse()
{
    m_house_x = WIDTH_X + HOUSE_SIZE - 300 * m_house_spd * m_house_pos_param.sF();

    // 家の表示
    m_house_buttons[0].setPos(m_house_x, WIDTH_Y_HALF + HOUSE_SIZE);
    m_house_buttons[1].setPos(m_house_x, WIDTH_Y_HALF - HOUSE_SIZE);
    m_house_buttons[0].isClicked(CANNOT_CLICK);
    m_house_buttons[1].isClicked(CANNOT_CLICK);

    if (m_house_x <= -HOUSE_SIZE)
    {
        m_house_pos_param.restart();
    }
}

void Game::jumpOutStr(const String str)
{
    m_font_MSDF(str).drawAt(std::min(std::pow(10 * m_font_size_param.sF(), 2.0), 100.0), Scene::Center(), Palette::Red);
}

int Game::titleScreen()
{
    if (!m_title_bgm.isPlaying())
    {
        m_title_bgm.play();
    }

    moveBackGroundHouse();
    
    m_font(m_text_data[U"title"].getString()).drawAt(Scene::Center(), Palette::Black);
    
    if (SimpleGUI::Button(m_text_data[U"button"][U"start"].getString(), Vec2{100, 500}, 100))
    {
        m_title_bgm.stop();
        m_main_bgm.play();

        Reseed(0);
        setSuccessfulHouse();

        m_house_pos_param.restart();
        return GAME_SCREEN;
    }

    if (SimpleGUI::Button(m_text_data[U"button"][U"rule"].getString(), Vec2{WIDTH_X_HALF - 50, 500}, 100))
    {
        m_title_bgm.stop();

        m_house_pos_param.restart();
        return RULE_SCREEN;
    }

    if (SimpleGUI::Button(m_text_data[U"button"][U"option"].getString(), Vec2{ WIDTH_X - 200, 500 }, 100))
    {
        m_house_pos_param.restart();
        return OPTION_SCREEN;
    }
    
	return TITLE_SCREEN;
}

int Game::mainScreen()
{   
    m_score_font(U"Score: {}"_fmt(m_score)).draw(0, 0, Palette::Black);
    
    if (failurePinponDush())
    {
        m_main_bgm.stop();
        m_game_over_bgm.play();

        return GAME_OVER_SCREEN;
    }
    
    if (m_is_pinponed)
    {
        jumpOutStr(m_text_data[U"success"].getString());
    }
    
    return GAME_SCREEN;
}

int Game::gameOverScreen()
{
    moveBackGroundHouse();

    jumpOutStr(m_text_data[U"failure"].getString());

    m_font(U"Score:{}"_fmt(m_score)).drawAt(Vec2{ WIDTH_X_HALF, 50 }, Palette::Black);

    if (SimpleGUI::Button(m_text_data[U"button"][U"retry"].getString(), Vec2{ 100, 500 }, 100))
    {
        m_game_over_bgm.stop();
        m_main_bgm.play();

        Reseed(0);
        setSuccessfulHouse();

        m_house_pos_param.restart();
        m_score = 0;
        return GAME_SCREEN;
    }

    if (SimpleGUI::Button(m_text_data[U"button"][U"title"].getString(), Vec2{ WIDTH_X - 200, 500 }, 100))
    {
        m_game_over_bgm.stop();

        m_house_pos_param.restart();
        m_score = 0;
        return TITLE_SCREEN;
    }

    return GAME_OVER_SCREEN;
}

int Game::optionScreen()
{
    moveBackGroundHouse();

    m_font(m_text_data[U"title"].getString()).drawAt(Scene::Center(), Palette::Black);
    
    SimpleGUI::Slider(m_text_data[U"button"][U"spd"].getString() + U": {:.2f}"_fmt(m_house_spd), m_house_spd, 1.0, 10.0, Vec2{ 200, 40 }, 100, 150);

    if (SimpleGUI::Slider(m_text_data[U"button"][U"volume"].getString() + U": {:.2f}"_fmt(m_volume), m_volume, Vec2{ 200, 100 }, 100, 150))
    {
        m_main_bgm.setVolume(m_volume);
        m_title_bgm.setVolume(m_volume);
        m_game_over_bgm.setVolume(m_volume);
    }

    if (SimpleGUI::Button(m_text_data[U"button"][U"change"].getString(), Vec2{200, 160}))
    {
        for (int i = 0; i < MAX_NUM_HOUSE; ++i)
        {
            m_house_buttons[i].changeDesign();
        }
    }

    if (SimpleGUI::Button(m_text_data[U"button"][U"title"].getString(), Vec2{ WIDTH_X_HALF, 500 }, 100))
    {
        m_house_pos_param.restart();
        return TITLE_SCREEN;
    }

    return OPTION_SCREEN;
}

int Game::ruleScreen()
{
    moveBackGroundHouse();

    m_score_font(m_text_data[U"rule"].getString()).drawAt(Scene::Center(), Palette::Black);

    if (SimpleGUI::Button(m_text_data[U"button"][U"title"].getString(), Vec2{ WIDTH_X_HALF, 500 }, 100))
    {
        m_house_pos_param.restart();
        return TITLE_SCREEN;
    }

    return RULE_SCREEN;
}
