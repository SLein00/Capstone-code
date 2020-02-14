#pragma once

#ifndef TRANSLATIONTOKBD_H
#define TRANSLATIONTOKBD_H

#include <iostream>
//using namespace std;
#include <array>
#include "Logger.h"

extern Logger Log1;

struct position {
	double X;
	double Y;
	double Z;
};

class Sensor
{
public:
	//LeddarTech sensor position coordinates
	double LeddarSidepositioncoordinateX = -68.2; //AT the moment
	double LeddarSidepositioncoordinateY = 5.08;
	double LeddarSidepositioncoordinateZ = 1;
	double LeddarFrontpositioncoordinateX = 34.75;
	double LeddarFrontpositioncoordinateY = 78.2;
	double LeddarFrontpositioncoordinateZ = 1;
	double LeddarWebcampositioncoordinateX = 34.75;
	double LeddarWebcampositioncoordinateY = 41.3; //We will see
	double LeddarWebcampositioncoordinateZ = 67; //62
	double LeddarAbovepositioncoordinateX = 34.75;
	double LeddarAbovepositioncoordinateY = 5.08;
	double LeddarAbovepositioncoordinateZ = 97.3; 
	//Leap sensor position coordinates
	double LeapSidepositioncoordinateX = -15;
	double LeapSidepositioncoordinateY = 7.75;
	double LeapSidepositioncoordinateZ = 1.5;
	double LeapFrontpositioncoordinateX = 34.75;
	double LeapFrontpositioncoordinateY = 30.1;
	double LeapFrontpositioncoordinateZ = 1.5;
	double LeapWebcampositioncoordinateX = 34.75;
	double LeapWebcampositioncoordinateY = 30.1;
	double LeapWebcampositioncoordinateZ = 45;
	double LeapAbovepositioncoordinateX = 34.75;
	double LeapAbovepositioncoordinateY = 7.55;
	double LeapAbovepositioncoordinateZ = 60;
	//Realsense sensor position coordinates
	double RealsenseSidepositioncoordinateX = -7;
	double RealsenseSidepositioncoordinateY = 5.08;
	double RealsenseSidepositioncoordinateZ = 1.5;
	double RealsenseFrontpositioncoordinateX = 34.75;
	double RealsenseFrontpositioncoordinateY = 30.1;
	double RealsenseFrontpositioncoordinateZ = 1.5;
	double RealsenseWebcampositioncoordinateX = 34.75;
	double RealsenseWebcampositioncoordinateY = 30.1;
	double RealsenseWebcampositioncoordinateZ = 45;
	double RealsenseAbovepositioncoordinateX = 34.75;
	double RealsenseAbovepositioncoordinateY = 7.55;
	double RealsenseAbovepositioncoordinateZ = 60;
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
	//LeddarTech matrices
	std::array<std::array<double, 4>, 4> Leddarsidematrix = { { { 1.0, 0.0, 0.0, LeddarSidepositioncoordinateX},
							{0.0, 1.0, 0.0, LeddarSidepositioncoordinateY},
							{0.0, 0.0, 1.0, LeddarSidepositioncoordinateZ},
							{0.0, 0.0, 0.0, 1.0} } };
	//Above is a translation matrix, no rotation was needed so the rotation peice is just the identity matrix
	std::array<std::array<double, 4>, 4> Leddarfrontmatrix = { { 
							{0, 1, 0, LeddarFrontpositioncoordinateX},
							{-1, 0, 0, LeddarFrontpositioncoordinateY},
							{0, 0, 1, LeddarFrontpositioncoordinateZ},
							{0, 0, 0, 1} } };

