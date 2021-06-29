#include "Punkt.h"

Punkt::Punkt() : Punkt::Punkt(0, 0)
{
}

Punkt::Punkt(double x, double y)
{
	this->x = x;
	this->y = y;
}

double Punkt::GetX()
{
	return this->x;
}

double Punkt::GetY()
{
	return this->y;
}

void Punkt::SetX(double x)
{
	this->x = x;
}

void Punkt::SetY(double y)
{
	this->y = y;
}
