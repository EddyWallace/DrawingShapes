#pragma once

#include "framework.h"

#define _AP_STR_UNDEFINED "UNDEFINED"
#define _AP_GEOFORM_TO_SHARED_PTR(clazz, obj) (std::make_shared<clazz>(obj))

class GeoForm
{
public:
	virtual void RufeAnzeige() = 0;
	virtual void Zeichne(HDC& hdc, PAINTSTRUCT& ps) = 0;
};

