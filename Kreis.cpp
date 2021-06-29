#include "Kreis.h"

Kreis::Kreis() : Kreis(Punkt(0, 0), 0)
{
}

Kreis::Kreis(Punkt punkt, double radius, LPCWSTR name)
{
	this->anz = std::make_shared<Anzeige>(Anzeige());
	this->punkt = punkt;
	this->radius = radius;
	this->name = name;
}

void Kreis::SetPunkt(Punkt punkt)
{
	this->punkt = punkt;
}

void Kreis::SetRadius(double radius)
{
	this->radius = radius;
}

void Kreis::SetName(LPCWSTR name)
{
	this->name = name;
}

Punkt Kreis::GetPunkt()
{
	return this->punkt;
}

double Kreis::GetRadius()
{
	return this->radius;
}

LPCWSTR Kreis::GetName()
{
	return this->name;
}

void Kreis::Zeichne(HDC& hdc, PAINTSTRUCT& ps)
{
	int x = (int)this->punkt.GetX();
	int y = (int)this->punkt.GetY();
	int r = (int)this->radius;

	Ellipse(hdc, x-r, y-r, x+r, y+r);
}

void Kreis::RufeAnzeige()
{
	this->anz->Flaeche(*this);
}
