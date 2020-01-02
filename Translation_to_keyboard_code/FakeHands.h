#pragma once
#ifndef FAKEHANDSH
#define FAKEHANDSH

#include "SensorBase.h"
#include <random>
#include <array>
#include "Logger.h"
#include "MidiNotes.h"
#include <string>

extern Logger Log1;


class FakeHands :
	public SensorBase
{
public:
	int InitializeSensor();
	int CloseSensor();
	std::array<MidiNotesNumbers, 10> GetValues(int SongType);

private:
	int lefthandbasepos;
	int righthandbasepos;
	bool startedplaying = false;
	std::array<int, 5> lefthandfingerpos;
	std::array<int, 5> righthandfingerpos;

	std::default_random_engine generator;
	std::normal_distribution<double> nhanddistribution;
	std::normal_distribution<double> nfingerdistribution;

	MidiNotesNumbers convinttonote(int in);
};

#endif