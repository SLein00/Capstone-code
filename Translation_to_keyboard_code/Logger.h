#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

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
		NOTES = 0,
		INFO = 1,
		WARN = 2,
		ERROR = 3
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

	~Logger();



private:
	void init();
	std::string m_filename;
	std::string m_directory;
	LogLevel m_curloglevel = NOTES;
	std::fstream m_logfile;
	std::chrono::time_point<std::chrono::system_clock> m_start = std::chrono::system_clock::now();
};

