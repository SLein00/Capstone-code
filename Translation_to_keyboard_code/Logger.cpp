#include "Logger.h"

extern MidiKeyboard midioutput;

Logger::Logger() {
	time_t now = time(0);
	std::string flname;
	tm *ltm = localtime(&now);

	char buffer[2560];


	//flname.append(std::to_string(1900 + ltm->tm_year));
	//sprintf(buffer, "%02d", 1 + ltm->tm_mon);
	//flname.append(buffer);
	//sprintf(buffer, "%02d", ltm->tm_mday);
	//flname.append(buffer);
	//flname.append("_");
	//sprintf(buffer, "%02d", ltm->tm_hour);
	//flname.append(buffer);
	//sprintf(buffer, "%02d", ltm->tm_min);
	//flname.append(buffer);
	//flname.append(".txt");

	sprintf(buffer, "Log%04d%02d%02d_%02d%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min);
	flname = buffer;
	m_filename = flname;
	m_filename.append(".txt");
	m_csvname = flname;
	m_csvname.append(".csv");
	m_directory = "./LogFiles";
}

Logger::Logger(std::string filename) {
	m_filename = filename;
	char buffer[1000];
	m_csvname = filename.copy(buffer, (filename.length() > 990) ? 990 : filename.length()-4 , 0);
	m_csvname.append(".csv");
	m_directory = "./LogFiles";
}

void Logger::flush() {
	if (m_logfile.is_open()) {
		m_logfile.flush();
	}
	if (m_csvfile.is_open()) {
		m_csvfile.flush();
	}
}

Logger::Logger(std::string directory, std::string filename) {
	m_filename = filename;

	char buffer[1000];
	m_csvname = filename.copy(buffer, (filename.length() > 990) ? 990 : filename.length() - 4, 0);
	m_csvname.append(".csv");
	m_directory = directory;
}


int Logger::openfile() {
	char buffer[1024];
	
	//std::cout << "Attempting to open the log file `" << m_filename << "` for writing." << std::endl;
	std::string filepath(m_directory);
	std::string csvpath(m_directory);
	filepath.append("/").append(m_filename);
	csvpath.append("/").append(m_csvname);
		
	// check if directory to write to exists
	std::cout << "Working directory: `" << _getcwd(buffer,1024) << std::endl;
	int res = _mkdir(m_directory.c_str());
	if (res == 0) {
		std::cout << "Directory `" << m_directory << "` created successfully" << std::endl;
	}
	else if (errno == ENOENT){
		std::cout << "Directory `" << m_directory << "` failed to create due to a path error" << std::endl;
	}
	
	
	m_logfile.open(filepath, std::ios::out);
	m_csvfile.open(csvpath, std::ios::out);
	if (m_logfile.is_open()) {
		// file opened ok
		std::cout << "Log file `" << filepath << "` opened OK." << std::endl;
	} else {
		std::cout << "ERROR: Log file `" << filepath << "` did NOT open for writing!" << std::endl;
	}
	if (m_csvfile.is_open()) {
		// file opened ok
		std::cout << "Log file `" << csvpath << "` opened OK." << std::endl;
		m_csvfile << "Time, Elapsed Seconds, LogLevel, SensorID, PositionID, SongClassID, TrialNum";
		m_csvfile << midioutput.playableNotes();
		m_csvfile << std::endl;
	} 
	else {
		std::cout << "ERROR: Log file `" << csvpath << "` did NOT open for writing!" << std::endl;
	}

	if (m_csvfile.is_open() && m_logfile.is_open()) {
		return 0;
	}
	else {
		return -1;

	}



}

int Logger::closefile() {
	if (m_logfile.is_open()) {
		m_logfile.close();
	}
	if (m_csvfile.is_open()) {
		m_csvfile.close();
	}
	std::cout << "Closed log file" << std::endl;
	return 0;
}

Logger::~Logger() {
	if (m_logfile.is_open()) {
		// file is still open, need to close it
		closefile();
	}
}

int Logger::log(LogLevel lvl, std::string message) {
	std::chrono::time_point<std::chrono::system_clock> end;
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - m_start;
	if (m_logfile.is_open() && lvl >= m_curloglevel) {
		// capture current time
		time_t now = time(0);
		std::string time = "";
		tm* ltm = localtime(&now);

		char buffer[256];

		time.append(std::to_string(1900 + ltm->tm_year));
		sprintf(buffer, "%02d", 1 + ltm->tm_mon);
		time.append(buffer);
		sprintf(buffer, "%02d", ltm->tm_mday);
		time.append(buffer);
		time.append("_");
		sprintf(buffer, "%02d", ltm->tm_hour);
		time.append(buffer);
		sprintf(buffer, "%02d", ltm->tm_min);
		time.append(buffer);
		sprintf(buffer, "%02d", ltm->tm_sec);
		time.append(buffer);
		if (lvl == NOTES && m_csvfile.is_open()) {
			m_csvfile << time << ',' << elapsed_seconds.count() << "," << LogLevelString(lvl) << "," << m_sensor << "," << m_position << "," << m_songclass << "," << m_trialnum << "," << message << std::endl;
		}
		else {
			m_logfile << time << ',' << elapsed_seconds.count() << "," << LogLevelString(lvl) << "," << m_sensor << "," << m_position << "," << m_songclass << "," << m_trialnum << "," << message << std::endl;
		}
		return 0;
	}
	else {
		return -1;
	}
}
int Logger::log(LogLevel lvl, std::string m1, std::string m2) {
	std::string message = "";
	message.append(m1).append(m2);

	return Logger::log(lvl, message);
}
void Logger::setLogLevel(LogLevel lvl) {
	m_curloglevel = lvl;
}

void Logger::restartTimer() {
	m_start = std::chrono::system_clock::now();
}

void Logger::setMetaData(int sensor, int position, int songclass, int trialnum) {
	m_sensor = sensor;
	m_position = position;
	m_songclass = songclass;
	m_trialnum = trialnum;
}

Logger Log1;