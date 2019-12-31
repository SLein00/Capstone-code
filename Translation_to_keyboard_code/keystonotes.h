#pragma once

#ifndef KEYSTONOTES_H
#define KEYSTONOTES_H

#include <iostream>
#include <string>
#include "MidiNotes.h"
#include "Logger.h"
using namespace std;

extern Logger Log1;
static class Keyboard {
public:
	MidiNotesNumbers notes(double, double, double);
};

#endif
