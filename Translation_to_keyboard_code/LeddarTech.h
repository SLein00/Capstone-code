#pragma once
#ifndef LEDDARTECHH
#define LEDDARTECHH


#include "SensorBase.h"
#include <array>
#include "Logger.h"
#include <vector>
#include <string>

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
#include "LtTimeUtils.h"


extern Logger Log1;

class LeddarTech :
	public SensorBase
{
public:
	int InitializeSensor();
	int CloseSensor();
	std::array<double, 16> GetValues();
	std::array<double, 16> CorrectionFactor = { {-0.249975246258358,-0.186651358160941,-0.194782136469763,-0.193209159420895,-0.165429551365639,-0.172604021355511,-0.158419862304782,-0.116666462906386,-0.114666462906386,-0.178991290876211,-0.176032592784083,-0.16985812279421,-0.182637730849466,-0.170353565041192,-0.207079929589512,-0.320689531972643
} }; //Meters {0.152,0.281,0.495,0.408,0.180,0.183,0.176,0.178,0.174,0.185,0.207,0.407,0.456,0.651,0.693,0.807}
	//Side  {-0.0312987635964963,-0.128228794572704,-0.311130500410793,-0.212187032742012,-0.157498233180454,-0.151092034399389,-0.149732766093701,-0.150526946362602,-0.149526946362602,-0.154732766093701,-0.156092034399389,-0.161498233180454,-0.178787032742012,-0.346530500410793,-0.292828794572704,-0.368498763596496
	// {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}
private:
	LeddarConnection::LdConnectionInfo* lConnectionInfo = nullptr;
	LeddarConnection::LdConnection* lConnection = nullptr;
	LeddarDevice::LdSensor* lSensor = nullptr;
};
#endif // !LEDDARTECHH
