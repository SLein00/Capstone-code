#pragma once
#ifndef INTELREALSENSEH
#define INTELREALSENSEH

#include "SensorBase.h"
#include <iostream>
//#include "librealsense2/rs.hpp"
#include "RSHelper.h"
#include "Logger.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"


extern Logger Log1;

class IntelRealsense :
	public SensorBase
{
public:
	int InitializeSensor();
	int CloseSensor();
	double* GetPointCloud();

    window* app = NULL;
    glfw_state* app_state = NULL;

    ~IntelRealsense() {
        Log1.flush();
        
        //if (app != NULL) {
        //    app->close();
        //    try {
        //        app->~window();
        //    }
        //    catch (...) {
        //        Log1.log(Logger::LogLevel::ERROR, "Window did not close correctly.");
        //    }
        //    delete(app);
        //}
        //if (app_state != NULL) {
        //    delete(app_state);
        //}
    }

private:
		rs2::pipeline pipe;
        // Declare pointcloud object, for calculating pointclouds and texture mappings
        rs2::pointcloud pc;
        // We want the points object to be persistent so we can display the last cloud when a frame drops
        rs2::points points;

        void * p_window_app;
        void * p_app2_state;
       
};
#endif // !INTELREALSENSEH
