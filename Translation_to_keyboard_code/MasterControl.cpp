#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;
#include "translationtokbd.h"
#include "keystonotes.h"
#include "LeddarTech.h"
#include "LeapMotion.h"
#include "IntelRealsense.h"
#include "SensorBase.h"
#include "Logger.h"
#include "MidiKeyboard.h"
#include "FakeHands.h"

#include "AsyncGetLine.h"

static const int max_number_of_threads = 8;

class ThreadCountSemaphore {
public:
	ThreadCountSemaphore() {
		m_count = 0;
		for (int id = 0; id < max_number_of_threads; id++) {
			threadids[id] = false;
		}
	}

	~ThreadCountSemaphore() {
		
	}

	int nextavailablethread() {
		lock_guard<mutex> lck(m_lck);
		for (int id = 0; id < max_number_of_threads; id++) {
			if (!threadids[id]) {
				m_count++;
				threadids[id] = true;
				return id;
			}
		}
		return -1;
		//return m_count;
	}

	int decrement(int id) {
		lock_guard<mutex> lck(m_lck);
		m_count--;
		threadids[id] = false;
		return m_count;
	}

	int getthreadcount() {
		return m_count;
	}

private:
	mutable int m_count;
	mutable mutex m_lck;
	mutable bool threadids[max_number_of_threads];
};

ThreadCountSemaphore numthreads;

int sensortype;
int location;
int songtype; 
int trialnum;
//LeddarTech sensor position coordinates in cm
/*double LeddarSidepositioncoordinateX = -68.2; //Original trial was -18.5
double LeddarSidepositioncoordinateY = 5.08;
double LeddarSidepositioncoordinateZ = 1; //Trying at "1 cm"
double LeddarFrontpositioncoordinateX = 34.75;
double LeddarFrontpositioncoordinateY = 30.1;
double LeddarFrontpositioncoordinateZ = 1.5;
double LeddarWebcampositioncoordinateX = 34.75;
double LeddarWebcampositioncoordinateY = 41.3;//103.3-62
double LeddarWebcampositioncoordinateZ = 62;//60.96
double LeddarAbovepositioncoordinateX = 34.75;
double LeddarAbovepositioncoordinateY = 5.08;
double LeddarAbovepositioncoordinateZ = 97.3; 
//Leap sensor position coordinates in cm
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
//Realsense sensor position coordinates in cm 
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
double RealsenseAbovepositioncoordinateZ = 60; */

double posX;
double posY;
double posZ;

double numkeys;

double finposX;
double finposY;
double finposZ;

double finalfingerposX;
double finalfingerposY;
double finalfingerposZ;

string note;

extern Logger Log1;
extern MidiKeyboard midioutput;

Sensor testsensors;
LeddarTech testsensorLeddar;
IntelRealsense testsensorRealsense;
LeapMotion testsensorLeap;
FakeHands testsensorHands;
Keyboard testnotes;

struct rs2threaddataset {
	rs2::frame depth;
	position verts[407040];
	int numValid;
};
rs2threaddataset* rs2threaddata;

void doRealsenseWork(int id) {
	int arridx = 0;
	bool arr[128] = {false};
	
	//testsensorRealsense.GetPointCloud();

	//rs2::frame depth[max_number_of_threads];
	
	int ret = testsensorRealsense.GetDepth(rs2threaddata[id].depth, id);
	if (ret == 0) {

		rs2::pointcloud pc;
		rs2::points points;

		points = pc.calculate(rs2threaddata[id].depth);

		const rs2::vertex* verts = points.get_vertices();

		//RealsensePointReturn retpoints[max_number_of_threads];
		rs2threaddata[id].numValid = 0;
		//rs2::vertex first = verts[0];
		// Intel Realsense D435 Spefic Decimate by 4
		for (int r = 150; r < 330; r += 2) {
			for (int c = 200; c < 648; c += 2)
			{
				rs2::vertex vert = verts[r * 848 + c];
				if (vert.z != 0) {
					int nv = rs2threaddata[id].numValid;
					rs2threaddata[id].verts[nv].X = vert.x*100.0;
					rs2threaddata[id].verts[nv].Y = vert.y*100.0;
					rs2threaddata[id].verts[nv].Z = vert.z*100.0;
					rs2threaddata[id].numValid++;
					//std::cout << idx << ";" << vert.x << "," << vert.y << "," << vert.z << std::endl;
				}

			}
		}


		for (int idx = 0; idx < rs2threaddata[id].numValid; idx++) {
			position FinalFingerPos = testsensors.Realsenseswitchtokbd(rs2threaddata[id].verts[idx].X, rs2threaddata[id].verts[idx].Y, rs2threaddata[id].verts[idx].Z);
			//Log1.log(Logger::LogLevel::MOREDEBUG, id, retpoints->verts[idx].X, retpoints->verts[idx].Y, retpoints->verts[idx].Z, FinalFingerPos.X, FinalFingerPos.Y, FinalFingerPos.Z);
			MidiNotesNumbers notenum = testnotes.notes(FinalFingerPos.X, FinalFingerPos.Y, FinalFingerPos.Z);
			if (!notenum == None) {
				//Log1.log(Logger::LogLevel::DEBUG, MidiNotesString(notenum), " On ", id);
				arr[notenum] = true;
			}
		}

		// locks the midistream, so bulk do midi stuff.
		midioutput.resetKeys();
		for (int i = 0; i < 128; i++) {
			if (arr[i]) {
				midioutput.playKey((MidiNotesNumbers)i);
			}
		}
		midioutput.sendKeys();
	}
	else {
		char buf[200];
		sprintf(buf, "Did not get good realsense data thread %d", id);
		Log1.log(Logger::LogLevel::cERROR, buf);
	}
	numthreads.decrement(id);

}


