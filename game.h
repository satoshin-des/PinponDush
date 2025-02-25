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
	bool m_is_pinponed = false;											// インターフォンが押されたかどうか
	int m_num_house = 2;												// 一度に出現する家の数
	int m_num_dushed_houses = 0;										// ピンポンダッシュに成功した家の数
	int okHouseIndex = 0;												// ピンポンダッシュ可能な家の番号
	double m_house_x;													// 家のx座標
	double m_house_spd = 1.0;											// 家の移動速度
	const Font m_font{ 60, Typeface::Heavy };							// リザルト画面に表示するフォント
	const Font m_score_font{ 30, Typeface::Heavy };						// スコアの表示に使用するフォント
	const Texture m_house{ U"🏠"_emoji };								// 家の絵文字
	const Font m_font_MSDF{ FontMethod::MSDF, 10, Typeface::Heavy };	// 成功したかどうかを知らせるフォント
	Stopwatch stopwatch{ StartImmediately::Yes };						// 時間計測
	Stopwatch test_stopwatch{ StartImmediately::Yes };
	House m_house_buttons[100];											// 家

public:
	void setNGHouse();

	void jumpOutStr(const String str);

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
