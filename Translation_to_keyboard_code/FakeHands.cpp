#include "FakeHands.h"

int FakeHands::CloseSensor() {
	return 0;
}

int FakeHands::InitializeSensor() {

	generator.seed(0);
	nhanddistribution = std::normal_distribution<double>(60, 20);
	nfingerdistribution = std::normal_distribution<double>(0, 2);

	lefthandbasepos = 40;
	righthandbasepos = 80;
	for (int i = 0; i < 5; i++) {
		lefthandfingerpos[i] = lefthandbasepos + i;
		righthandfingerpos[i] = righthandbasepos + i;
	}

	return 0;
}

std::array<MidiNotesNumbers, 10> FakeHands::GetValues(int SongType) {
	std::array<MidiNotesNumbers, 10> retval = { { None, None, None, None, None, None, None, None, None, None } };
	double number = nhanddistribution(generator);
	if (SongType == 1) {
		// finger scales
		if (startedplaying == false) {
			// do we start playing yet?
			
			if (number > 70) {
				startedplaying = true;
				lefthandfingerpos[0] = 36;
				retval[0] = convinttonote(36);
			}
		}
		else {
			// play!
			if (number > 60) {
				if (lefthandfingerpos[0] < 85) {
					lefthandfingerpos[0] += 1;
					retval[0] = convinttonote(lefthandfingerpos[0]);
				}
			}
			// between 40 and 60 is silence
			else if (number < 40 && number > 30) {
				// Oops!  Insert garbage
				number = nhanddistribution(generator);
				retval[0] = convinttonote((int)number);
				// and insert a correct key
				if (lefthandfingerpos[0] < 85) {
					lefthandfingerpos[0] += 1;
					retval[1] = convinttonote(lefthandfingerpos[0]);
				}
			}
			else if (number < 30) {
				// Oops!  Insert garbage
				number = nhanddistribution(generator);
				retval[0] = convinttonote((int)number);
			}

		}
	} // song type 1
	else if (SongType == 2) {
		if (startedplaying == false) {
			// do we start playing yet?

			if (number > 70) {
				startedplaying = true;
				lefthandfingerpos[0] = 36;
				retval[0] = convinttonote(36);
			}

		}
		else {
			// play!
			if (number > 80) {
				// move the left hand
				lefthandbasepos = (int)number;
				number = nfingerdistribution(generator);
				lefthandfingerpos[0] = lefthandbasepos + (int)number;
				retval[0] = convinttonote(lefthandfingerpos[0]);
			}
			else if (number > 50) {
				number = nfingerdistribution(generator);
				lefthandfingerpos[0] = lefthandbasepos + (int)number;
				retval[0] = convinttonote(lefthandfingerpos[0]);
			}
			else if (number > 40) {
				number = nhanddistribution(generator);
				retval[1] = convinttonote((int)number);
				if (number > 75) {
					number = nhanddistribution(generator);
					retval[2] = convinttonote((int)number);
				}
				number = nfingerdistribution(generator);
				lefthandfingerpos[0] = lefthandbasepos + (int)number;
				retval[0] = convinttonote(lefthandfingerpos[0]);
			}
		}
	}//song type 2
	else {
		if (startedplaying == false) {
			// do we start playing yet?
			if (number > 70) {
				startedplaying = true;
			}
		}
		else{
			if (number > 70) {
				//move hands
				number = nhanddistribution(generator);
				lefthandbasepos = (int)number;
				number = nhanddistribution(generator);
				righthandbasepos = (int)number;

				for (int i = 0; i < 5; i++) {
					number = nfingerdistribution(generator);
					lefthandfingerpos[i] = lefthandbasepos + (int)number;
					number = nfingerdistribution(generator);
					righthandfingerpos[i] = righthandbasepos + (int)number;
				}

				int leftfincount = (int)(nhanddistribution(generator) / 20.0);
				for (int i = 0; i < leftfincount; i++) {
					retval[i] = convinttonote(lefthandfingerpos[i]);
				}
				int rightfincount = (int)(nhanddistribution(generator) / 20.0);
				for (int i = 0; i < rightfincount; i++) {
					retval[i + 5] = convinttonote(righthandfingerpos[i]);
				}

			}
			else if (number > 40) {
				for (int i = 0; i < 5; i++) {
					number = nfingerdistribution(generator);
					lefthandfingerpos[i] = lefthandbasepos + (int)number;
					number = nfingerdistribution(generator);
					righthandfingerpos[i] = righthandbasepos + (int)number;
				}

				int leftfincount = (int)(nhanddistribution(generator) / 20.0);
				for (int i = 0; i < leftfincount; i++) {
					retval[i] = convinttonote(lefthandfingerpos[i]);
				}
				int rightfincount = (int)(nhanddistribution(generator) / 20.0);
				for (int i = 0; i < rightfincount; i++) {
					retval[i + 5] = convinttonote(righthandfingerpos[i]);
				}
			}

		}

	}


	return retval;
}

MidiNotesNumbers FakeHands::convinttonote(int in) {
	if (in < 121 && in > 23) {
		return (MidiNotesNumbers)in;
	}
	return None;
}