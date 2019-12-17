#pragma once
#pragma comment(lib, "winmm.lib")
#ifndef MIDIKEYBOARDH
#define MIDIKEYBOARDH


#include <string>
#include "Logger.h"
#include "MidiNotes.h"
#include "RtMidi.h"

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



private:

};

#endif // !MIDIKEYBOARDH