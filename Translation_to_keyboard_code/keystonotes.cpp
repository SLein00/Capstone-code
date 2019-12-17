#include "keystonotes.h"


MidiNotesNumbers Keyboard::notes( double finalfingerposX, double finalfingerposY, double finalfingerposZ) {
	MidiNotesNumbers note = None;
	/*if (67.2 < finalfingerposX < 69.5 && 0 < finalfingerposY < 15.1 && 0 < finalfingerposZ < 1.5) {
		note = C6;
	}
	else if(64.8 < finalfingerposX < 67.1 && 0 < finalfingerposY < 5 && 0 < finalfingerposZ < 1.5){
		note = B5;
	}
	else if (65.8 < finalfingerposX < 67.1 && 5.1 < finalfingerposY < 15.1 && 0 < finalfingerposZ < 1.5) {
		note = B5;
	}
	else if (64.4 < finalfingerposX < 65.7 && 5.1 < finalfingerposY < 15.1 && 0 < finalfingerposZ < 1.5) {
		note = As5;
	}
	else {
		note = None;
	}*/
	//Measurements are in cm
	if (0 < finalfingerposZ < 1.5) {//Z is in playing range
		if (0 < finalfingerposY <= 5.08) {//Y is in the bottom section of white notes
			if (finalfingerposX < 0) {//
				return note;
			}
			else if (finalfingerposX <= 2.4) {
				note = C2;
			}
			else if (finalfingerposX <= 4.8) {
				note = D2;
			}
			else if (finalfingerposX <= 7.2) {
				note = E2;
			}
			else if (finalfingerposX <= 9.6) {
				note = F2;
			}
			else if (finalfingerposX <= 12) {
				note = G2;
			}
			else if (finalfingerposX <= 14.4) {
				note = A2;
			}
			else if (finalfingerposX <= 16.8) {
				note = B2;
			}
			else if (finalfingerposX <= 19.2) {
				note = C3;
			}
			else if (finalfingerposX <= 21.6) {
				note = D3;
			}
			else if (finalfingerposX <= 24) {
				note = E3;
			}
			else if (finalfingerposX <= 26.4) {
				note = F3;
			}
			else if (finalfingerposX <= 28.8) {
				note = G3;
			}
			else if (finalfingerposX <= 31.2) {
				note = A3;
			}
			else if (finalfingerposX <= 33.6) {
				note = B3;
			}
			else if (finalfingerposX <= 36) {
				note = C4;
			}
			else if (finalfingerposX <= 38.4) {
				note = D4;
			}
			else if (finalfingerposX <= 40.8) {
				note = E4;
			}
			else if (finalfingerposX <= 43.2) {
				note = F4;
			}
			else if (finalfingerposX <= 45.6) {
				note = G4;
			}
			else if (finalfingerposX <= 48) {
				note = A4;
			}
			else if (finalfingerposX <= 50.4) {
				note = B4;
			}
			else if (finalfingerposX <= 52.8) {
				note = C5;
			}
			else if (finalfingerposX <= 55.2) {
				note = D5;
			}
			else if (finalfingerposX <= 57.6) {
				note = E5;
			}
			else if (finalfingerposX <= 60) {
				note = F5;
			}
			else if (finalfingerposX <= 62.4) {
				note = G5;
			}
			else if (finalfingerposX <= 64.8) {
				note = A5;
			}
			else if (finalfingerposX <= 67.2) {
				note = B5;
			}
			else if (finalfingerposX <= 69.6) {
				note = C6;
			}

		}//End of Y bottom 
		else if (5.08 < finalfingerposY < 15.24) {//Y is in the blacks and top whites
			if (finalfingerposX < 0) {//
				return note;
			}
			else if (finalfingerposX <= 1.5) {
				note = C2;
			}
			else if (finalfingerposX <= 2.9) {
				note = Cs2;
			}
			else if (finalfingerposX <= 4.3) {
				note = D2;
			}
			else if (finalfingerposX <= 5.7) {
				note = Ds2;
			}
			else if (finalfingerposX <= 7.2) {
				note = E2;
			}
			else if (finalfingerposX <= 8.5) {
				note = F2;
			}
			else if (finalfingerposX <= 9.9) {
				note = Fs2;
			}
			else if (finalfingerposX <= 11.3) {
				note = G2;
			}
			else if (finalfingerposX <= 12.7) {
				note = Gs2;
			}
			else if (finalfingerposX <= 14.1) {
				note = A2;
			}
			else if (finalfingerposX <= 15.5) {
				note = As2;
			}
			else if (finalfingerposX <= 16.8) {
				note = B2;
			}
			else if (finalfingerposX <= 18.3) {
				note = C3;
			}
			else if (finalfingerposX <= 19.7) {
				note = Cs3;
			}
			else if (finalfingerposX <= 21.1) {
				note = D3;
			}
			else if (finalfingerposX <= 22.5) {
				note = Ds3;
			}
			else if (finalfingerposX <= 24) {
				note = E3;
			}
			else if (finalfingerposX <= 25.3) {
				note = F3;
			}
			else if (finalfingerposX <= 26.7) {
				note = Fs3;
			}
			else if (finalfingerposX <= 28.1) {
				note = G3;
			}
			else if (finalfingerposX <= 29.5) {
				note = Gs3;
			}
			else if (finalfingerposX <= 30.9) {
				note = A3;
			}
			else if (finalfingerposX <= 32.3) {
				note = As3;
			}
			else if (finalfingerposX <= 33.6) {
				note = B3;
			}
			else if (finalfingerposX <= 35.1) {
				note = C4;
			}
			else if (finalfingerposX <= 36.5) {
				note = Cs4;
			}
			else if (finalfingerposX <= 37.9) {
				note = D4;
			}
			else if (finalfingerposX <= 39.3) {
				note = Ds4;
			}
			else if (finalfingerposX <= 40.8) {
				note = E4;
			}
			else if (finalfingerposX <= 42.1) {
				note = F4;
			}
			else if (finalfingerposX <= 43.5) {
				note = Fs4;
			}
			else if (finalfingerposX <= 44.9) {
				note = G4;
			}
			else if (finalfingerposX <= 46.3) {
				note = Gs4;
			}
			else if (finalfingerposX <= 47.7) {
				note = A4;
			}
			else if (finalfingerposX <= 49.1) {
				note = As4;
			}
			else if (finalfingerposX <= 50.4) {
				note = B4;
			}
			else if (finalfingerposX <= 51.9) {
				note = C5;
			}
			else if (finalfingerposX <= 53.3) {
			note = Cs5;
			}
			else if (finalfingerposX <= 54.7) {
			note = D5;
			}
			else if (finalfingerposX <= 56.1) {
			note = Ds5;
			}
			else if (finalfingerposX <= 57.6) {
			note = E5;
			}
			else if (finalfingerposX <= 58.9) {
			note = F5;
			}
			else if (finalfingerposX <= 60.3) {
			note = Fs5;
			}
			else if (finalfingerposX <= 61.7) {
			note = G5;
			}
			else if (finalfingerposX <= 63.1) {
			note = Gs5;
			}
			else if (finalfingerposX <= 64.5) {
			note = A5;
			}
			else if (finalfingerposX <= 65.9) {
			note = As5;
			}
			else if (finalfingerposX <= 67.2) {
			note = B5;
			}
			else if (finalfingerposX <= 69.6) {
			note = C6;
			}

		}//End of Y top
	}//end of if Z<1.5

	return note;
}