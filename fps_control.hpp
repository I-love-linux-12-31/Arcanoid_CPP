//
// Created by yaroslav_admin on 31.10.22.
//


#ifndef ARCANOID_CPP_FPS_CONTROL_HPP
#define ARCANOID_CPP_FPS_CONTROL_HPP
#include <GLFW/glfw3.h>
#include <QtCore/QEvent>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>


#include <iostream>

time_t current_time;
int frames = 0;
unsigned int current_fps = 1024;

unsigned int target_fps = 60;

double lastTime = 0.0;

void next_frame(){
    double currentTime = glfwGetTime();
    double delta = currentTime - lastTime;
    frames++;

    if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
        // std::cout << "FPS :" << 1000.0/ (double)frames << std::endl;
        std::cout << "FPS alt :" << current_fps << std::endl;

        current_fps = (int)(frames / delta);
        frames = 0;
        lastTime = currentTime;
    }
    }

unsigned int get_main_thread_fps(){
    if (current_fps < 16){
        return 16;
    }
    return current_fps;
}


void set_slowmo_fps(){
    current_fps = 100000;
}


#endif //ARCANOID_CPP_FPS_CONTROL_HPP
