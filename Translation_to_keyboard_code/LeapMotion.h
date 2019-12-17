#pragma once
#ifndef LEAPMOTIONH
#define LEAPMOTIONH


#include "SensorBase.h"
#include <array>
#include "translationtokbd.h"

class LeapMotion :
	public SensorBase
{
public:
	int InitializeSensor();

	int CloseSensor();

	std::array<position,10> GetFingerPositions();

};
#endif // !LEAPMOTIONH
