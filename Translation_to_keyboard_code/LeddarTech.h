#pragma once
#ifndef LEDDARTECHH
#define LEDDARTECHH


#include "SensorBase.h"
#include <array>
#include "Logger.h"
#include <vector>

// start copying from leddar
#include <iostream>
#include <iomanip>
#include "LdConnectionFactory.h"
#include "LdDeviceFactory.h"
#include "LdPropertyIds.h"
#include "LdResultEchoes.h"
#include "LdSensorVu8.h"
#include "LdSpiFTDI.h"
//#include "LdLjrRecorder.h"
#include "LdRecordPlayer.h"
//USB
#include "LdLibUsb.h"
#include "LdProtocolLeddartechUSB.h"
////Utils
//#include "LtExceptions.h"
//#include "LtKeyboardUtils.h"
//#include "LtStringUtils.h"
//#include "LtTimeUtils.h"


extern Logger Log1;

class LeddarTech :
	public SensorBase
{
public:
	int InitializeSensor();
	int CloseSensor();
	std::array<double, 16> GetValues();
	std::array<double, 16> CorrectionFactor = { {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0} };

private:
	LeddarConnection::LdConnectionInfo* lConnectionInfo = nullptr;
	LeddarConnection::LdConnection* lConnection = nullptr;
	LeddarDevice::LdSensor* lSensor = nullptr;
};
#endif // !LEDDARTECHH
