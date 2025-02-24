#ifndef GAME_H
#define GAME_H

#include <Siv3D.hpp>
#include "core.h"
#include "house.h"

class Game
{
private:
	int m_num_dushed_house = 0;
	int m_time_count = WIDTH_X - 150;
	const Font m_font{ 60 };
	const Texture m_house{ U"🏠"_emoji };

public:
	House house;

	/// <summary>
	/// タイトル画面の描画
	/// </summary>
	/// <returns>ゲーム状態</returns>
	int titleScreen();

	int mainScreen();
};

#endif // !GAME_H
