#include "LeapMotion.h"

int LeapMotion::InitializeSensor() {
	return 0;
}

int LeapMotion::CloseSensor() {
	return 0;
}

std::array<position, 10> LeapMotion::GetFingerPositions() {
	position foo1;
	foo1.X = -32.75;
	foo1.Y = 46.386;
	foo1.Z = 15.132;

	position foo2;
	foo2.X = 3.55;
	foo2.Y = 20;
	foo2.Z = 0;

	position foo3;
	foo3.X = .55;
	foo3.Y = 30;
	foo3.Z = 0;

	position foo4;
	foo4.X = 19.75;
	foo4.Y = 27.1;
	foo4.Z = 0;

	position foo5;
	foo5.X = 14.75;
	foo5.Y = 28.1;
	foo5.Z = 0;

	position foo6;
	foo6.X = -4.75;
	foo6.Y = 47.446;
	foo6.Z = 14.779;

	position foo7;
	foo7.X = -75;
	foo7.Y = 49.215;
	foo7.Z = 12.304;

	position foo8;
	foo8.X = 5.25;
	foo8.Y = 58.8;
	foo8.Z = -3.55;

	position foo9;
	foo9.X = 8.25;
	foo9.Y = 58.5;
	foo9.Z = 3.45;

	position foo10;
	foo10.X = 20.25;
	foo10.Y = 58.5;
	foo10.Z = -1.55;

	std::array<position, 10> retval = { {foo1,foo2,foo3,foo4,foo5,foo6,foo7,foo8,foo9,foo10} };
	return retval;

}