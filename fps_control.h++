//
// Created by yaroslav_admin on 31.10.22.
//

#ifndef ARCANOID_CPP_FPS_CONTROL_HPP
#define ARCANOID_CPP_FPS_CONTROL_HPP
#include <QtCore/QEvent>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>


#include <iostream>

time_t current_time;
int frames = 0;
unsigned int current_fps = 512;

unsigned int target_fps = 60;

void next_frame(){
    if (std::time(0) != current_time){
        current_time = std::time(0);
        current_fps =frames;
        frames = 0;
    }
    else {
        frames++;
    }
}

bool next_frame_more_target(){
    next_frame();
    if (frames > target_fps){
        //std::cout << "FPS (Main thread) = " << frames << std::endl;
        return true;
    }
    return false;
}

unsigned int get_main_thread_fps(){
    if (current_fps < 32){
        return 32;
    }
    return current_fps;
}




#endif //ARCANOID_CPP_FPS_CONTROL_HPP