int main() {//Beginning of main

	cout << "Sensor type: " << endl;
	cout << "(Pick one of the following options)" << endl;
	cout << "1 = LeddarTech Sensor Evaluation Kit" << endl;
	cout << "2 = Leap Motion Controller" << endl;
	cout << "3 = Intel Realsense Depth Camera " << endl;
	cout << "4 = Fake Hands" << endl;
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
		Log1.log(Logger::LogLevel::INFO, "Sensor 3 is Realsense");
		try {
			rs2threaddata = new rs2threaddataset[max_number_of_threads];
		}
		catch (bad_alloc xa) {
			cerr << "Cannot allocate memory for threads" << endl;
			return -1;
		}
		break;
	case 4:
		Log1.log(Logger::LogLevel::INFO, "Sensor is the random keyboard");
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
			posX = testsensors.LeddarSidepositioncoordinateX;
			posY = testsensors.LeddarSidepositioncoordinateY;
			posZ = testsensors.LeddarSidepositioncoordinateZ;
		}
		else if (location == 2) {//Front position
			posX = testsensors.LeddarFrontpositioncoordinateX;
			posY = testsensors.LeddarFrontpositioncoordinateY;
			posZ = testsensors.LeddarFrontpositioncoordinateZ;
		}
		else if (location == 3) {//Webcam position
			posX = testsensors.LeddarWebcampositioncoordinateX;
			posY = testsensors.LeddarWebcampositioncoordinateY;
			posZ = testsensors.LeddarWebcampositioncoordinateZ;
		}
		else if (location == 4) {//Above position
			posX = testsensors.LeddarAbovepositioncoordinateX;
			posY = testsensors.LeddarAbovepositioncoordinateY;
			posZ = testsensors.LeddarAbovepositioncoordinateZ;
		}
	}
	else if (sensortype == 2) {//Leap Motion
		testsensorLeap.InitializeSensor();
		//Location initialization
		if (location == 1) {//Side position
			posX = testsensors.LeapSidepositioncoordinateX;
			posY = testsensors.LeapSidepositioncoordinateY;
			posZ = testsensors.LeapSidepositioncoordinateZ;
		}
		else if (location == 2) {//Front position
			posX = testsensors.LeapFrontpositioncoordinateX;
			posY = testsensors.LeapFrontpositioncoordinateY;
			posZ = testsensors.LeapFrontpositioncoordinateZ;
		}
		else if (location == 3) {//Webcam position
			posX = testsensors.LeapWebcampositioncoordinateX;
			posY = testsensors.LeapWebcampositioncoordinateY;
			posZ = testsensors.LeapWebcampositioncoordinateZ;
		}
		else if (location == 4) {//Above position
			posX = testsensors.LeapAbovepositioncoordinateX;
			posY = testsensors.LeapAbovepositioncoordinateY;
			posZ = testsensors.LeapAbovepositioncoordinateZ;
		}
	} 
	else if (sensortype == 3) {//Realsense
		testsensorRealsense.InitializeSensor();
		//Location initialization
		if (location == 1) {//Side position
			posX = testsensors.RealsenseSidepositioncoordinateX;
			posY = testsensors.RealsenseSidepositioncoordinateY;
			posZ = testsensors.RealsenseSidepositioncoordinateZ;
		}
		else if (location == 2) {//Front position
			posX = testsensors.RealsenseFrontpositioncoordinateX;
			posY = testsensors.RealsenseFrontpositioncoordinateY;
			posZ = testsensors.RealsenseFrontpositioncoordinateZ;
		}
		else if (location == 3) {//Webcam position
			posX = testsensors.RealsenseWebcampositioncoordinateX;
			posY = testsensors.RealsenseWebcampositioncoordinateY;
			posZ = testsensors.RealsenseWebcampositioncoordinateZ;
		}
		else if (location == 4) {//Above position
			posX = testsensors.RealsenseAbovepositioncoordinateX;
			posY = testsensors.RealsenseAbovepositioncoordinateY;
			posZ = testsensors.RealsenseAbovepositioncoordinateZ;
		}
	}
	else if (sensortype == 4) {
		testsensorHands.InitializeSensor();

	}

	//Makes it so the translation to kbd pos values are equal to master control pos values
	testsensors.posX = posX;
	testsensors.posY = posY;
	testsensors.posZ = posZ;

	AsyncGetline ag;
	string consoleinput;

	for (int i = 0; i < 1500; i++) {//beginning of loop
		//CAITLYNS EDITS
	
		Log1.log(Logger::LogLevel::DEBUG, "At begining of Master Control's loop");
		
		consoleinput = ag.GetLine();
		if (!consoleinput.empty() && consoleinput[1] == 'q'){
			break;
		}

		//recieve data



		//condition data
		if (sensortype == 1) {//LeddarTech
			midioutput.resetKeys();
			//condition data
			array <double, 16> Originalvals;
			array <position, 16> Coordinates;
			Originalvals = testsensorLeddar.GetValues();
			for (int idx = 0; idx < 16; idx++) {
				double angle = ((22.5 - idx * 3) * 3.1415965359) / 180;
				Coordinates[idx].Z = 0;
				Coordinates[idx].X = cos(angle) * (Originalvals[idx] * 100 + testsensorLeddar.CorrectionFactor[idx] * 100);
				Coordinates[idx].Y = sin(angle) * (Originalvals[idx] * 100 + testsensorLeddar.CorrectionFactor[idx] * 100);
				

				cout << Coordinates[idx].X << "," << Coordinates[idx].Y << "," << Coordinates[idx].Z << endl ;

				position FinalFingerPos = testsensors.Leddarswitchtokbd(Coordinates[idx].X, Coordinates[idx].Y, Coordinates[idx].Z);

				cout << FinalFingerPos.X << "," << FinalFingerPos.Y << "," << FinalFingerPos.Z << endl;

				MidiNotesNumbers notenum = testnotes.notes(FinalFingerPos.X, FinalFingerPos.Y, FinalFingerPos.Z);

				char buffer[10000];
				sprintf(buffer, "In MC Loop, Leddar, Idx=%i, Leddar=%f, Coord=[%f, %f, %f], FinalFingerPos=[%f, %f, %f], Midi=[%s]", idx, Originalvals[idx], Coordinates[idx].X, Coordinates[idx].Y, Coordinates[idx].Z, FinalFingerPos.X, FinalFingerPos.Y, FinalFingerPos.Z, MidiNotesString(notenum).c_str());
				Log1.log(Logger::LogLevel::INFO, buffer);

				if (!notenum == None) {
					Log1.log(Logger::LogLevel::INFO, MidiNotesString(notenum), "On");
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
			midioutput.resetKeys();
			//condition data
			array <position, 10> Originalvals;
			position PreCoordinates;
			array <position, 10> Coordinates;
			Originalvals = testsensorLeap.GetFingerPositions();
			for (int idx = 0; idx < 10; idx++) {
				PreCoordinates = Originalvals[idx];
				Coordinates[idx].X = PreCoordinates.X;
				Coordinates[idx].Y = PreCoordinates.Y;
				Coordinates[idx].Z = PreCoordinates.Z;

				cout << Coordinates[idx].X << "," << Coordinates[idx].Y << "," << Coordinates[idx].Z << endl;

				position FinalFingerPos = testsensors.Leapswitchtokbd(Coordinates[idx].X, Coordinates[idx].Y, Coordinates[idx].Z);

				char buffer[10000];
				sprintf(buffer, "Leap Keyboard Coordinates finger %d = [ X = %0.3f, Y = %0.3f, Z = %0.3f ] ", idx, FinalFingerPos.X, FinalFingerPos.Y, FinalFingerPos.Z);
				Log1.log(Logger::LogLevel::DEBUG, buffer);

				cout << FinalFingerPos.X << "," << FinalFingerPos.Y << "," << FinalFingerPos.Z << endl;

				MidiNotesNumbers notenum = testnotes.notes(FinalFingerPos.X, FinalFingerPos.Y, FinalFingerPos.Z);

				note = MidiNotesString(notenum);

				Log1.log(Logger::LogLevel::DEBUG, note);

				if (!notenum == None) {
					Log1.log(Logger::LogLevel::INFO, MidiNotesString(notenum), " On");
					midioutput.playKey(notenum);

					cout << note << endl;
				}
			}
			midioutput.sendKeys();
		}
		else if (sensortype == 3) {//Realsense
			/*
			//condition data
			midioutput.resetKeys();
			//Log1.log(Logger::LogLevel::ERROR, "Chose Realsense and Code has yet to be made for said sensor.");

			testsensorRealsense.GetPointCloud();
			for (int idx = 0; idx < testsensorRealsense.validPoints->numValid; idx++) {
				position FinalFingerPos = testsensors.Realsenseswitchtokbd((testsensorRealsense.validPoints->verts[idx].x)*100, (testsensorRealsense.validPoints->verts[idx].y)*100, (testsensorRealsense.validPoints->verts[idx].z)*100);
				MidiNotesNumbers notenum = testnotes.notes(FinalFingerPos.X, FinalFingerPos.Y, FinalFingerPos.Z);

				char buffer[10000];
				sprintf(buffer, "In MC Loop, Realsense, Idx=%i, Coord=[%f, %f, %f], FinalFingerPos=[%f, %f, %f], Midi=[%s]", idx, (testsensorRealsense.validPoints->verts[idx].x)*100, (testsensorRealsense.validPoints->verts[idx].y)*100, (testsensorRealsense.validPoints->verts[idx].z)*100, FinalFingerPos.X, FinalFingerPos.Y, FinalFingerPos.Z, MidiNotesString(notenum).c_str());
				Log1.log(Logger::LogLevel::DEBUG, buffer);

				if (!notenum == None) {
					Log1.log(Logger::LogLevel::DEBUG, MidiNotesString(notenum), "On");
					midioutput.playKey(notenum);
			*/ // moving main to threading
			
			// realsense processing moved to thread helper way above.

			if (numthreads.getthreadcount() < max_number_of_threads) {
				int tid = numthreads.nextavailablethread();
				if (tid > -1) {
					std::thread t(doRealsenseWork, tid);
					t.detach();
				}
			}
			else {
				Log1.log(Logger::LogLevel::DEBUG, "Waiting for thread reasources");
				this_thread::sleep_for(4ms);
			}

		}
		else if (sensortype == 4) { // fake random keyboard
			midioutput.resetKeys();
			array<MidiNotesNumbers, 10> possiblenotes;
			possiblenotes = testsensorHands.GetValues(songtype);

			for (int i = 0; i < 10; i++) {
				if (possiblenotes[i] != None) {
					midioutput.playKey(possiblenotes[i]);
				}
			}

			midioutput.sendKeys();
		}
		//pass list of keys played to Keyboard control
		//Keyboardcontrol-Caitlyn



	/*
	Log1.log(Logger::LogLevel::NOTES, "This is a test of the notes logging");
	Log1.log(Logger::LogLevel::INFO, "This is a test of the info logging");
	Log1.log(Logger::LogLevel::WARN, "This is a test of the warning logging");
	Log1.log(Logger::LogLevel::ERROR, "This is a test of the error logging");
	*/


	}//end of loop
	cout << "Wrapping Up for trial: " << sensortype << ", " << location << ", " << songtype << ", " << trialnum << endl;

	while (numthreads.getthreadcount() > 0) {
		cout << "Waiting for " << numthreads.getthreadcount() << " threads to wrap up." << endl;
		this_thread::sleep_for(500ms);
	}

	midioutput.closekeyboard();

	//turn off sensor
	if (sensortype == 1) { // leddar
		testsensorLeddar.CloseSensor();
	}
	else if (sensortype == 2) { // leap
		testsensorLeap.CloseSensor();
	}
	else if (sensortype == 3) { // realsense
		testsensorRealsense.CloseSensor();
	}

	//close and save
	Log1.closefile();


}//End of main

