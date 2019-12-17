#pragma once
#ifndef INTELREALSENSEH
#define INTELREALSENSEH


#include "SensorBase.h"
class IntelRealsense :
	public SensorBase
{
public:
	int InitializeSensor();
	int CloseSensor();
	double* GetPointCloud();
};
#endif // !INTELREALSENSEH
