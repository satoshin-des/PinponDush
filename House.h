#ifndef HOUSE_H
#define HOUSE_H

#include <Siv3D.hpp>
#include "core.h"

class House
{
private:
	double m_x;
	double m_y;
	const Texture m_house{ U"🏠"_emoji };

public:
	void setPos(const double x, const double y);
	bool isClicked();
};

#endif // !HOUSE_H
