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
#include "MidiKeyboard.h"
#include <thread>
#include <mutex>

//#include <filesystem>

class Logger
{
public:
	enum LogLevel {
		NOTES = 4,
		INFO = 2,
		WARN = 3,
		ERROR = 5,
		DEBUG = 1
	};

	std::string LogLevelString(LogLevel e) {
		switch (e){
		case NOTES: return "Notes";
		case INFO: return "Information";
		case WARN: return "Warning!";
		case ERROR: return "ERROR!";
		case DEBUG: return "DEBUG!";
		default: return "UNDEFINED";
		}
	}
	

	Logger();
	Logger(std::string filename);
	Logger(std::string directory, std::string filename);
	int openfile();
	int closefile();

	int log(LogLevel lvl, std::string message);

	int log(LogLevel lvl, std::string m1, std::string m2);

	void setLogLevel(LogLevel lvl);

	~Logger();

	void hardflush();
	void softflush();

	void restartTimer();

	void setMetaData(int, int, int, int);

private:
	mutable std::mutex m_logmutex;


	std::string m_filename;
	std::string m_csvname;
	std::string m_directory;
	LogLevel m_curloglevel = DEBUG;
	std::fstream m_logfile;
	std::fstream m_csvfile;
	std::chrono::time_point<std::chrono::system_clock> m_start = std::chrono::system_clock::now();
	int m_songclass = -1;
	//std::string m_sensor = "Undefined";
	//std::string m_position = "Undefined";
	int m_sensor = -1;
	int m_position = -1;
	int m_trialnum = -1;

	static const int m_smallbuffersize = 2000;
	uint_fast32_t m_smallbufpos = 0;
	char m_smallbuffer[m_smallbuffersize];

	static const int m_buffersize = 250000;
	uint_fast32_t m_bufpos = 0;
	char m_buffer[m_buffersize];
	static const int m_bufferflushlimit = m_buffersize - 20000;

	static const int m_csvbuffersize = 250000;
	uint_fast32_t m_csvbufpos = 0;
	char m_csvbuffer[m_csvbuffersize];
	static const int m_csvbufferflushlimit = m_buffersize - 20000;
};

#endif // !LOGGER_H