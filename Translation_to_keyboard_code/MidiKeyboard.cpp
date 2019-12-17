#include "MidiKeyboard.h"

extern Logger Log1;

int MidiKeyboard::openkeyboard() {


	return 0;
}

int MidiKeyboard::closekeyboard() {

	return 0;
}

void MidiKeyboard::listKeyboardOutputs() {
	RtMidiOut* midiout = 0;

	try {
		midiout = new RtMidiOut();

	}
	catch (RtMidiError & error) {
		error.printMessage();
		return;
	}

	unsigned int nPorts = midiout->getPortCount();
	
	std::string message("There are ");
	std::string portName;
	message += std::to_string(nPorts) + " MIDI Output ports available.";
	Log1.log(Logger::LogLevel::INFO, message);
	for (unsigned int i = 0; i < nPorts; i++) {
		try {
			portName = midiout->getPortName(i);

		}
		catch (RtMidiError & error) {
			error.printMessage();
			break;
		}

		message = "Output port #" + std::to_string(i + 1);
		message += ": " + portName;
		Log1.log(Logger::LogLevel::INFO, message );
	}

	delete midiout;

}
 
void MidiKeyboard::playKey(MidiNotesNumbers key) {

}

void MidiKeyboard::resetKeys() {

}

void MidiKeyboard::sendKeys() {

}