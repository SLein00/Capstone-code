#pragma once

#ifndef KEYSTONOTES_H
#define KEYSTONOTES_H

#include <iostream>
#include <string>
#include "MidiNotes.h"
using namespace std;


static class Keyboard {
public:
	MidiNotes notes(double, double, double);
};

#endif
