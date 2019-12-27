#include <iostream>
#include <string>
using namespace std;
#include "translationtokbd.h"
#include "keystonotes.h"
#include "LeddarTech.h"
#include "LeapMotion.h"
#include "IntelRealsense.h"
#include "SensorBase.h"
#include "Logger.h"
#include "MidiKeyboard.h"


int sensortype;
int location;
int songtype; 
int trialnum;
//LeddarTech sensor position coordinates
double LeddarSidepositioncoordinateX = -15;
double LeddarSidepositioncoordinateY = 7.75;
double LeddarSidepositioncoordinateZ = 1.5;
double LeddarFrontpositioncoordinateX = 34.75;
double LeddarFrontpositioncoordinateY = 30.1;
double LeddarFrontpositioncoordinateZ = 1.5;
double LeddarWebcampositioncoordinateX = 34.75;
double LeddarWebcampositioncoordinateY = 30.1;
double LeddarWebcampositioncoordinateZ = 45;
double LeddarAbovepositioncoordinateX = 34.75;
double LeddarAbovepositioncoordinateY = 7.55;
double LeddarAbovepositioncoordinateZ = 60;
//Leap sensor position coordinates
double LeapSidepositioncoordinateX = -15;
double LeapSidepositioncoordinateY = 7.75;
double LeapSidepositioncoordinateZ = 1.5;
double LeapFrontpositioncoordinateX = 34.75;
double LeapFrontpositioncoordinateY = 30.1;
double LeapFrontpositioncoordinateZ = 1.5;
double LeapWebcampositioncoordinateX = 34.75;
double LeapWebcampositioncoordinateY = 30.1;
double LeapWebcampositioncoordinateZ = 45;
double LeapAbovepositioncoordinateX = 34.75;
double LeapAbovepositioncoordinateY = 7.55;
double LeapAbovepositioncoordinateZ = 60;
//Realsense sensor position coordinates
double RealsenseSidepositioncoordinateX = -15;
double RealsenseSidepositioncoordinateY = 7.75;
double RealsenseSidepositioncoordinateZ = 1.5;
double RealsenseFrontpositioncoordinateX = 34.75;
double RealsenseFrontpositioncoordinateY = 30.1;
double RealsenseFrontpositioncoordinateZ = 1.5;
double RealsenseWebcampositioncoordinateX = 34.75;
double RealsenseWebcampositioncoordinateY = 30.1;
double RealsenseWebcampositioncoordinateZ = 45;
double RealsenseAbovepositioncoordinateX = 34.75;
double RealsenseAbovepositioncoordinateY = 7.55;
double RealsenseAbovepositioncoordinateZ = 60;

double sensorposX;
double sensorposY;
double sensorposZ;

double numkeys;

double finposX;
double finposY;
double finposZ;

double finalfingerposX;
double finalfingerposY;
double finalfingerposZ;

string note;

extern Logger Log1;

