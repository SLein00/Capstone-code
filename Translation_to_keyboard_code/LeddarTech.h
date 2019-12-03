#pragma once
#include "SensorBase.h"
#include <array>

class LeddarTech :
	public SensorBase
{
public:
	int InitializeSensor();
	int CloseSensor();
	std::array<double, 16> GetValues();
};

