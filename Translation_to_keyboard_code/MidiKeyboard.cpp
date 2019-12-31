#include "MidiKeyboard.h"

extern Logger Log1;

int MidiKeyboard::openkeyboard() {
	Log1.log(Logger::LogLevel::INFO, "Attempting to open midi keyboard");

	return 0;
}

int MidiKeyboard::closekeyboard() {
	Log1.log(Logger::LogLevel::INFO, "closing midi keyboard");
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
	Log1.log(Logger::LogLevel::INFO, "Keyboard Being asked to play key ", MidiNotesString(key));
}

void MidiKeyboard::resetKeys() {
	Log1.log(Logger::LogLevel::INFO, "Keyboard Resetting keys played");
}

void MidiKeyboard::sendKeys() {

}