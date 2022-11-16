#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "./GUI/GUI.h++"
#include "./fps_control.h++"

#include "./level_files_handler.h++"

#include <ctime>

Ui_MainWindow* window;


void enter_main_loop()
{
    while (true){
        QApplication::processEvents();
        next_frame();
        if (!window->g_window->isHidden()){
            window->g_window->new_game_iteration();
        }
        if (window->g_window->isHidden() and window->isHidden())
            exit(0);
    }
}
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    window = new Ui_MainWindow();
    std::cout << "INIT" << std::endl;
    window->setupUi();
    std::cout << "INIT DONE" << std::endl;
    window->g_window = new GameWindow();
    window->g_window->init(window);

    window->show();

    window->g_window->show();
    QApplication::quitOnLastWindowClosed();



    enter_main_loop();
    return 0;
    //return QApplication::exec();
}
