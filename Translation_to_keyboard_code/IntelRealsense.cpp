#include "IntelRealsense.h"
// Create a simple OpenGL window for rendering:
#ifdef GUI
window app(1280, 720, "RealSense Pointcloud Example");
#endif
//glfw_state app_state;

int IntelRealsense::InitializeSensor(){
	Log1.log(Logger::LogLevel::INFO, "Attempting to start the realsense");
	//app = new window (1280, 720, "RealSense Pointcloud Example");
	// register callbacks to allow manipulation of the pointcloud
#ifdef GUI
	register_glfw_callbacks(app, app_state);
#endif
	//register_glfw_callbacks(*app, app_state);
	// p.start();
	 // Create a simple OpenGL window for rendering:
	//window app(1280, 720, "RealSense Pointcloud Example");
	// Construct an object to manage view state
	//glfw_state app_state;
	// Declare pointcloud object, for calculating pointclouds and texture mappings
	//rs2::pointcloud pc;
	// We want the points object to be persistent so we can display the last cloud when a frame drops
	//rs2::points points;

	// Declare RealSense pipeline, encapsulating the actual device and sensors
	//rs2::pipeline pipe;
	// Start streaming with default recommended configuration
	pipe.start();
	validPoints = new RealsensePointReturn;


	return 0;
}

int IntelRealsense::CloseSensor() {
	Log1.log(Logger::LogLevel::INFO, "Closing the realsense");
	Log1.hardflush();
	delete(validPoints);
	//if (app != NULL) {
	//	app->close();
	//	try {
	//		app->~window();
	//	}
	//	catch (...) {
	//		Log1.log(Logger::LogLevel::ERROR, "Window did not close correctly.");
	//	}
	//	delete(app);
	//}
	//if (app_state != NULL) {
	//	delete(app_state);
	//}
	return 0;

}



int IntelRealsense::GetPointCloud() {

	Log1.log(Logger::LogLevel::DEBUG, "In Realsense GetPointCloud");
	// Wait for the next set of frames from the camera
	//while (app) {
	Log1.log(Logger::LogLevel::DEBUG, "Never leaving Realsense GetPointCloud");

	rs2::frameset frames;
	frames = pipe.wait_for_frames();
	auto depth = frames.get_depth_frame();

	// Generate the pointcloud and texture mappings
	points = pc.calculate(depth);

	//draw_pointcloud_2((*app).width(), (*app).height(), app_state, points, 0);
	const rs2::vertex* verts = points.get_vertices();

	(*validPoints).numValid = 0;
	//rs2::vertex first = verts[0];
	// Intel Realsense D435 Spefic Decimate by 4
	//480 = total number of rows
	//848 = total num of columns
	for (int r = 160; r < 320; r += 4) {
		for (int c = 214; c < 634; c+=4)
		{
			rs2::vertex vert = verts[r*848+c];
			if (vert.z != 0) {
				(*validPoints).verts[(*validPoints).numValid] = vert;
				(*validPoints).numValid++;
				//std::cout << idx << ";" << vert.x << "," << vert.y << "," << vert.z << std::endl;
			}

		}
	}

	
	return validPoints->numValid;
}