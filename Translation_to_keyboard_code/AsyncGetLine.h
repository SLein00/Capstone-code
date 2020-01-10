#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;



//https://stackoverflow.com/questions/16592357/non-blocking-stdgetline-exit-if-no-input
//This code works perfectly well on Windows 10 in Visual Studio 2015 c++ Win32 Console Debug and Release mode.
//If it doesn't work in your OS or environment, that's too bad; guess you'll have to fix it. :(
//You are free to use this code however you please, with one exception: no plagiarism!
//(You can include this in a much bigger project without giving any credit.)
class AsyncGetline
{
public:
	//AsyncGetline is a class that allows for asynchronous CLI getline-style input
	//(with 0% CPU usage!), which normal iostream usage does not easily allow.
	AsyncGetline();
	

	//Stop getting asynchronous CLI input.
	~AsyncGetline();

	//Get the next line of input if there is any; if not, sleep for a millisecond and return an empty string.
	string GetLine();

private:
	//Cross-thread-safe boolean to tell the getline thread to stop when AsyncGetline is deconstructed.
	atomic<bool> continueGettingInput;

	//Cross-thread-safe boolean to denote when the processing thread is ready for the next input line.
	//This exists to prevent any previous line(s) from being overwritten by new input lines without
	//using a queue by only processing further getline input when the processing thread is ready.
	atomic<bool> sendOverNextLine;

	//Mutex lock to ensure only one thread (processing vs. getline) is accessing the input string at a time.
	mutex inputLock;

	//string utilized safely by each thread due to the inputLock mutex.
	string input;
};
