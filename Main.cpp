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

    // Create a texture from an image file
    // const Texture texture{ U"example/windmill.png" };

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

        /*
        // Draw a red transparent circle that follows the mouse cursor
        Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1, 0, 0, 0.5 });

        // When [A] key is down
        if (KeyA.down())
        {
            // Print a randomly selected text
            Print << Sample({ U"Hello!", U"こんにちは", U"你好", U"안녕하세요?" });
        }

        // When [Button] is pushed
        if (SimpleGUI::Button(U"Button", Vec2{ 640, 40 }))
        {
            // Move the coordinates to a random position in the screen
            emojiPos = RandomVec2(Scene::Rect());
        }
        */
    }
}
