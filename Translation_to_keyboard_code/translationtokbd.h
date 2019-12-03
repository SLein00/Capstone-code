#pragma once

#ifndef TRANSLATIONTOKBD_H
#define TRANSLATIONTOKBD_H

#include <iostream>
//using namespace std;
#include <array>
struct position {
	double X;
	double Y;
	double Z;
};

class Sensor
{
public:
	double posX;
	double posY;
	double posZ;
	double fingerposX;
	double fingerposY;
	double fingerposZ;
	double finpos[4][1] = { {0}, {0}, {0}, {0} };
	double fingerkeyposX;
	double fingerkeyposY;
	double fingerkeyposZ;
	std::array<std::array<double, 4>, 4> sidematrix = { { { 0.0, 1.0, 0.0, -15.0},
							{-1.0, 0.0, 0.0, 7.55},
							{0.0, 0.0, 1.0, 1.5},
							{0.0, 0.0, 0.0, 1.0} } };
	std::array<std::array<double, 4>, 4> frontmatrix = { { {-1, 0, 0, 34.75},
							{0, -1, 0, 30.1},
							{0, 0, 1, 1.5},
							{0, 0, 0, 1} } };
	std::array<std::array<double, 4>, 4> webcammatrix = { { {1, 0, 0, 34.75},
					{0, -sqrt(20) / 2, sqrt(20) / 2, 30.1},
					{0, -sqrt(20) / 2, -sqrt(20) / 2, 45},
					{0, 0, 0, 1} } };
	std::array<std::array<double, 4>, 4> abovematrix = { { {1, 0, 0, 34.75},
							{0, 0, 1, 30.1},
							{0, -1, 0, 60},
							{0, 0, 0, 1} } };

	/*double sidematrix[4][4] = { { 0.0, 1.0, 0.0, -15.0},
							{-1.0, 0.0, 0.0, 7.55},
							{0.0, 0.0, 1.0, 1.5},
							{0.0, 0.0, 0.0, 1.0} };*/
	/*double frontmatrix[4][4] = { {-1, 0, 0, 34.75},
						{0, -1, 0, 30.1},
						{0, 0, 1, 1.5},
						{0, 0, 0, 1} };*/
	/*double webcammatrix[4][4] = { {1, 0, 0, 34.75},
					{0, -sqrt(20) / 2, sqrt(20) / 2, 30.1},
					{0, -sqrt(20) / 2, -sqrt(20) / 2, 45},
					{0, 0, 0, 1} };*/
	/*double abovematrix[4][4] = { {1, 0, 0, 34.75},
							{0, 0, 1, 30.1},
							{0, -1, 0, 60},
							{0, 0, 0, 1} };*/
	double finalfingerposX;
	double finalfingerposY;
	double finalfingerposZ;
	Sensor(double, double, double);
	void zeros();
	void matchcoordinates(double sensorposX , double sensorposY , double sensorposZ , double finposX , double finposY , double finposZ );
	void switchtokbd(double, double, double);
	double getfinalX() const;
	double getfinalY() const;
	double getfinalZ() const;
};
position matrixmultiply_4x4_4x1(std::array<std::array<double, 4>, 4>, std::array<std::array<double, 1>, 4>);
#endif