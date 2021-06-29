#pragma once
class Punkt
{
public:
	Punkt();
	Punkt(double x, double y);

	double GetX();
	double GetY();
	
	void SetX(double x);
	void SetY(double y);

private:
	double x, y;
};

