#include "translationtokbd.h"




/* double Sensor::fingerpos[4][1] = { { fingerposX },
							{ fingerposY },
							{ fingerposZ },
							{1} }; */
	/* double sidematrix[4][4] = { { 0, 1, 0, -15},
						{-1, 0, 0, 7.55},
						{0, 0, 1, 1.5},
						{0, 0, 0, 1} };
	double frontmatrix[4][4] = { {-1, 0, 0, 34.75},
						{0, -1, 0, 30.1},
						{0, 0, 1, 1.5},
						{0, 0, 0, 1} };
	double webcammatrix[4][4] = { {1, 0, 0, 34.75},
					{0, -sqrt(20) / 2, sqrt(20) / 2, 30.1},
					{0, -sqrt(20) / 2, -sqrt(20) / 2, 45},
					{0, 0, 0, 1} };
	double abovematrix[4][4] = { {1, 0, 0, 34.75},
							{0, 0, 1, 30.1},
							{0, -1, 0, 60},
							{0, 0, 0, 1} };
	double fingerkeypos[4][1] = { {fingerkeyposX},{fingerkeyposY},{fingerkeyposZ}, {1} };
	double finalfingerposX;
	double finalfingerposY;
	double finalfingerposZ;*/


	Sensor::Sensor(double sensorposX, double sensorposY, double sensorposZ)
	{
		posX = sensorposX;
		posY = sensorposY;
		posZ = sensorposZ;
	}
	void Sensor::zeros() {
		posX = 0;
		posY = 0;
		posZ = 0;
		fingerposX = 0;
		fingerposY = 0;
		fingerposZ = 0;
		fingerkeyposX = 0;
		fingerkeyposY = 0;
		fingerkeyposZ = 0;
		finalfingerposX = 0;
		finalfingerposY = 0;
		finalfingerposZ = 0;
	}
	void Sensor::matchcoordinates(double sensorposX, double sensorposY, double sensorposZ, double finposX, double finposY, double finposZ) {
		posX = sensorposX;
		posY = sensorposY;
		posZ = sensorposZ;
		fingerposX = finposX;
		fingerposY = finposY;
		fingerposZ = finposZ;
	}

	void Sensor::switchtokbd(double finposX, double finposY, double finposZ)
	{
		if (posX == SidepositioncoordinateX && posY == SidepositioncoordinateY && posZ == SidepositioncoordinateZ )
		{
			//finpos[4][1] = { {finposX}, {finposY}, {finposZ}, {1} };
			/*finpos[0][0] = finposX;
			finpos[1][0] = finposY;
			finpos[2][0] = finposZ;
			finpos[3][0] = 1;*/
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(sidematrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			// fingerkeypos[4][1] = sidematrix[4][4] * fingerpos[4][1];
			// finalfingerposX = fingerkeypos[0][0];
			// finalfingerposY = fingerkeypos[1][0];
			//finalfingerposZ = fingerkeypos[2][0];
		}
		else if (posX == FrontpositioncoordinateX && posY == FrontpositioncoordinateY && posZ == FrontpositioncoordinateZ)
		{
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(frontmatrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			//fingerkeypos[4][1] = frontmatrix[4][4] * fingerpos[4][1];
			//finalfingerposX = fingerkeypos[0][0];
			//finalfingerposY = fingerkeypos[1][0];
			//finalfingerposZ = fingerkeypos[2][0];
		}
		else if (posX == WebcampositioncoordinateX && posY == WebcampositioncoordinateY && posZ == WebcampositioncoordinateZ)
		{
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(webcammatrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			//fingerkeypos[4][1] = webcammatrix[4][4] * fingerpos[4][1];
			//finalfingerposX = fingerkeypos[0][0];
			//finalfingerposY = fingerkeypos[1][0];
			//finalfingerposZ = fingerkeypos[2][0];
		}
		else if (posX == AbovepositioncoordinateX && posY == AbovepositioncoordinateY && posZ == AbovepositioncoordinateZ)
		{
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(abovematrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			//fingerkeypos[4][1] = abovematrix[4][4] * fingerpos[4][1];
			//finalfingerposX = fingerkeypos[0][0];
			//finalfingerposY = fingerkeypos[1][0];
			//finalfingerposZ = fingerkeypos[2][0];
		}


	}
	/*
	double getfinalX() const {
		return finalfingerposX;
	}
	double getfinalY() const {
		return finalfingerposY;
	}
	double getfinalZ() const {
		return finalfingerposZ;
	}
	*/

position matrixmultiply_4x4_4x1(std::array<std::array<double, 4>, 4> left, std::array<std::array<double, 1>, 4>right) {
	double results[4][1] = { {0},{0}, {0}, {0} };
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			results[i][0] += left[i][j] * right[j][0];
		}
	}
	
	position retval;
	retval.X = results[0][0];
	retval.Y = results[1][0];
	retval.Z = results[2][0];

	return retval;
	

		
};