int main() {//Beginning of main
	cout << "Sensor type: " << endl;
	cout << "(Pick one of the following options)" << endl;
	cout << "1 = LeddarTech Sensor Evaluation Kit" << endl;
	cout << "2 = Leap Motion Controller" << endl;
	cout << "3 = Intel Realsense Depth Camera " << endl;
	cin >> sensortype;
	cout << "Location of sensor: "<< endl;
	cout << "(Pick one of the following options)" << endl;
	cout << "1 = Side position" << endl;
	cout << "2 = Front position" << endl;
	cout << "3 = Webcam position" << endl;
	cout << "4 = Above position " << endl;
	cin >> location;
	cout << "Song classification: "<< endl;
	cout << "(Pick one of the following options)" << endl;
	cout << "1 = Level 1 (One-fingered scales)" << endl;
	cout << "2 = Level 2 (One-handed simple melody)" << endl;
	cout << "3 = Level 3 (Two-handed simple)" << endl;
	cout << "4 = Level 4 (Two-handed advanced) " << endl;
	cin >> songtype;
	cout << "Trial number: ";
	cin >> trialnum;

	// Puts the metadata in the log file, sets the running timer to 0 and opens the file
	Log1.setMetaData(sensortype, location, songtype, trialnum);
	Log1.restartTimer();
	Log1.openfile();

	Sensor testsensors;
	LeddarTech testsensorLeddar;
	IntelRealsense testsensorRealsense;
	LeapMotion testsensorLeap;
	MidiKeyboard midioutput;
	Keyboard testnotes;
	midioutput.listKeyboardOutputs();
	
		
	/*cout << sensortype << ", " << location << ", "<< songlevel <<", " << trialnumber;
	senstype = stoi(sensortype);
	senslocation = stoi(location);
	songtype = stoi(songlevel);
	trialnum = stoi(trialnumber);*/

	cout << "Summary of options: " << sensortype << ", " << location << ", " << songtype << ", " << trialnum << endl;
	switch (sensortype) {
	case 1:
		Log1.log(Logger::LogLevel::INFO, "Sensor 1 is Leddartech");
		break;
	case 2:
		Log1.log(Logger::LogLevel::INFO, "Sensor 2 is Leap");
		break;
	case 3:
		Log1.log(Logger::LogLevel::INFO, "Sensor 3 is Leddartech");
		break;
	default:
		Log1.log(Logger::LogLevel::INFO, "Sensor is unidentified");
		break;
	}

	switch (location) {
	case 1:
		Log1.log(Logger::LogLevel::INFO, "Location 1 is Side");
		break;
	case 2:
		Log1.log(Logger::LogLevel::INFO, "Location 2 is Front");
		break;
	case 3:
		Log1.log(Logger::LogLevel::INFO, "Location 3 is Webcam");
		break;
	case 4:
		Log1.log(Logger::LogLevel::INFO, "Location 4 is Above");
		break;
	default:
		Log1.log(Logger::LogLevel::INFO, "Location is unidentified");
		break;
	}

	switch (songtype) {
	case 1:
		Log1.log(Logger::LogLevel::INFO, "Song 1 is one-finger scales");
		break;
	case 2:
		Log1.log(Logger::LogLevel::INFO, "Song 2 is one handed - simple melody");
		break;
	case 3:
		Log1.log(Logger::LogLevel::INFO, "Song 3 is two handed - simple melody");
		break;
	case 4:
		Log1.log(Logger::LogLevel::INFO, "Song 4 is two handed - advanced melody");
		break;
	default:
		Log1.log(Logger::LogLevel::INFO, "Song is unidentified");
		break;
	}

	Log1.log(Logger::LogLevel::INFO, "Trial # is ", to_string(trialnum));
	//Location initialization
	/*
	if (location == 1) {//Side position
		Sensor testsensor = Sensor(sensorposX, sensorposY, sensorposZ);
	}
	else if (location == 2) {//Front position
	}
	else if (location == 3) {//Webcam position
	}
	else if (location == 4) {//Above position
	}	
	*/
	//initialize sensor

	if (sensortype == 1) {//LeddarTech
		testsensorLeddar.InitializeSensor();
		//Location initialization
		if (location == 1) {//Side position
			sensorposX = LeddarSidepositioncoordinateX;
			sensorposY = LeddarSidepositioncoordinateY;
			sensorposZ = LeddarSidepositioncoordinateZ;
		}
		else if (location == 2) {//Front position
			sensorposX = LeddarFrontpositioncoordinateX;
			sensorposY = LeddarFrontpositioncoordinateY;
			sensorposZ = LeddarFrontpositioncoordinateZ;
		}
		else if (location == 3) {//Webcam position
			sensorposX = LeddarWebcampositioncoordinateX;
			sensorposY = LeddarWebcampositioncoordinateY;
			sensorposZ = LeddarWebcampositioncoordinateZ;
		}
		else if (location == 4) {//Above position
			sensorposX = LeddarAbovepositioncoordinateX;
			sensorposY = LeddarAbovepositioncoordinateY;
			sensorposZ = LeddarAbovepositioncoordinateZ;
		}
	}
	else if (sensortype == 2) {//Leap Motion
		testsensorLeap.InitializeSensor();
		//Location initialization
		if (location == 1) {//Side position
			sensorposX = LeapSidepositioncoordinateX;
			sensorposY = LeapSidepositioncoordinateY;
			sensorposZ = LeapSidepositioncoordinateZ;
		}
		else if (location == 2) {//Front position
			sensorposX = LeapFrontpositioncoordinateX;
			sensorposY = LeapFrontpositioncoordinateY;
			sensorposZ = LeapFrontpositioncoordinateZ;
		}
		else if (location == 3) {//Webcam position
			sensorposX = LeapWebcampositioncoordinateX;
			sensorposY = LeapWebcampositioncoordinateY;
			sensorposZ = LeapWebcampositioncoordinateZ;
		}
		else if (location == 4) {//Above position
			sensorposX = LeapAbovepositioncoordinateX;
			sensorposY = LeapAbovepositioncoordinateY;
			sensorposZ = LeapAbovepositioncoordinateZ;
		}
	} 
	else if (sensortype == 3) {//Realsense
		testsensorRealsense.InitializeSensor();
		//Location initialization
		if (location == 1) {//Side position
			sensorposX = RealsenseSidepositioncoordinateX;
			sensorposY = RealsenseSidepositioncoordinateY;
			sensorposZ = RealsenseSidepositioncoordinateZ;
		}
		else if (location == 2) {//Front position
			sensorposX = RealsenseFrontpositioncoordinateX;
			sensorposY = RealsenseFrontpositioncoordinateY;
			sensorposZ = RealsenseFrontpositioncoordinateZ;
		}
		else if (location == 3) {//Webcam position
			sensorposX = RealsenseWebcampositioncoordinateX;
			sensorposY = RealsenseWebcampositioncoordinateY;
			sensorposZ = RealsenseWebcampositioncoordinateZ;
		}
		else if (location == 4) {//Above position
			sensorposX = RealsenseAbovepositioncoordinateX;
			sensorposY = RealsenseAbovepositioncoordinateY;
			sensorposZ = RealsenseAbovepositioncoordinateZ;
		}
	}

	for (int i = 0; i < 1; i++) {//beginning of loop
		Log1.log(Logger::LogLevel::INFO, "At begining of Master Control's loop");
		//recieve data

		//condition data
		if (sensortype == 1) {//LeddarTech
			midioutput.resetKeys();
			//condition data
			array <double, 16> Originalvals;
			array <position, 16> Coordinates;
			Originalvals = testsensorLeddar.GetValues();
			for (int idx = 0; idx < 16; idx++) {
				double angle = ((-22.5 + idx * 3)*3.1415965359)/180;
				Coordinates[idx].Z = 0;
				Coordinates[idx].X = sin(angle) * (Originalvals[idx] * 100 + testsensorLeddar.CorrectionFactor[idx]);
				Coordinates[idx].Y = cos(angle) * (Originalvals[idx] * 100 + testsensorLeddar.CorrectionFactor[idx]);
				position FinalFingerPos = testsensors.Leddarswitchtokbd(Coordinates[idx].X, Coordinates[idx].Y, Coordinates[idx].Z);
				MidiNotesNumbers notenum =testnotes.notes(FinalFingerPos.X, FinalFingerPos.Y, FinalFingerPos.Z);
				char buffer[1000];
				sprintf(buffer, "In MC Loop, Leddar, Idx=%i, Leddar=%f, Coord=[%f, %f, %f], FinalFingerPos=[%f, %f, %f], Midi=[%s]", idx, Originalvals[idx], Coordinates[idx].X, Coordinates[idx].Y, Coordinates[idx].Z, FinalFingerPos.X, FinalFingerPos.Y, FinalFingerPos.Z, MidiNotesString(notenum).c_str());
				Log1.log(Logger::LogLevel::INFO, buffer);
				if (!notenum == None) {
					Log1.log(Logger::LogLevel::NOTES, MidiNotesString(notenum), "On");
					midioutput.playKey(notenum);
				}
			}
			midioutput.sendKeys();
			//Coordinates[5].Y
			/*
			Always run all 16 segments
			Side position: Still run all sections, just will rarely get data from outer ones only the middle few sections will matter closest is the note, determine coordinate
			Front position: most if not all of the sections, determine the sections that have a distance within the keyboards area, determine coordinate
			Webcam position: most/all, same as the front position basically
			Above: all sections will be used. sections that contain a distance closer than the table
			Store incoming data 
			number of notes played (numkeys)
			storing each coordinate played
			*/
			
			
			
		}
		else if (sensortype == 2) {//Leap Motion
			//condition data
			//number of notes played
			//store all coordinates

			for (int n = 0; n < (numkeys + 1); n++) {
				testsensors.Leddarswitchtokbd(finposX, finposY, finposZ);
				testnotes.notes(finalfingerposX, finalfingerposY, finalfingerposZ);
				Log1.log(Logger::LogLevel::NOTES, note, "On");
			}
		}
		else if (sensortype == 3) {//Realsense
			//condition data
			Log1.log(Logger::LogLevel::ERROR, "Chose Realsense and Code has yet to be made for said sensor.");

			for (int n = 0; n < (numkeys + 1); n++) {
				testsensors.Leddarswitchtokbd(finposX, finposY, finposZ);
				testnotes.notes(finalfingerposX, finalfingerposY, finalfingerposZ);
				Log1.log(Logger::LogLevel::NOTES, note, "On");
			}
		}
		
		//pass list of keys played to Keyboard control
		//Keyboardcontrol-Caitlyn


	cout << "Wrapping Up for trial: " << sensortype << ", " << location << ", " << songtype << ", " << trialnum << endl; 
	/*
	Log1.log(Logger::LogLevel::NOTES, "This is a test of the notes logging");
	Log1.log(Logger::LogLevel::INFO, "This is a test of the info logging");
	Log1.log(Logger::LogLevel::WARN, "This is a test of the warning logging");
	Log1.log(Logger::LogLevel::ERROR, "This is a test of the error logging");
	*/


	}//end of loop
	
	 //close and save
	Log1.closefile();

	//turn off sensor


}//End of main