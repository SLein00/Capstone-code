#pragma once
#include "SensorBase.h"
class IntelRealsense :
	public SensorBase
{
public:
	int InitializeSensor();
	int CloseSensor();
	double* GetPointCloud();
};

