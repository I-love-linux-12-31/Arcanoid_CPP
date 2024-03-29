cmake_minimum_required(VERSION 3.20)
project(Arcanoid_cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(-O3)
add_compile_options(-mcx16 -msse  -msse2 -msse3) # need CPU instructions support !!!

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Arcanoid_cpp
        main.cpp
        ./GUI/GUI.hpp
        ./GUI/MainMenu.hpp
        ./GUI/GameWindow.hpp
        ./GUI/Ball.hpp
        ./GUI/Bonuses.hpp
        ./GUI/LevelSelectMenu.hpp
        game_consts_and_globals.hpp
        fps_control.hpp
        random.hpp
        level_files_handler.hpp
        physics.hpp
        )
target_link_libraries(
        Arcanoid_cpp
        Qt::Core
        Qt::Gui
        Qt::Widgets
        glfw
        )

