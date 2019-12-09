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


string sensortype;
string location;
string songlevel;
string trialnumber;
int songtype; 
int trialnum;

extern Logger Log1;

int main() {//Beginning of main
	cout << "Sensor type: ";
	cin >> sensortype;
	cout << "Location of sensor: ";
	cin >> location;
	cout << "Song classification: ";
	cin >> songtype;
	cout << "Trial number: ";
	cin >> trialnum;
	//TODO make this into a log call
	
	// in work 
	Log1.setMetaData(sensortype, location, songtype, trialnum);
	Log1.restartTimer();
	Log1.openfile();

	SensorBase testsensor;
	LeddarTech testsensorLeddar;
	IntelRealsense testsensorRealsense;
	LeapMotion testsensorLeap;
	MidiKeyboard midioutput;
	midioutput.listKeyboardOutputs();
	
		
	/*cout << sensortype << ", " << location << ", "<< songlevel <<", " << trialnumber;
	senstype = stoi(sensortype);
	senslocation = stoi(location);
	songtype = stoi(songlevel);
	trialnum = stoi(trialnumber);*/

	cout << sensortype << ", " << location << ", " << songtype << ", " << trialnum;
	//initialize sensor

	if (sensortype == "LeddarTech") {	
		testsensorLeddar.InitializeSensor();
	}
	else if (sensortype == "LeapMotion") {
		testsensorLeap.InitializeSensor();
	} 
	else if (sensortype == "IntelRealSense") {
		testsensorRealsense.InitializeSensor();
	}
	for (int i = 0; i < 10; i++) {//beginning of loop
		//recieve data
		//condition data
		if (sensortype == "LeddarTech") {
			//condition data
		}
		else if (sensortype == "LeapMotion") {
			//condition data
		}
		else if (sensortype == "IntelRealSense") {
			//condition data
		}
		//Loop 2
			//transitiontokbd function
			//keystonotes function
		//pass list of keys played to Keyboard control
		//Keyboardcontrol

	/*
	cout << sensortype << ", " << location << ", " << songtype << ", " << trialnum << endl; 

	Log1.log(Logger::LogLevel::NOTES, "This is a test of the notes logging");
	Log1.log(Logger::LogLevel::INFO, "This is a test of the info logging");
	Log1.log(Logger::LogLevel::WARN, "This is a test of the warning logging");
	Log1.log(Logger::LogLevel::ERROR, "This is a test of the error logging");
	*/


	}//end of loop
	//close and save
	//turn off sensor
}//End of main