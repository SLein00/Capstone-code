#pragma once
#ifndef SENSORBASEH
#define SENSORBASEH


class SensorBase
{
	virtual int InitializeSensor();

	virtual int CloseSensor();

};

#endif // !SENSORBASEH