#include "IntelRealsense.h"

int IntelRealsense::InitializeSensor(){
	Log1.log(Logger::LogLevel::INFO, "Attempting to start the realsense");
	p.start();

	return 0;
}

int IntelRealsense::CloseSensor() {
	Log1.log(Logger::LogLevel::INFO, "Closing the realsense");
	return 0;

}



double* IntelRealsense::GetPointCloud() {
	Log1.log(Logger::LogLevel::DEBUG, "In Realsense GetPointCloud");
	rs2::frameset frames = p.wait_for_frames();
	rs2::depth_frame depth = frames.get_depth_frame();
	float width = depth.get_width();
	float height = depth.get_height();
	float distance_to_center = depth.get_distance(width / 2, height / 2);
	std::cout << "The camera is facing an object " << distance_to_center << " meters away \r";
	return nullptr;
}