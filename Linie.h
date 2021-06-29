#pragma once

#include "GeoForm.h"
#include "Anzeige.h"
#include "Punkt.h"

class Anzeige;
class Linie : public GeoForm
{
public:
	Linie();
	Linie(Punkt p1, Punkt p2, LPCWSTR name = _T(_AP_STR_UNDEFINED));

	Punkt GetP1();
	Punkt GetP2();
	LPCWSTR GetName();

	void SetP1(Punkt p1);
	void SetP2(Punkt p2);
	void SetName(LPCWSTR name);

	void Zeichne(HDC& hdc, PAINTSTRUCT& ps);
	void RufeAnzeige();

private:
	std::shared_ptr<Anzeige> anz;
	Punkt p1, p2;
	LPCWSTR name;
};

