#include <stdlib.h>
#include <time.h>

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

    srand(static_cast<unsigned int>(time(nullptr)));
    Reseed(0);
    
	game.preloadFonts();

    while (System::Update())
    {
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
