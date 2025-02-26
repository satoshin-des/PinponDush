﻿#ifndef GAME_H
#define GAME_H

#include <Siv3D.hpp>

#include "core.h"
#include "house.h"

class Game
{
private:
	bool m_is_pinponed = false;											// インターフォンが押されたかどうか
	int m_num_house = 2;												// 一度に出現する家の数
	int m_num_dushed_houses = 0;										// ピンポンダッシュに成功した家の数
	int successful_house_index = 0;										// ピンポンダッシュ可能な家の番号
	double m_house_x;													// 家のx座標
	double m_house_spd = 1.0;											// 家の移動速度
	const Font m_font{ 60, Typeface::Heavy };							// リザルト画面に表示するフォント
	const Font m_score_font{ 30, Typeface::Heavy };						// スコアの表示に使用するフォント
	const Texture m_house{ U"🏠"_emoji };								// 家の絵文字
	const Font m_font_MSDF{ FontMethod::MSDF, 100, Typeface::Heavy };	// 成功したかどうかを知らせるフォント
	Stopwatch m_house_pos_param{ StartImmediately::Yes };				// 時間計測
	Stopwatch m_font_size_param{ StartImmediately::Yes };
	House m_house_buttons[100];											// 家
	const String m_title_str = U"ピンポンダッシュ  \n  チャレンジ!!";	// タイトルの表示をするための文字
	const String m_change_house_button_label = U"デザイン変更";			// デザイン変更ボタンのラベル
	const String m_retry_button_label = U"リトライ";					// リトライボタンのラベル
	const String m_option_button = U"設定";								// 設定ボタンのラベル
	const String m_start_button = U"スタート";							// スタートボタンのラベル
	const String m_rule_button = U"ルール";								// ルールボタンのラベル
	const String m_clear_str = U"成功！";								// 成功したときに出す文字列
	const String m_title_button_label = U"タイトル";					// タイトルボタンのラベル
	const String m_failure_str = U"失敗…";								// 失敗したときに出す文字列

	const String m_rule_str = U"ルールは簡単，右から来る家のうちどれかが\n空き家なので，その家をタップしてピンポン\nダッシュを成功させるゲームです．\n　もし失敗したらその時点でゲームオーバー\nです．";

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
