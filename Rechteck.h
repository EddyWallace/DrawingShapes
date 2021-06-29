#pragma once

#include "GeoForm.h"
#include "Punkt.h"
#include "Anzeige.h"

class Anzeige;
class Rechteck : public GeoForm
{
public:
	Rechteck();
	Rechteck(Punkt p1, Punkt p2, Punkt p3, Punkt p4, LPCWSTR name = _T(_AP_STR_UNDEFINED));

	void SetP1(Punkt p1);
	void SetP2(Punkt p2);
	void SetP3(Punkt p3);
	void SetP4(Punkt p4);
	void SetName(LPCWSTR name);

	Punkt GetP1();
	Punkt GetP2();
	Punkt GetP3();
	Punkt GetP4();
	LPCWSTR GetName();

	void Zeichne(HDC& hdc, PAINTSTRUCT& ps);
	void RufeAnzeige();

private:
	Punkt p1, p2, p3, p4;
	std::shared_ptr<Anzeige> anz;
	LPCWSTR name;
};

