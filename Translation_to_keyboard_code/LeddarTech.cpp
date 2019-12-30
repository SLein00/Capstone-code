#include "LeddarTech.h"

int LeddarTech::InitializeSensor() {


	Log1.log(Logger::LogLevel::INFO, "Attempting to Initialize Leap Motion");
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
	Log1.log(Logger::LogLevel::INFO, "Attempting to Close out Leap Motion");
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
	Log1.log(Logger::LogLevel::INFO, "Getting values from leap motion");
	std::array<double, 16> retval;
	if (lSensor) {
		lSensor->SetDataMask(LeddarDevice::LdSensor::DM_ALL);
		bool newData = lSensor->GetData();
		if (newData) {
			LeddarConnection::LdResultEchoes* lResultEchoes = lSensor->GetResultEchoes();
			uint32_t lDistanceScale = lResultEchoes->GetDistanceScale();
			uint32_t lAmplitudeScale = lResultEchoes->GetAmplitudeScale();
			lResultEchoes->Lock(LeddarConnection::B_GET);
			std::vector<LeddarConnection::LdEcho>& lEchoes = *(lResultEchoes->GetEchoes());
			for (int i = 0; i < lResultEchoes->GetEchoCount(); i++) {
				retval[i] = ((float)lEchoes[i].mDistance / (float)lDistanceScale);
			}
			lResultEchoes->UnLock(LeddarConnection::B_GET);
		}
	}
	else {
		retval = { {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0} };
	}

	char buffer[1000];
	sprintf(buffer, "Leap Values: [%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]", retval[0], retval[1], retval[2], retval[3], retval[4], retval[5], retval[6], retval[7], retval[8], retval[9], retval[10], retval[11], retval[12], retval[13], retval[14], retval[15]);
	Log1.log(Logger::LogLevel::INFO, buffer);
	return retval;
}

