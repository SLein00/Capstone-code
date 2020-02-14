#include "IntelRealsense.h"
// Create a simple OpenGL window for rendering:
#ifdef GUI
window app(1280, 720, "RealSense Pointcloud Example");
#endif
//glfw_state app_state;

int IntelRealsense::InitializeSensor(){
	std::lock_guard<std::mutex> lck(rs2lck);
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
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_DEPTH, 848, 480, RS2_FORMAT_Z16, 90);
	pipe.start(cfg);
	validPoints = new RealsensePointReturn;


	return 0;
}

int IntelRealsense::CloseSensor() {
	std::lock_guard<std::mutex> lck(rs2lck);
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

int IntelRealsense::GetDepth(rs2::frame &depth, int id) {
	std::lock_guard<std::mutex> lck(rs2lck);
	char buf[200];
	sprintf(buf, "Getting RS2 Depth Thread %d", id);
	Log1.log(Logger::LogLevel::DEBUG, buf);
	rs2::frameset frames;
	try {
		frames = pipe.wait_for_frames();
		depth = frames.get_depth_frame();
	}
	catch (...) {
		Log1.log(Logger::LogLevel::ERROR, "Unhandled realsense depth error");
		return -1;
	}
	return 0;
}

int IntelRealsense::GetPointCloud() {
	std::lock_guard<std::mutex> lck(rs2lck);

	Log1.log(Logger::LogLevel::DEBUG, "In Realsense GetPointCloud");
	// Wait for the next set of frames from the camera
	//while (app) {
	//Log1.log(Logger::LogLevel::DEBUG, "Never leaving Realsense GetPointCloud");
	
	rs2::frameset frames;
	
	try {

		frames = pipe.wait_for_frames();

		rs2::frameset depth;
		depth = frames.get_depth_frame();
		points = pc.calculate(depth);

		const rs2::vertex* verts = points.get_vertices();
		(*validPoints).numValid = 0;
		//rs2::vertex first = verts[0];
		// Intel Realsense D435 Spefic Decimate by 4
		for (int r = 0; r < 480; r += 2) {
			for (int c = 0; c < 848; c += 2)
			{
				rs2::vertex vert = verts[r * 848 + c];
				if (vert.z != 0) {
					(*validPoints).verts[(*validPoints).numValid].X = vert.x * 100;
					(*validPoints).verts[(*validPoints).numValid].Y = vert.y * 100;
					(*validPoints).verts[(*validPoints).numValid].Z = vert.z * 100;
					(*validPoints).numValid++;
					//std::cout << idx << ";" << vert.x << "," << vert.y << "," << vert.z << std::endl;
				}


			}
		}
		

		/*rs2::frameset frames = pipe.wait_for_frames();
		rs2::depth_frame depth = frames.get_depth_frame();
		float width = depth.get_width();
		float height = depth.get_height();
		float distance_to_center = depth.get_distance(width / 2, height / 2);
		std::cout << "The camera is facing an object " << distance_to_center << " meters away \r";*/
		//}

		return validPoints->numValid;
	}
	catch (...) {
		Log1.log(Logger::LogLevel::ERROR, "Unhandled Realsense Error");
		return -1;
	}
}