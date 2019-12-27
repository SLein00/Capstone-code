#include "LeddarTech.h"

int LeddarTech::InitializeSensor() {
	Log1.log(Logger::LogLevel::INFO, "Attempting to Initialize Leap Motion");
	return 0;
}

int LeddarTech::CloseSensor() {
	return 0;
	Log1.log(Logger::LogLevel::INFO, "Attempting to Close out Leap Motion");
}

std::array<double,16> LeddarTech::GetValues() {
	Log1.log(Logger::LogLevel::INFO, "Getting values from leap motion");
	std::array<double, 16> retval = { {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0} };

	char buffer[1000];
	sprintf(buffer, "Leap Values: [%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]", retval[0], retval[1], retval[2], retval[3], retval[4], retval[5], retval[6], retval[7], retval[8], retval[9], retval[10], retval[11], retval[12], retval[13], retval[14], retval[15]);
	Log1.log(Logger::LogLevel::INFO, buffer);
	return retval;
}

