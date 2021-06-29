#include "Linie.h"

Linie::Linie() : Linie::Linie(Punkt(0, 0), Punkt(0, 0))
{
}

Linie::Linie(Punkt p1, Punkt p2, LPCWSTR name)
{
	this->anz = std::make_shared<Anzeige>(Anzeige());
	this->p1 = p1;
	this->p2 = p2;
	this->name = name;
}

Punkt Linie::GetP1()
{
	return this->p1;
}

Punkt Linie::GetP2()
{
	return this->p2;
}

LPCWSTR Linie::GetName()
{
	return this->name;
}

void Linie::SetP1(Punkt p1)
{
	this->p1 = p1;
}

void Linie::SetP2(Punkt p2)
{
	this->p2 = p2;
}

void Linie::SetName(LPCWSTR name)
{
	this->name = name;
}

void Linie::RufeAnzeige()
{
	this->anz->Laenge(*this);
}

void Linie::Zeichne(HDC& hdc, PAINTSTRUCT& ps)
{
	MoveToEx(hdc, (int)this->p1.GetX(), (int)this->p1.GetY(), NULL);
	LineTo(hdc, (int)this->p2.GetX(), (int)this->p2.GetY());
}
