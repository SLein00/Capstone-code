#pragma once
#ifndef LEDDARTECHH
#define LEDDARTECHH


#include "SensorBase.h"
#include <array>

class LeddarTech :
	public SensorBase
{
public:
	int InitializeSensor();
	int CloseSensor();
	std::array<double, 16> GetValues();
	std::array<double, 16> CorrectionFactor = { {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0} };
};
#endif // !LEDDARTECHH
