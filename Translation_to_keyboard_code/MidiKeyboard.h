#pragma once
#pragma comment(lib, "winmm.lib")

#include <string>
#include "Logger.h"

#include "RtMidi.h"

class MidiKeyboard
{
public:
	std::string keyboardname = "Skulpt";

	int openkeyboard();
	int closekeyboard();

	void listKeyboardOutputs();

private:

};

