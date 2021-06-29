#include "Anzeige.h"

Anzeige::Anzeige()
{
}

void Anzeige::Laenge(Linie& l)
{
	double length = abs(sqrt(pow(_AP_L_DIFF_X(l), 2) + pow(_AP_L_DIFF_Y(l), 2)));

	std::wcout << "Name: " << l.GetName() << _T(" -+- Laenge: ") << length << std::endl;
}

void Anzeige::Flaeche(Kreis& k)
{
	double area = (pow(k.GetRadius(), 2) * M_PI);

	std::wcout << "Name: " << k.GetName() << _T(" -+- Flaeche: ") << area << std::endl;
}

void Anzeige::Flaeche(Rechteck& r)
{
	double area = 0;
	auto p1 = r.GetP1();
	auto p2 = r.GetP2();
	auto p3 = r.GetP3();
	auto p4 = r.GetP4();

	// Lambda Funktion zum Prüfen auf Überschneidung.
	auto fnc_checkIntersection = [](Punkt p1, Punkt p2, Punkt p3, Punkt p4) -> IntersectionHelper {
		IntersectionHelper helper = { 0, 0, false, false };

		double x1 = p1.GetX();
		double x2 = p2.GetX();
		double x3 = p3.GetX();
		double x4 = p4.GetX();

		double y1 = p1.GetY();
		double y2 = p2.GetY();
		double y3 = p3.GetY();
		double y4 = p4.GetY();

		double denominator = (((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)));

		if (denominator == 0) {
			return helper;
		}

		double t = ((((x1 - x3) * (y3 - y4)) - ((y1 - y3) * (x3 - x4))) / denominator);
		double u = ((((x2 - x1) * (y1 - y3)) - ((y2 - y1) * (x1 - x3))) / denominator);

		if ((0.0 < t && t < 1.0) && (0.0 < u && u < 1.0)) {
			double newX = (x1 + (t * (x2 - x1)));
			double newY = (y1 + (t * (y2 - y1)));

			helper.hasIntersection = true;
			helper.x = newX;
			helper.y = newY;

			return helper;
		}

		return helper;
	};

	// Prüfe ob Polygon sich überschneidet.
	// P1 x P2 und P3 x P4.
	auto sIntersection = fnc_checkIntersection(p1, p2, p3, p4);
	if (!sIntersection.hasIntersection) {
		// P2 x P3 und P4 x P1.
		sIntersection = fnc_checkIntersection(p2, p3, p4, p1);
		if (sIntersection.hasIntersection) {
			sIntersection.isRotated = true;
		}
	}

	if (!sIntersection.hasIntersection) {
		// Wenn keine Überschneidung vorhanden, benutze Kreuzprodukte um Fläche zu errechnen.
		area = ((p1.GetX() * p2.GetY()) - (p1.GetY() * p2.GetX()));
		area += ((p2.GetX() * p3.GetY()) - (p2.GetY() * p3.GetX()));
		area += ((p3.GetX() * p4.GetY()) - (p3.GetY() * p4.GetX()));
		area += ((p4.GetX() * p1.GetY()) - (p4.GetY() * p1.GetX()));
		
		// Durch zwei teilen nicht vergessen.
		area = abs(area / 2);
	}
	else{
		// Lambda Funktion zum Holen der Disanz zwischen zwei Punkten.
		auto fnc_distance = [](Punkt a, Punkt b) -> double {
			return abs(sqrt(pow(a.GetX() - b.GetX(), 2) + pow(a.GetY() - b.GetY(), 2)));
		};

		// Lambda Funktion zum Berechnen der Fläche eines Dreiecks nach Heron's Formel.
		auto fnc_calcArea = [](double a, double b, double c) -> double {

			// Kleiner Fehler hinzufügen, damit Ergebnis nicht 0 oder NAN wird.
			if (a > b && a > c) {
				a -= 0.001;
			}
			else if (b > a && b > c) {
				b -= 0.001;
			}
			else {
				c -= 0.001;
			}

			double s = 0.5 * (a + b + c);

			return sqrt(s * (s - a) * (s - b) * (s - c));
		};

		Punkt pX = Punkt(sIntersection.x, sIntersection.y);

		if (!sIntersection.isRotated) {
			// ABX, CDX.
			double lAB = fnc_distance(p1, p2);
			double lAX = fnc_distance(p1, pX);
			double lBX = fnc_distance(p2, pX);

			double lCD = fnc_distance(p3, p4);
			double lCX = fnc_distance(p3, pX);
			double lDX = fnc_distance(p4, pX);

			area = fnc_calcArea(lAB, lAX, lBX);
			area += fnc_calcArea(lCD, lCX, lDX);
		}
		else {
			// AXD, BCX.
			double lAD = fnc_distance(p1, p4);
			double lAX = fnc_distance(p1, pX);
			double lDX = fnc_distance(p4, pX);

			double lBC = fnc_distance(p2, p3);
			double lBX = fnc_distance(p2, pX);
			double lCX = fnc_distance(p3, pX);

			area = fnc_calcArea(lAD, lAX, lDX);
			area += fnc_calcArea(lBC, lBX, lCX);
		}
	}

	std::wcout << "Name: " << r.GetName() << _T(" -+- Flaeche: ") << area << std::endl;
}
