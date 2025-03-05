#ifndef GAME_H
#define GAME_H

#include <Siv3D.hpp>

#include "core.h"
#include "house.h"

/// <summary>
/// ゲーム画面
/// </summary>
class Game
{
private:
	bool m_is_pinponed = false;												// インターフォンが押されたかどうか
	int m_num_house = 2;													// 一度に出現する家の数
	int m_score = 0;														// ピンポンダッシュに成功した家の数
	int successful_house_index = 0;											// ピンポンダッシュ可能な家の番号
	double m_volume = 1.0;													// 音楽のボリューム
	double m_house_x;														// 家のx座標
	double m_house_spd = 1.0;												// 家の移動速度
	const Font m_font{ 60, Typeface::Heavy };								// リザルト画面に表示するフォント
	const Font m_score_font{ 30, Typeface::Heavy };							// スコアの表示に使用するフォント
	const Font m_font_MSDF{ FontMethod::MSDF, 100, Typeface::Heavy };		// 成功したかどうかを知らせるフォント
	Stopwatch m_house_pos_param{ StartImmediately::Yes };					// 家の動きをつかさどるパラメタ
	Stopwatch m_font_size_param{ StartImmediately::No };					// 成功／失敗の文字を司るパラメタ
	House m_house_buttons[MAX_NUM_HOUSE];									// 家
	const Audio m_game_over_bgm{ Audio::Stream, GAME_OVER_BGM, Loop::Yes };	// リザルト画面のbgm
	const Audio m_title_bgm{ Audio::Stream, TITLE_BGM, Loop::Yes };			// タイトル画面のbgm
	const Audio m_main_bgm{ Audio::Stream, MAIN_BGM, Loop::Yes };			// ゲーム画面のbgm
	const JSON m_text_data = JSON::Load(U"resources/engine/text_data.json");// ゲームに使うテキストをまとめてあるjsonファイル

	/// <summary>
	/// ピンポンダッシュに成功する家のインデックスを設定する
	/// </summary>
	void setSuccessfulHouse();

	/// <summary>
	/// 家の数を増やす
	/// </summary>
	void incrHouse();

	/// <summary>
	/// ピンポンダッシュに失敗したかどうか
	/// </summary>
	/// <returns>失敗したらtrue，成功したらfalse</returns>
	bool failurePinponDush();

	/// <summary>
	/// 背景の家を動かす
	/// </summary>
	void moveBackGroundHouse();

	/// <summary>
	/// 文字列が飛び出してくる関数
	/// </summary>
	/// <param name="str">飛び出させたい文字列</param>
	void jumpOutStr(const String str);

public:
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

	/// <summary>
	/// 設定場面の描画
	/// </summary>
	/// <returns>ゲーム状態</returns>
	int optionScreen();

	/// <summary>
	/// ルールの描画
	/// </summary>
	/// <returns>ゲーム状態</returns>
	int ruleScreen();
};

#endif // !GAME_H
