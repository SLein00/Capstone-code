#include "Logger.h"

extern MidiKeyboard midioutput;

Logger::Logger() {
	time_t now = time(0);
	std::string flname;
	tm *ltm = localtime(&now);

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

	sprintf(m_buffer, "Log%04d%02d%02d_%02d%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min);
	flname = m_buffer;
	m_filename = flname;
	m_filename.append(".txt");
	m_csvname = flname;
	m_csvname.append(".csv");
	m_directory = "./LogFiles";

	//arduino = new SerialPort("\\\\.\\COM3");

}

Logger::Logger(std::string filename) {
	m_filename = filename;
	m_csvname = filename.copy(m_buffer, (filename.length() > 990) ? 990 : filename.length()-4 , 0);
	m_csvname.append(".csv");
	m_directory = "./LogFiles";
}

void Logger::softflush() {
	std::lock_guard<std::mutex> lck(m_logmutex);
	if (m_logfile.is_open() && m_bufpos > 0) {
		m_logfile << m_buffer;
		m_bufpos = 0;
	}
	if (m_csvfile.is_open() && m_csvbufpos > 0) {
		m_csvfile << m_csvbuffer;
		m_csvbufpos = 0;
	}
	
}

void Logger::hardflush() {
	std::lock_guard<std::mutex> lck(m_logmutex);
	if (m_logfile.is_open() && m_bufpos > 0) {
		m_logfile << m_buffer;
		m_bufpos = 0;
		m_logfile.flush();
	}
	if (m_csvfile.is_open() && m_csvbufpos > 0) {
		m_csvfile << m_csvbuffer;
		m_csvbufpos = 0;
		m_csvfile.flush();
	}

}

Logger::Logger(std::string directory, std::string filename) {
	m_filename = filename;

	m_csvname = filename.copy(m_buffer, (filename.length() > 990) ? 990 : filename.length() - 4, 0);
	m_csvname.append(".csv");
	m_directory = directory;
}


int Logger::openfile() {
	std::lock_guard<std::mutex> lck(m_logmutex);
	//std::cout << "Attempting to open the log file `" << m_filename << "` for writing." << std::endl;
	std::string filepath(m_directory);
	std::string csvpath(m_directory);
	filepath.append("/").append(m_filename);
	csvpath.append("/").append(m_csvname);
	m_bufpos = 0;
	// check if directory to write to exists
	//std::cout << "Working directory: `" << _getcwd(buffer,1024) << std::endl;
	_getcwd(m_smallbuffer, m_smallbuffersize);
	m_bufpos += sprintf(m_buffer, "Working Directory: `%s`\n", m_smallbuffer);
	int res = _mkdir(m_directory.c_str());
	if (res == 0) {
		//std::cout << "Directory `" << m_directory << "` created successfully" << std::endl;
		m_bufpos += sprintf(m_buffer + m_bufpos, "Directory `%s` created successfully.\n", m_directory.c_str());
	}
	else if (errno == ENOENT){
		//std::cout << "Directory `" << m_directory << "` failed to create due to a path error" << std::endl;
		m_bufpos += sprintf(m_buffer + m_bufpos, "Directory `%s` FAILED to create due to a path error.\n", m_directory.c_str());
	}
	
	
	m_logfile.open(filepath, std::ios::out);
	m_csvfile.open(csvpath, std::ios::out);
	if (m_logfile.is_open()) {
		// file opened ok
		//std::cout << "Log file `" << filepath << "` opened OK." << std::endl;
		m_bufpos += sprintf(m_buffer + m_bufpos, "Log File `%s` opened OK.\n", filepath.c_str());
	} else {
		//std::cout << "ERROR: Log file `" << filepath << "` did NOT open for writing!" << std::endl;
		m_bufpos += sprintf(m_buffer + m_bufpos, "Log File `%s` did NOT open for writing.\n", filepath.c_str());
	}
	if (m_csvfile.is_open()) {
		// file opened ok
		//std::cout << "Log file `" << csvpath << "` opened OK." << std::endl;
		m_bufpos += sprintf(m_buffer + m_bufpos, "CSV File `%s` opened OK.\n", csvpath.c_str());
		m_csvfile << "Time, Elapsed Seconds, LogLevel, SensorID, PositionID, SongClassID, TrialNum";
		m_csvfile << midioutput.playableNotes();
		m_csvfile << std::endl;
	} 
	else {
		//std::cout << "ERROR: Log file `" << csvpath << "` did NOT open for writing!" << std::endl;
		m_bufpos += sprintf(m_buffer + m_bufpos, "CSV File `%s` did NOT open for writing.\n", csvpath.c_str());
	}

	if (m_logfile.is_open() && m_bufpos > 0) {
		m_logfile << m_buffer;
		m_bufpos = 0;
		m_logfile.flush();
	}
	if (m_csvfile.is_open() && m_csvbufpos > 0) {
		m_csvfile << m_csvbuffer;
		m_csvbufpos = 0;
		m_csvfile.flush();
	}

	arduino = new SerialPort("COM3", 115200);
	//arduino->Initialize("COM3", 115200);


	if (m_csvfile.is_open() && m_logfile.is_open()) {
		return 0;
	}
	else {
		return -1;

	}



}

int Logger::closefile() {
	std::lock_guard<std::mutex> lck(m_logmutex);
	if (m_logfile.is_open()) {
		if (m_bufpos > 0) {
			m_logfile << m_buffer;
			m_bufpos = 0;
		}
		m_logfile.close();
	}
	if (m_csvfile.is_open()) {
		if (m_csvbufpos > 0) {
			m_csvfile << m_csvbuffer;
			m_csvbufpos = 0;
		}
		m_csvfile.close();
	}
	std::cout << "Closed log file" << std::endl;
	return 0;
}

Logger::~Logger() {
	std::lock_guard<std::mutex> lck(m_logmutex);
	if (m_logfile.is_open()) {
		// file is still open, need to close it
		closefile();
	}
}

int Logger::log(LogLevel lvl, float sx, float sy, float sz, float fx, float fy, float fz) {
	char buf[1000];
	sprintf(buf, "Sensor: X %.2f, Y %.2f, Z %.2f;  FFP: X %.2f, Y %.2f, Z %.2f", sx, sy, sz, fx, fy, fz);
	return log(lvl, buf);
}

int Logger::log(LogLevel lvl, int tid, float sx, float sy, float sz, float fx, float fy, float fz) {
	char buf[1000];
	sprintf(buf, "ThreadID: %d;  Sensor: X %.2f, Y %.2f, Z %.2f;  FFP: X %.2f, Y %.2f, Z %.2f", tid, sx, sy, sz, fx, fy, fz);
	return log(lvl, buf);
}


int Logger::log(LogLevel lvl, std::string message) {
	std::lock_guard<std::mutex> lck(m_logmutex);
	if (lvl >= m_curloglevel) {
		std::chrono::time_point<std::chrono::system_clock> end;
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - m_start;
		if (lvl == NOTES && m_csvfile.is_open()) {
			// capture current time
			time_t now = time(0);
			tm* ltm = localtime(&now);
			m_csvbufpos += sprintf(m_csvbuffer+m_csvbufpos, "%04d%02d%02d_%02d%02d%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

			//m_csvfile << time << ',' << elapsed_seconds.count() << "," << LogLevelString(lvl) << "," << m_sensor << "," << m_position << "," << m_songclass << "," << m_trialnum << "," << message << std::endl;
			m_csvbufpos += sprintf(m_csvbuffer + m_csvbufpos, ",%f,%s,%d,%d,%d,%d,%s\n", elapsed_seconds.count(), LogLevelString(lvl).c_str(), m_sensor, m_position, m_songclass, m_trialnum, message.c_str());
			//m_csvfile << m_csvbuffer;

			if (m_csvbufpos > m_csvbufferflushlimit) {
				m_csvfile << m_csvbuffer;
				m_csvbufpos = 0;
			}

			if (arduino->isConnected()) {
				char smbuf[10];
				sprintf(smbuf, "%.2f", elapsed_seconds.count());
				//sprintf(smbuf, "abc.00\n");
				smbuf[5] = '\n';
				arduino->transmit(smbuf, 6);
			}
			return 0;
		}
		else if (m_logfile.is_open()) {
			// capture current time
			time_t now = time(0);
			tm* ltm = localtime(&now);
			m_bufpos += sprintf(m_buffer+m_bufpos, "%04d%02d%02d_%02d%02d%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

			//m_csvfile << time << ',' << elapsed_seconds.count() << "," << LogLevelString(lvl) << "," << m_sensor << "," << m_position << "," << m_songclass << "," << m_trialnum << "," << message << std::endl;
			m_bufpos += sprintf(m_buffer + m_bufpos, ",%f,%s,%d,%d,%d,%d,%s\n", elapsed_seconds.count(), LogLevelString(lvl).c_str(), m_sensor, m_position, m_songclass, m_trialnum, message.c_str());
			//m_logfile << m_buffer;

			if (m_bufpos > m_bufferflushlimit) {
				m_logfile << m_buffer;
				m_bufpos = 0;
			}
			return 0;


			return 0;
		} else {
			return -1;
		}

	}
	else {
		return 0;
	}
}

int Logger::log(LogLevel lvl, std::string m1, std::string m2) {
	std::string message = "";
	message.append(m1).append(m2);

	return Logger::log(lvl, message);
}

int Logger::log(LogLevel lvl, std::string m1, std::string m2, int tid) {
	std::string message = "";
	message.append(m1).append(m2).append(std::to_string(tid));

	return Logger::log(lvl, message);
}

void Logger::setLogLevel(LogLevel lvl) {
	std::lock_guard<std::mutex> lck(m_logmutex);
	m_curloglevel = lvl;
}

void Logger::restartTimer() {
	std::lock_guard<std::mutex> lck(m_logmutex);
	m_start = std::chrono::system_clock::now();
}

void Logger::setMetaData(int sensor, int position, int songclass, int trialnum) {
	m_sensor = sensor;
	m_position = position;
	m_songclass = songclass;
	m_trialnum = trialnum;
}

Logger Log1;