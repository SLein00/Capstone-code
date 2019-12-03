#include <iostream>
#include <string>
using namespace std;
#include "translationtokbd.h"
#include "keystonotes.h"
string sensortype;
string location;
string songlevel;
string trialnumber;
int senstype;
int senslocation;
int songtype; 
int trialnum;
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
	/*cout << sensortype << ", " << location << ", "<< songlevel <<", " << trialnumber;
	senstype = stoi(sensortype);
	senslocation = stoi(location);
	songtype = stoi(songlevel);
	trialnum = stoi(trialnumber);*/
	cout << sensortype << ", " << location << ", " << songtype << ", " << trialnum;

}//End of main