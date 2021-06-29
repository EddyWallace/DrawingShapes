#include "Rechteck.h"

Rechteck::Rechteck() : Rechteck(Punkt(0, 0), Punkt(0, 0), Punkt(0, 0), Punkt(0, 0))
{
}

Rechteck::Rechteck(Punkt p1, Punkt p2, Punkt p3, Punkt p4, LPCWSTR name)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	this->name = name;
	this->anz = std::make_shared<Anzeige>(Anzeige());
}

void Rechteck::SetP1(Punkt p1)
{
	this->p1 = p1;
}

void Rechteck::SetP2(Punkt p2)
{
	this->p2 = p2;
}

void Rechteck::SetP3(Punkt p3)
{
	this->p3 = p3;
}

void Rechteck::SetP4(Punkt p4)
{
	this->p4 = p4;
}

void Rechteck::SetName(LPCWSTR name)
{
	this->name = name;
}

Punkt Rechteck::GetP1()
{
	return this->p1;
}

Punkt Rechteck::GetP2()
{
	return this->p2;
}

Punkt Rechteck::GetP3()
{
	return this->p3;
}

Punkt Rechteck::GetP4()
{
	return this->p4;
}

LPCWSTR Rechteck::GetName()
{
	return this->name;
}

void Rechteck::Zeichne(HDC& hdc, PAINTSTRUCT& ps)
{
	POINT* apts = new POINT[4]{
		{ (LONG)p1.GetX(), (LONG)p1.GetY() },
		{ (LONG)p2.GetX(), (LONG)p2.GetY() },
		{ (LONG)p3.GetX(), (LONG)p3.GetY() },
		{ (LONG)p4.GetX(), (LONG)p4.GetY() }
	};

	Polygon(hdc, apts, 4);
}

void Rechteck::RufeAnzeige()
{
	this->anz->Flaeche(*this);
}
