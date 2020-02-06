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
	Log1.flush();
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
		auto frames = pipe.wait_for_frames();

		auto color = frames.get_color_frame();
		frames = pipe.wait_for_frames();

		color = frames.get_color_frame();

		// For cameras that don't have RGB sensor, we'll map the pointcloud to infrared instead of color
		if (!color)
			color = frames.get_infrared_frame();

		// Tell pointcloud object to map to this color frame
		pc.map_to(color);

		auto depth = frames.get_depth_frame();

		// Generate the pointcloud and texture mappings
		points = pc.calculate(depth);

#ifdef GUI
		// Upload the color frame to OpenGL
		app_state.tex.upload(color);

		// Draw the pointcloud
		draw_pointcloud_2(app.width(), app.height(), app_state, points, 0);
#endif
		//draw_pointcloud_2((*app).width(), (*app).height(), app_state, points, 0);
		const rs2::vertex* verts = points.get_vertices();
		(*validPoints).numValid = 0;
		//rs2::vertex first = verts[0];
		for (int idx = 0; idx < 407040; idx++)
		{
			rs2::vertex vert = verts[idx];
			if (vert.x != 0) {
				(*validPoints).verts[(*validPoints).numValid] = vert;
				(*validPoints).numValid++;
				//std::cout << idx << ";" << vert.x << "," << vert.y << "," << vert.z << std::endl;
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