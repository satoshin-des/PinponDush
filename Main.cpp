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
    int num_dushed_houses = 0;                  // ピンポンダッシュに成功した家の数

    game.setNumHouse(2);

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
        }
    }
}
