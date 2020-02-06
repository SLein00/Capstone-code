#include "MidiKeyboard.h"

extern Logger Log1;

int MidiKeyboard::openkeyboard() {
	Log1.log(Logger::LogLevel::INFO, "Attempting to open midi keyboard");
	return 0;
}

std::string MidiKeyboard::playableNotes() {
	std::string retstring;
	for (int i = 0; i < 128; i++) {
		if (isplayable(i)) {
			retstring.append(", ");
			retstring.append(MidiNotesString((MidiNotesNumbers)i));
		}
	}
	return retstring;
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
	Log1.log(Logger::LogLevel::DEBUG, "Keyboard Being asked to play key ", MidiNotesString(key));
	keysplayednow[key] = true;
}

void MidiKeyboard::resetKeys() {
	keysplayedlast = keysplayednow;
	Log1.log(Logger::LogLevel::DEBUG, "======================");
	Log1.log(Logger::LogLevel::DEBUG, "Keyboard Resetting keys played");
	for (int i = 0; i < 128; i++) {
		keysplayednow[i] = false;
	}
}

void MidiKeyboard::sendKeys() {
	std::string logres;
	for (int i = 0; i < 128; i++) {
		if (keysplayedlast[i] == false && keysplayednow[i] == true) {
			// send note on
		}
		else if (keysplayedlast[i] == true && keysplayednow[i] == false) {
			// send note off
		}
		if (isplayable(i)) {
			if (keysplayednow[i]) {
				logres.append(",ON");
			}
			else {
				logres.append(",OFF");
			}
		}
	}

	//Log1.log(Logger::LogLevel::NOTES, logres.substr(2,logres.length()-2));
	Log1.log(Logger::LogLevel::DEBUG, "======================");
	Log1.log(Logger::LogLevel::NOTES, logres.substr(1,logres.length()-1));
	

}

bool MidiKeyboard::isplayable(int notein) {
	if (notein > 23 && notein < 121)
		return true;
	else
		return false;
}

MidiKeyboard midioutput;