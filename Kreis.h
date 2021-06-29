#pragma once

#include "GeoForm.h"
#include "Anzeige.h"
#include "Punkt.h"

class Anzeige;
class Kreis : public GeoForm
{
public:
	Kreis();
	Kreis(Punkt punkt, double radius, LPCWSTR name = _T(_AP_STR_UNDEFINED));

	void SetPunkt(Punkt punkt);
	void SetRadius(double radius);
	void SetName(LPCWSTR name);

	Punkt GetPunkt();
	double GetRadius();
	LPCWSTR GetName();

	void Zeichne(HDC& hdc, PAINTSTRUCT& ps);
	void RufeAnzeige();

private:
	LPCWSTR name;
	double radius;
	Punkt punkt;
	std::shared_ptr<Anzeige> anz;
};

