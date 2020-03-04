#include "MidiKeyboard.h"

extern Logger Log1;

int MidiKeyboard::openkeyboard() {
	std::lock_guard<std::mutex> lck(m_midimutex);
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
	std::lock_guard<std::mutex> lck(m_midimutex);
	Log1.log(Logger::LogLevel::INFO, "closing midi keyboard");
	std::vector<unsigned char> message;
	message.resize(3);
#ifdef MAKENOISE
	if (midiout->isPortOpen()) {
		for (int i = 0; i < 128; i++) {
			// send note off
			message[0] = 128;
			message[1] = i;
			message[2] = 40;
			midiout->sendMessage(&message);

		}
		midiout->closePort();
	}
#endif
	return 0;
}

void MidiKeyboard::listKeyboardOutputs() {
	std::lock_guard<std::mutex> lck(m_midimutex);
	//RtMidiOut* midiout = 0;

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

	try {
		midiout->openPort(nPorts-1); /// open the last port by default.
	}
	catch (RtMidiError &e) {
		Log1.log(Logger::LogLevel::cERROR, e.getMessage());
	}

	//delete midiout;

}
 
// NOTE:  resetKeys, playKey and sendKey must now be called in order to maintain thread locking.

void MidiKeyboard::playKey(MidiNotesNumbers key) {
	//Log1.log(Logger::LogLevel::DEBUG, "Keyboard Being asked to play key ", MidiNotesString(key));
	keysplayednow[key] = true;
}

void MidiKeyboard::resetKeys() {
	m_midimutex.lock(); // lock mutex on 
	keysplayedlast = keysplayednow;
	//Log1.log(Logger::LogLevel::DEBUG, "======================");
	//Log1.log(Logger::LogLevel::DEBUG, "Keyboard Resetting keys played");
	for (int i = 0; i < 128; i++) {
		keysplayednow[i] = false;
	}
}

void MidiKeyboard::sendKeys() {
	std::vector<unsigned char> message;
	message.resize(3);
	std::string logres = "";

	for (int i = 0; i < 128; i++) {
#ifdef MAKENOISE
		if (keysplayedlast[i] == false && keysplayednow[i] == true) {
			// send note on
			message[0] = 144;
			message[1] = i;
			message[2] = 40;
			midiout->sendMessage(&message);

		}
		else if (keysplayedlast[i] == true && keysplayednow[i] == false) {
			// send note off
			message[0] = 128;
			message[1] = i;
			message[2] = 40;
			midiout->sendMessage(&message);
		}
#endif
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
	//Log1.log(Logger::LogLevel::DEBUG, "======================");
	Log1.log(Logger::LogLevel::NOTES, logres.substr(1,logres.length()-1));
	m_midimutex.unlock();

}

bool MidiKeyboard::isplayable(int notein) {
	if (notein > 23 && notein < 121)
		return true;
	else
		return false;
}

MidiKeyboard midioutput;