#include "LeapMotion.h"

int LeapMotion::InitializeSensor() {
	Log1.log(Logger::LogLevel::INFO, "Initializing Leap");
	return 0;

}

int LeapMotion::CloseSensor() {
	Log1.log(Logger::LogLevel::INFO, "Closing Leap");
	return 0;
}

std::array<position, 10> LeapMotion::GetFingerPositions() {
	Log1.log(Logger::LogLevel::INFO, "Getting Leap finger position data");
	position foo1;//Side
	foo1.X = -32.75;
	foo1.Y = 46.386;
	foo1.Z = 15.132;

	position foo2;//Side
	foo2.X = 3.55;
	foo2.Y = 20;
	foo2.Z = 0;

	position foo3;//Side
	foo3.X = .55;
	foo3.Y = 30;
	foo3.Z = 0;

	position foo4;//Front
	foo4.X = 19.75;
	foo4.Y = 27.1;
	foo4.Z = 0;

	position foo5;//Front
	foo5.X = 14.75;
	foo5.Y = 28.1;
	foo5.Z = 0;

	position foo6;//Webcam
	foo6.X = -4.75;
	foo6.Y = 47.446;
	foo6.Z = 14.779;
	
	position foo7;//Webcam
	foo7.X = -.75;
	foo7.Y = 49.215;
	foo7.Z = 12.304;

	position foo8;//Overhead
	foo8.X = 5.25;
	foo8.Y = 58.8;
	foo8.Z = -3.55;

	position foo9;//Overhead
	foo9.X = 8.25;
	foo9.Y = 58.5;
	foo9.Z = 3.45;

	position foo10;//Overhead
	foo10.X = 20.25;
	foo10.Y = 58.5;
	foo10.Z = -1.55;

	std::array<position, 10> retval = { {foo1,foo2,foo3,foo4,foo5,foo6,foo7,foo8,foo9,foo10} };

	position PreCoordinates;
	std::array<position, 10> Coordinates;
	for (int idx = 0; idx < 10; idx++) {
		PreCoordinates = retval[idx];
		Coordinates[idx].X = PreCoordinates.X;
		Coordinates[idx].Y = PreCoordinates.Y;
		Coordinates[idx].Z = PreCoordinates.Z;
		char buffer[1000];
		sprintf(buffer, "Leap Finger %d = [ X = %0.3f, Y = %0.3f, Z = %0.3f ]", idx, Coordinates[idx].X, Coordinates[idx].Y, Coordinates[idx].Z);

		Log1.log(Logger::LogLevel::DEBUG, buffer);
	}
	return retval;

}