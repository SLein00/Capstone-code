#include <iostream>
#include <string>
using namespace std;
#include "translationtokbd.h"
#include "keystonotes.h"
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
	Log1.openfile();

	MidiKeyboard midioutput;
	midioutput.listKeyboardOutputs();
	
		
	/*cout << sensortype << ", " << location << ", "<< songlevel <<", " << trialnumber;
	senstype = stoi(sensortype);
	senslocation = stoi(location);
	songtype = stoi(songlevel);
	trialnum = stoi(trialnumber);*/
	cout << sensortype << ", " << location << ", " << songtype << ", " << trialnum << endl; 

	Log1.log(Logger::LogLevel::NOTES, "This is a test of the notes logging");
	Log1.log(Logger::LogLevel::INFO, "This is a test of the info logging");
	Log1.log(Logger::LogLevel::WARN, "This is a test of the warning logging");
	Log1.log(Logger::LogLevel::ERROR, "This is a test of the error logging");

}//End of main