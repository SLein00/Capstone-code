#include "Logger.h"

Logger::Logger() {
	time_t now = time(0);
	std::string flname = "Log";
	tm *ltm = localtime(&now);

	char buffer[256];

	flname.append(std::to_string(1900 + ltm->tm_year));
	sprintf(buffer, "%02d", 1 + ltm->tm_mon);
	flname.append(buffer);
	sprintf(buffer, "%02d", ltm->tm_mday);
	flname.append(buffer);
	flname.append("_");
	sprintf(buffer, "%02d", ltm->tm_hour);
	flname.append(buffer);
	sprintf(buffer, "%02d", ltm->tm_min);
	flname.append(buffer);
	flname.append(".txt");
	m_filename = flname;
	m_directory = "./LogFiles";
}

Logger::Logger(std::string filename) {
	m_filename = filename;
	m_directory = "./LogFiles";
}

Logger::Logger(std::string directory, std::string filename) {
	m_filename = filename;
	m_directory = directory;
}


int Logger::openfile() {
	char buffer[1024];
	
	//std::cout << "Attempting to open the log file `" << m_filename << "` for writing." << std::endl;
	std::string path(m_directory);
	path.append("/").append(m_filename);
		
	// check if directory to write to exists
	std::cout << "Working directory: `" << _getcwd(buffer,1024) << std::endl;
	int res = _mkdir(m_directory.c_str());
	if (res == 0) {
		std::cout << "Directory `" << m_directory << "` created successfully" << std::endl;
	}
	else if (errno == ENOENT){
		std::cout << "Directory `" << m_directory << "` failed to create due to a path error" << std::endl;
	}
	
	
	m_logfile.open(path, std::ios::out);
	if (m_logfile.is_open()) {
		// file opened ok
		std::cout << "Log file `" << path << "` opened OK." << std::endl;
		return 0;
	} else {
		std::cout << "ERROR: Log file `" << path << "` did NOT open for writing!" << std::endl;
		return -1;
	}
}

int Logger::closefile() {
	if (m_logfile.is_open()) {
		m_logfile.close();
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
		
		m_logfile << time << ',' << elapsed_seconds.count() << "," << LogLevelString(lvl) << "," << message <<  std::endl;

		return 0;
	}
	else {
		return -1;
	}
}

void Logger::setLogLevel(LogLevel lvl) {
	m_curloglevel = lvl;
}