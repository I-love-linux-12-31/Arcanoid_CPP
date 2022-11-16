cmake_minimum_required(VERSION 3.23)
project(Arcanoid_cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Arcanoid_cpp
        main.cpp
        ./GUI/GUI.h++
        ./GUI/MainMenu.hpp
        ./GUI/GameWindow.h++
        ./GUI/UIElements.h++
        fps_control.h++
        random.h++
        level_files_handler.h++
        )
target_link_libraries(Arcanoid_cpp
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

