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
Sensor::Sensor() {
	posX = 0;
	posY = 0;
	posZ = 0;
}

	Sensor::Sensor(double sensorposX, double sensorposY, double sensorposZ)
	{
		posX = sensorposX;
		posY = sensorposY;
		posZ = sensorposZ;
	}
	/*void Sensor::Leddar(double LeddarSidepositioncoordinateX, double LeddarSidepositioncoordinateY, double LeddarSidepositioncoordinateZ)
	{
		posX = LeddarSidepositioncoordinateX;
		posY = LeddarSidepositioncoordinateY;
		posZ = LeddarSidepositioncoordinateZ;
	}*/
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

	position Sensor::Leddarswitchtokbd(double finposX, double finposY, double finposZ)
	{
		Log1.log(Logger::LogLevel::DEBUG, "Translating leddar finger coordinate to keyboard");
		if (posX == LeddarSidepositioncoordinateX && posY == LeddarSidepositioncoordinateY && posZ == LeddarSidepositioncoordinateZ )
		{
			Log1.log(Logger::LogLevel::DEBUG, "In Leddar Side Position");

			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Leddarsidematrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;


		}
		else if (posX == LeddarFrontpositioncoordinateX && posY == LeddarFrontpositioncoordinateY && posZ == LeddarFrontpositioncoordinateZ)
		{
			Log1.log(Logger::LogLevel::DEBUG, "In Leddar Front Position");
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Leddarfrontmatrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;
		}
		else if (posX == LeddarWebcampositioncoordinateX && posY == LeddarWebcampositioncoordinateY && posZ == LeddarWebcampositioncoordinateZ)
		{
			Log1.log(Logger::LogLevel::DEBUG, "In Leddar Webcam Position");
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Leddarwebcammatrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;
		}
		else if (posX == LeddarAbovepositioncoordinateX && posY == LeddarAbovepositioncoordinateY && posZ == LeddarAbovepositioncoordinateZ)
		{
			Log1.log(Logger::LogLevel::DEBUG, "In Leddar Above Position");
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Leddarabovematrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;
		}


	}

	position Sensor::Leapswitchtokbd(double finposX, double finposY, double finposZ)
	{
		Log1.log(Logger::LogLevel::DEBUG, "Translating leap finger coordinate to keyboard");
		if (posX == LeapSidepositioncoordinateX && posY == LeapSidepositioncoordinateY && posZ == LeapSidepositioncoordinateZ)
		{
			Log1.log(Logger::LogLevel::DEBUG, "In leap side matrix multiplication");
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Leapsidematrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;
		}
		else if (posX == LeapFrontpositioncoordinateX && posY == LeapFrontpositioncoordinateY && posZ == LeapFrontpositioncoordinateZ)
		{
			Log1.log(Logger::LogLevel::DEBUG, "In leap front matrix multiplication");
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Leapfrontmatrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;
		}
		else if (posX == LeapWebcampositioncoordinateX && posY == LeapWebcampositioncoordinateY && posZ == LeapWebcampositioncoordinateZ)
		{
			Log1.log(Logger::LogLevel::DEBUG, "In leap webcam matrix multiplication");
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Leapwebcammatrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;
		}
		else if (posX == LeapAbovepositioncoordinateX && posY == LeapAbovepositioncoordinateY && posZ == LeapAbovepositioncoordinateZ)
		{
			Log1.log(Logger::LogLevel::DEBUG, "In leap above matrix multiplication");

			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Leapabovematrix, finpos);
			std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;
		}


	}

	position Sensor::Realsenseswitchtokbd(double finposX, double finposY, double finposZ)
	{
		if (posX == RealsenseSidepositioncoordinateX && posY == RealsenseSidepositioncoordinateY && posZ == RealsenseSidepositioncoordinateZ)
		{
			//Log1.log(Logger::LogLevel::DEBUG, "In Realsense switch to keyboard Side");
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Realsensesidematrix, finpos);
			//std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;
		}
		else if (posX == RealsenseFrontpositioncoordinateX && posY == RealsenseFrontpositioncoordinateY && posZ == RealsenseFrontpositioncoordinateZ)
		{
			//Log1.log(Logger::LogLevel::DEBUG, "In Realsense switch to keyboard Front");
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Realsensefrontmatrix, finpos);
			//std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;
		}
		else if (posX == RealsenseWebcampositioncoordinateX && posY == RealsenseWebcampositioncoordinateY && posZ == RealsenseWebcampositioncoordinateZ)
		{
			//Log1.log(Logger::LogLevel::DEBUG, "In Realsense switch to keyboard Webcam");
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Realsensewebcammatrix, finpos);
			//std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			return foo;
		}
		else if (posX == RealsenseAbovepositioncoordinateX && posY == RealsenseAbovepositioncoordinateY && posZ == RealsenseAbovepositioncoordinateZ)
		{
			//Log1.log(Logger::LogLevel::DEBUG, "In Realsense switch to keyboard Above");
			std::array<std::array<double, 1>, 4> finpos = { {{finposX}, {finposY}, {finposZ}, {1}} };

			position foo = matrixmultiply_4x4_4x1(Realsenseabovematrix, finpos);
			//std::cout << foo.X << ", " << foo.Y << ", " << foo.Z << std::endl;
			finalfingerposX = foo.X;
			finalfingerposY = foo.Y;
			finalfingerposZ = foo.Z;
			return foo;

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
			// current bottleneck
			results[i][0] += left[i][j] * right[j][0];
		}
	}
	
	position retval;
	retval.X = results[0][0];
	retval.Y = results[1][0];
	retval.Z = results[2][0];

	return retval;
	

		
};