	std::array<std::array<double, 4>, 4> Leddarwebcammatrix = { 
					{ {0, 1, 0, LeddarWebcampositioncoordinateX},
					{-.5, 0, -.8660254038, LeddarWebcampositioncoordinateY},
					{-.8660254038, 0, .5, LeddarWebcampositioncoordinateZ},
					{0, 0, 0, 1} } };//X rotation of 60 degrees
	/*{ {0, 1, 0, LeddarWebcampositioncoordinateX},
					{-.7660444431, 0, -.6427876097, LeddarWebcampositioncoordinateY},
					{-.6427876097, 0, .7660444431, LeddarWebcampositioncoordinateZ},
					{0, 0, 0, 1} }//X rotation of 40 degrees
	{ {0, 1, 0, LeddarWebcampositioncoordinateX},
					{-.6428, 0, -.766, LeddarWebcampositioncoordinateY},
					{-.766, 0, .6428, LeddarWebcampositioncoordinateZ},
					{0, 0, 0, 1} }*///X rotation of 50 degrees
	std::array<std::array<double, 4>, 4> Leddarabovematrix = 
						{ { {0, 1, 0, LeddarAbovepositioncoordinateX},
							{0, 0, -1, LeddarAbovepositioncoordinateY},
							{-1, 0, 0, LeddarAbovepositioncoordinateZ},
							{0, 0, 0, 1} } };
	//Leap matrices
	std::array<std::array<double, 4>, 4> Leapsidematrix = { { { 0.0, 1.0, 0.0, LeapSidepositioncoordinateX},
							{-1.0, 0.0, 0.0, LeapSidepositioncoordinateY},
							{0.0, 0.0, 1.0, LeapSidepositioncoordinateZ},
							{0.0, 0.0, 0.0, 1.0} } };
	std::array<std::array<double, 4>, 4> Leapfrontmatrix = { { {-1, 0, 0, LeapFrontpositioncoordinateX},
							{0, -1, 0, LeapFrontpositioncoordinateY},
							{0, 0, 1, LeapFrontpositioncoordinateZ},
							{0, 0, 0, 1} } };
	std::array<std::array<double, 4>, 4> Leapwebcammatrix = { { {1, 0, 0, LeapWebcampositioncoordinateX},
					{0, -sqrt(2) / 2, sqrt(2) / 2, LeapWebcampositioncoordinateY},
					{0, -sqrt(2) / 2, -sqrt(2) / 2, LeapWebcampositioncoordinateZ},
					{0, 0, 0, 1} } };
	std::array<std::array<double, 4>, 4> Leapabovematrix = { { {1, 0, 0, LeapAbovepositioncoordinateX},
							{0, 0, 1, LeapAbovepositioncoordinateY},
							{0, -1, 0, LeapAbovepositioncoordinateZ},
							{0, 0, 0, 1} } };
	//Realsense matrices
	std::array<std::array<double, 4>, 4> Realsensesidematrix = { { 
							{ 0.0, 0.0, 1.0, RealsenseSidepositioncoordinateX},
							{1.0, 0.0, 0.0, RealsenseSidepositioncoordinateY},
							{0.0, 1.0, 0.0, RealsenseSidepositioncoordinateZ},
							{0.0, 0.0, 0.0, 1.0} } };
	std::array<std::array<double, 4>, 4> Realsensefrontmatrix = { { {-1, 0, 0, RealsenseFrontpositioncoordinateX},
							{0, -1, 0, RealsenseFrontpositioncoordinateY},
							{0, 0, 1, RealsenseFrontpositioncoordinateZ},
							{0, 0, 0, 1} } };
	std::array<std::array<double, 4>, 4> Realsensewebcammatrix = { { {1, 0, 0, RealsenseWebcampositioncoordinateX},
					{0, -sqrt(20) / 2, sqrt(20) / 2, RealsenseWebcampositioncoordinateY},
					{0, -sqrt(20) / 2, -sqrt(20) / 2, RealsenseWebcampositioncoordinateZ},
					{0, 0, 0, 1} } };
	std::array<std::array<double, 4>, 4> Realsenseabovematrix = { { {1, 0, 0, RealsenseAbovepositioncoordinateX},
							{0, 0, 1, RealsenseAbovepositioncoordinateY},
							{0, -1, 0, RealsenseAbovepositioncoordinateZ},
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
							{0, 0, 1, 7.55},
							{0, -1, 0, 60},
							{0, 0, 0, 1} };*/
	double finalfingerposX;
	double finalfingerposY;
	double finalfingerposZ;
	Sensor();
	Sensor(double, double, double);
	void zeros();
	void matchcoordinates(double sensorposX , double sensorposY , double sensorposZ , double finposX , double finposY , double finposZ );
	position Leddarswitchtokbd(double, double, double);
	position Leapswitchtokbd(double, double, double);
	position Realsenseswitchtokbd(double, double, double);
	double getfinalX() const;
	double getfinalY() const;
	double getfinalZ() const;
};
position matrixmultiply_4x4_4x1(std::array<std::array<double, 4>, 4>, std::array<std::array<double, 1>, 4>);

#endif