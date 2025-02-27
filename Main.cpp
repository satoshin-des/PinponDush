# include <Siv3D.hpp>

#include "core.h"
#include "game.h"

void Main()
{
    Scene::SetResizeMode(ResizeMode::Keep);     // リサイズモード
    Window::Resize(WIDTH_X, WIDTH_Y);           // リサイズ
    Scene::SetBackground(ColorF{ SKY_BLUE });   // 背景色の設定
    
    Game game;                                  // ゲーム画面
    int game_state = 0;                         // 今のゲームの状態

    Reseed(0);
    
    const Audio m_game_over_bgm{ Audio::Stream, GAME_OVER_BGM, Loop::Yes };
    m_game_over_bgm.play();

    Console << U"ggggggggggggggggggggggggggggg";
    for (const auto& path : EnumResourceFiles())
    {
        Console << path;
    }

    while (System::Update())
    {
        ClearPrint();
        Print << m_game_over_bgm.isPlaying();
        Print << m_game_over_bgm.isEmpty();
        Print << m_game_over_bgm.getVolume();

        switch(game_state)
        {
        case TITLE_SCREEN:
            game_state = game.titleScreen();
            break;

        case GAME_SCREEN:
            game_state = game.mainScreen();
            break;

        case GAME_OVER_SCREEN:
            game_state = game.gameOverScreen();
            break;

        case OPTION_SCREEN:
            game_state = game.optionScreen();
            break;

        case RULE_SCREEN:
            game_state = game.ruleScreen();
            break;
        }
    }
}
