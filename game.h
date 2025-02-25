#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <random>
#include <Siv3D.hpp>
#include "core.h"
#include "house.h"

static std::mt19937_64 mt64((unsigned int)time(nullptr));

class Game
{
private:
	bool m_is_pinponed = false;
	int m_time_count = WIDTH_X - HOUSE_SIZE;
	int m_num_house = 2;
	int m_num_dushed_houses = 0;
	int okHouseIndex = 0;
	double m_house_spd = 3.0;
	const Font m_font{ 60 };
	const Texture m_house{ U"🏠"_emoji };

	House m_house_buttons[100];

public:
	/// <summary>
	/// ピンポンダッシュ可能な家の数
	/// </summary>
	/// <param name="n">個数</param>
	void setNumHouse(const int n);
	
	void setNGHouse();

	/// <summary>
	/// タイトル画面の描画
	/// </summary>
	/// <returns>ゲーム状態</returns>
	int titleScreen();

	/// <summary>
	/// メインのゲーム画面の描画
	/// </summary>
	/// <returns>ゲーム状態</returns>
	int mainScreen();

	/// <summary>
	/// ゲームオーバー画面の描画
	/// </summary>
	/// <returns>ゲーム状態</returns>
	int gameOverScreen();

	int optionScreen();
};

#endif // !GAME_H
