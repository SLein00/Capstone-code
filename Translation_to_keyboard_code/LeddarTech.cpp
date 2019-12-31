#include "LeddarTech.h"

int LeddarTech::InitializeSensor() {

	return 0;
}

int LeddarTech::CloseSensor() {
	return 0;

}

std::array<double,16> LeddarTech::GetValues() {
	std::array<double, 16> retval = { {.17005954, .17005954, .17005954, .17005954, .17005954,.17005954,.17005954,.17005954,.17005954, .17005954, .17005954,.17005954,.17005954,.17005954, .17005954, .17005954} };
	return retval;
	//.17005954 should result in Cs2 and came from the squareroot of ((-.45)^2 + (17)^2) divided by 100 (convert to meters)
}

