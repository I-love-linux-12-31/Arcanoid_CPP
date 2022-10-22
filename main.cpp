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

    return QApplication::exec();
}
