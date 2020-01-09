#include "LeddarTech.h"

int LeddarTech::InitializeSensor() {


	Log1.log(Logger::LogLevel::INFO, "Attempting to Initialize Leddar");
	try {
		std::vector<LeddarConnection::LdConnectionInfo*> lConnectionsList = LeddarConnection::LdLibUsb::GetDeviceList(0x28F1, 0x0400);
		if (lConnectionsList.size() == 0) {
			Log1.log(Logger::LogLevel::WARN, "No connection to Leddar Tech found");
			return -1;
		}
		else {
			lConnectionInfo = lConnectionsList[0];
			LeddarConnection::LdInterfaceUsb* lUsbInterface = new LeddarConnection::LdLibUsb(dynamic_cast<const LeddarConnection::LdConnectionInfoUsb*>(lConnectionInfo));
			lConnection = new LeddarConnection::LdProtocolLeddartechUSB(lConnectionInfo, lUsbInterface);
			lConnection->Connect(); //We can connect to USB to fetch device type
			lSensor = LeddarDevice::LdDeviceFactory::CreateSensor(lConnection);
			Log1.log(Logger::LogLevel::INFO, "Opened Leddar: ", lConnectionsList[0]->GetDisplayName());
			lSensor->GetConstants();
			lSensor->GetConfig();
			lSensor->GetCalib();

		}

	}
	catch (std::exception & e)
	{
		Log1.log(Logger::LogLevel::ERROR, e.what());
		std::cout << "Exception: " << e.what() << std::endl;
	}
	return 0;
}

int LeddarTech::CloseSensor() {
	Log1.log(Logger::LogLevel::INFO, "Attempting to Close out Leddar");
	try {
		if (lSensor) {
			lSensor->Disconnect();
			delete lSensor;
		}
	}
	catch (std::exception & e)
	{
		Log1.log(Logger::LogLevel::ERROR, e.what());
		std::cout << "Exception: " << e.what() << std::endl;
#ifdef _WIN32
		system("pause");
#endif
	}
	return 0;
}

std::array<double,16> LeddarTech::GetValues() {

	
	Log1.log(Logger::LogLevel::INFO, "Getting values from Leddar");
	std::array<double, 16> retval;
	if (lSensor) {
		lSensor->SetDataMask(LeddarDevice::LdSensor::DM_ALL);
		bool newData = lSensor->GetData();
		LeddarUtils::LtTimeUtils::Wait(10);
		newData = lSensor->GetData();
		if (newData) {
			LeddarConnection::LdResultEchoes* lResultEchoes = lSensor->GetResultEchoes();
			uint32_t lDistanceScale = lResultEchoes->GetDistanceScale();
			uint32_t lAmplitudeScale = lResultEchoes->GetAmplitudeScale();
			char buffer[1000]; 
			//sprintf(buffer, "Leddar distance scale = %f", lDistanceScale);
			//Log1.log(Logger::LogLevel::INFO, buffer);
			lResultEchoes->Lock(LeddarConnection::B_GET);
			std::vector<LeddarConnection::LdEcho>& lEchoes = *(lResultEchoes->GetEchoes());
			for (int i = 0; i < lResultEchoes->GetEchoCount() && i < 16; i++) {
				retval[i] = ((float)lEchoes[i].mDistance / (float)lDistanceScale);
			}
			lResultEchoes->UnLock(LeddarConnection::B_GET);
		}
		else {
			Log1.log(Logger::LogLevel::WARN, "No new data in Leddar, retval might be unreliable.");
		}
	}
	else {
		Log1.log(Logger::LogLevel::WARN, "No leddar sensor, returning default values");
		retval = { {.1856997, .1856997, .1856997, .1856997, .1856997,.1856997,1 ,.9996 ,.9996 , 1, .1856997,.1856997,.1856997,.1856997, .1856997, .1856997} };
		//Need to change to actual distance values that will output keys
		//.5088 should = Middle C# (Cs5) in side position (element 7)
		//.497770 should = Middle C (C5) in side position (element 8)
		
	}

	char buffer[2000];
	sprintf(buffer, "Leddar Values: [%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f,%6.3f]", retval[0], retval[1], retval[2], retval[3], retval[4], retval[5], retval[6], retval[7], retval[8], retval[9], retval[10], retval[11], retval[12], retval[13], retval[14], retval[15]);
	Log1.log(Logger::LogLevel::INFO, buffer);
	return retval;

}

