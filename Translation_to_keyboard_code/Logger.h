#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#ifndef LOGGER_H
#define LOGGER_H



#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <direct.h>
#include <chrono>
#include <map>

//#include <filesystem>

class Logger
{
public:
	enum LogLevel {
		NOTES = 3,
		INFO = 1,
		WARN = 2,
		ERROR = 4
	};

	std::string LogLevelString(LogLevel e) {
		switch (e){
		case NOTES: return "Notes";
		case INFO: return "Information";
		case WARN: return "Warning!";
		case ERROR: return "ERROR!";
		default: return "UNDEFINED";
		}
	}
	

	Logger();
	Logger(std::string filename);
	Logger(std::string directory, std::string filename);
	int openfile();
	int closefile();

	int log(LogLevel lvl, std::string message);

	void setLogLevel(LogLevel lvl);

	~Logger();

	void restartTimer();

	void setMetaData(int, int, int, int);

private:
	std::string m_filename;
	std::string m_directory;
	LogLevel m_curloglevel = INFO;
	std::fstream m_logfile;
	std::chrono::time_point<std::chrono::system_clock> m_start = std::chrono::system_clock::now();
	int m_songclass = -1;
	std::string m_sensor = "Undefined";
	std::string m_position = "Undefined";
	int m_trialnum = -1;


};

#endif // !LOGGER_H