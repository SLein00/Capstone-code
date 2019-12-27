#pragma once
#ifndef LEDDARTECHH
#define LEDDARTECHH


#include "SensorBase.h"
#include <array>
#include "Logger.h"

extern Logger Log1;

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
