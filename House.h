#ifndef HOUSE_H
#define HOUSE_H

#include <Siv3D.hpp>

#include "core.h"

class House
{
private:
	int m_house_label;
	double m_x;
	double m_y;
	Texture m_house{ U"🏠"_emoji };

public:
	void setDesign();

	/// <summary>
	/// 家を表示する場所を設定する
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	void setPos(const double x, const double y);

	/// <summary>
	/// 家がクリックされたかどうかを判定する関数
	/// </summary>
	/// <returns>クリックされたらtrue，そうじゃなければfalse</returns>
	bool isClicked(const bool canClick);
};

#endif // !HOUSE_H
