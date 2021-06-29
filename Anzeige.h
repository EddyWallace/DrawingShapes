#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>

#include "Punkt.h"
#include "Linie.h"
#include "Kreis.h"
#include "Rechteck.h"

#define _AP_L_DIFF_X(l) (l.GetP1().GetX() - l.GetP2().GetX())
#define _AP_L_DIFF_Y(l) (l.GetP1().GetY() - l.GetP2().GetY())

class Linie;
class Kreis;
class Rechteck;
class Anzeige
{
public:
	Anzeige();

	void Laenge(Linie& l);
	void Flaeche(Kreis& k);
	void Flaeche(Rechteck& r);

private:
	struct IntersectionHelper {
		double x, y;
		bool hasIntersection;
		bool isRotated;
	};
};

