#pragma once
#ifndef INTELREALSENSEH
#define INTELREALSENSEH

#include "SensorBase.h"
#include <iostream>
#include "librealsense2/rs.hpp"
#include "Logger.h"

extern Logger Log1;

class IntelRealsense :
	public SensorBase
{
public:
	int InitializeSensor();
	int CloseSensor();
	double* GetPointCloud();

private:
		rs2::pipeline p;
};
#endif // !INTELREALSENSEH
