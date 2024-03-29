//
// Created by yaroslav_admin on 22.10.22.
//

#ifndef MAINNDWLFU_H
#define MAINNDWLFU_H

#include <QtCore/QVariant>
#include <QtCore/QEvent>
#include <QKeyEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <QMainWindow>
#include <QFileDialog>

#include "GameWindow.hpp"
#include "TargetBlock.hpp"
#include "LevelSelectMenu.hpp"

#include "AboutForm.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow :public QMainWindow
{
public:
    void onExitButtonPush();
    GameWindow *g_window;

private:
    LevelSelectMenu* levelSelectMenu;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_LoadCustomLevel;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QWidget *widget_3;
    QStatusBar *statusbar;
    Ui::AboutForm *aboutForm;


//    bool event(QEvent *event) {
//        int key = event->//event->key() - целочисленный код клавиши
//        QString str = QString(QChar(key));
//        if (key>=Qt::Key_0 && key<=Qt::Key_9) { //Цифровые клавиши 0..9
//
//        }
//        else if (key==Qt::Key_Backspace) { //BackSpace стирает символ
//
//        }
//        else if (key==Qt::Key_Delete) { //Delete стирает всё
//
//        }
//        else if (key==Qt::Key_Plus || key==Qt::Key_Minus) {
//
//        }
//    }

public:
    void onLevelSelectButtonPushed(){
        this->levelSelectMenu->show();
    }
    void init(){
        this->setupUi();
        this->levelSelectMenu = new LevelSelectMenu();
        this->levelSelectMenu->init(this->g_window, this);
    }

    void onNewGameButtonPushed(){
        if (this->g_window->aborted_by_esc)
            this->g_window->show();
        else
            create_new_demo_game();
    }

    void onCustomLevelPlayPushed(){
        QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("Level file (*.txt *.level)"));
             //std::wcout << fileName << std::endl;
         std::cout << "selected file path : " << fileName.toStdString() << std::endl;
         if (fileName.isEmpty())
             return;
        this->g_window->play_level_by_path(fileName.toStdString());
    }
    void setupUi()
    {
        auto MainWindow = this;
        aboutForm = new Ui::AboutForm();
        aboutForm->setupUi(aboutForm);
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(640, 480);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));

        gridLayout->addWidget(widget_2, 0, 0, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(256, 16777215));
        QFont font;
        font.setPointSize(16);
        widget->setFont(font);
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 32));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(256, 16777215));
        pushButton->setFont(font);

        QObject::connect(pushButton, &QPushButton::clicked, this, &Ui_MainWindow::onNewGameButtonPushed);

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMaximumSize(QSize(256, 16777215));
        pushButton_2->setFont(font);

        QObject::connect(pushButton_2, &QPushButton::clicked, this, &Ui_MainWindow::onLevelSelectButtonPushed);

        verticalLayout->addWidget(pushButton_2);

        pushButton_LoadCustomLevel = new QPushButton(widget);

        pushButton_LoadCustomLevel->setMaximumSize(QSize(256, 16777215));
        pushButton_LoadCustomLevel->setFont(font);

        verticalLayout->addWidget(pushButton_LoadCustomLevel);

        QObject::connect(pushButton_LoadCustomLevel, &QPushButton::clicked, this, &Ui_MainWindow::onCustomLevelPlayPushed);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMaximumSize(QSize(256, 16777215));
        pushButton_4->setFont(font);
        QObject::connect(pushButton_4, &QPushButton::clicked, this, [this]() {

//             QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),
//                                                             "/home",
//                                                             ("Level file (*.txt *.level)"));
//             //std::wcout << fileName << std::endl;
//             std::cout << "selected file path : " << fileName.toStdString();
            this->aboutForm->show();
            return;
        }
        );

        verticalLayout->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(widget);
        //pushButton_3 = createButton("Exit", SIGNAL(onExitButtonPush()));
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(256, 16777215));
        pushButton_3->setFont(font);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgba(68, 24, 24,64);\n"
                                                      "color: rgb(165, 29, 45);"));
        QObject::connect(pushButton_3, &QPushButton::clicked, this, &Ui_MainWindow::onExitButtonPush);


        verticalLayout->addWidget(pushButton_3);


        gridLayout->addWidget(widget, 0, 1, 1, 1);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));

        gridLayout->addWidget(widget_3, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);


        //void objectDestroyed(QObject* obj = nullptr);
        grabKeyboard();
        //installEventFilter(eventFilter)
        MainWindow->installEventFilter(MainWindow);


    } // setupUi

private:

    void retranslateUi(Ui_MainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Arcanod main menu", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Arcanoid", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Levels", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        pushButton_LoadCustomLevel->setText(QCoreApplication::translate("MainWindow", "Load custom level", nullptr));
    } // retranslateUi

    bool eventFilter(QObject *object, QEvent *event)
    {
        if (this->g_window != nullptr and this->g_window->aborted_by_esc)
            this->pushButton->setText("Continue");
        else
            this->pushButton->setText("New Game");

        if (event->type() == QEvent::KeyPress) {
            auto* keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Escape and !this->isHidden()) {
                if (this->g_window != nullptr and this->g_window->aborted_by_esc){
                    this->g_window->show();
                    this->hide();
                    return true;
                }
                std::cout << "Exiting..." << std::endl;
                QApplication::exit(0);
                exit(0);
                return true;
            }
        }
        return QMainWindow::eventFilter(object, event);
    }


    void create_new_demo_game(){
        if (this->g_window != nullptr) {
            this->g_window->rest_game();
            //this->g_window->show();
            this->hide();
            g_window->play_level(1, false);
        }
    }

};

void Ui_MainWindow::onExitButtonPush(){
    std::cout << "Exiting..." << std::endl;
    QApplication::exit(0);
    exit(0);
};




namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINNDWLFU_H