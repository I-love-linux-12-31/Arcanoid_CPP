#include <QApplication>
#include <QPushButton>
#include <iostream>

#include "./GUI/GUI.h++"

Ui_MainWindow* window;

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
    while (true){
        QApplication::processEvents();
        if (!window->g_window->isHidden()){
            window->g_window->new_game_iteration();
        }

        if (window->g_window->isHidden() and window->isHidden())
            exit(0);
    }

    return QApplication::exec();
}
