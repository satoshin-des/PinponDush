#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <vector>
#include <random>
#include <Siv3D.hpp>
#include "core.h"
#include "house.h"

static std::mt19937_64 mt64((unsigned int)time(nullptr));

class Game
{
private:
	int m_num_dushed_house = 0;
	int m_time_count = WIDTH_X - HOUSE_SIZE;
	int m_num_house = 2;
	int ngHouseIndex = 0;
	const Font m_font{ 60 };
	const Texture m_house{ U"🏠"_emoji };

	std::vector<House> m_house_buttons;

public:
	House house;

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

	int mainScreen();
};

#endif // !GAME_H
