#include <QApplication>
#include <iostream>
#include "./GUI/GUI.h++"

#include <chrono>
#include <thread>

Ui_MainWindow* window;

void enter_main_loop()
{
    auto start = std::chrono::steady_clock::now();
    while (true){
        //++frames;
        auto now = std::chrono::steady_clock::now();
        auto diff = now - start;
        auto end = now + std::chrono::milliseconds(8);
        if(diff >= std::chrono::seconds(1))
        {
            start = now;
            std::cout << "FPS: " << frames << std::endl;

        }
        QApplication::processEvents();
        next_frame();
        if (!window->g_window->isHidden()){
            window->g_window->new_game_iteration();
        }
        if (window->g_window->isHidden() and window->isHidden())
            exit(0);

        std::this_thread::sleep_until(end);
    }
}
int main(int argc, char *argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // раскомментируйте эту строку, если используете macOS
#endif


    QApplication a(argc, argv);
    window = new Ui_MainWindow();
    std::cout << "INIT" << std::endl;
    window->g_window = new GameWindow();
    window->init();
    window->g_window->init(window);
    std::cout << "INIT DONE" << std::endl;

    window->show();

    window->g_window->show();
    QApplication::quitOnLastWindowClosed();

    auto* icon = new QIcon("../icons/Ball_triple_ico.png");
    QApplication::setWindowIcon(*icon);
    enter_main_loop();
    return 0;
    //return QApplication::exec();
}
