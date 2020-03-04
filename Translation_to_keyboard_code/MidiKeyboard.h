#pragma once
#pragma comment(lib, "winmm.lib")
#ifndef MIDIKEYBOARDH
#define MIDIKEYBOARDH
//#define MAKENOISE //To turn on noise uncomment this line

#include <string>
#include "Logger.h"
#include "MidiNotes.h"
#include "RtMidi.h"
#include <array>
#include <thread>
#include <mutex>

class MidiKeyboard
{
public:
	std::string keyboardname = "Skulpt";

	int openkeyboard();
	int closekeyboard();

	void listKeyboardOutputs();
	void resetKeys();
	void playKey(MidiNotesNumbers key);
	void sendKeys();
	std::string playableNotes();



private:
	mutable std::mutex m_midimutex;
	std::array<bool,128> keysplayednow;
	std::array<bool,128> keysplayedlast;
	bool isplayable(int i);

	RtMidiOut* midiout;
};

#endif // !MIDIKEYBOARDH