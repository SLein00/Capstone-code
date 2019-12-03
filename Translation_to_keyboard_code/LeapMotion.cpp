#include "LeapMotion.h"

int LeapMotion::InitializeSensor() {
	return 0;
}

int LeapMotion::CloseSensor() {
	return 0;
}

std::array<position, 10> LeapMotion::GetFingerPositions() {
	position foo;
	foo.X = 1.0;
	foo.Y = 2.0;
	foo.Z = 3.0;

	std::array<position, 10> retval = { {foo,foo,foo,foo,foo,foo,foo,foo,foo,foo} };
	return retval;

}