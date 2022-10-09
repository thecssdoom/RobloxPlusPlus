#pragma once
#include "PVInstance.h"
#include "Enum.h"
#define _USE_MATH_DEFINES
#include <cmath>

class LightingInstance : public Instance
{
public:
	
	LightingInstance(void);
	LightingInstance(const LightingInstance &oinst);
	~LightingInstance(void);
	LightingInstance* clone() const { return 0; }

	virtual std::vector<PROPGRIDITEM> getProperties();
private:
};
