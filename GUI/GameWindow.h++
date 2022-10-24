//
// Created by yaroslav_admin on 22.10.22.
//

#ifndef ARCANOID_CPP_GAMEWINDOW_HPP
#define ARCANOID_CPP_GAMEWINDOW_HPP
/********************************************************************************
** Form generated from reading UI file 'game_windowuurkpL.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#include <QtCore/QVariant>
#include <QtCore/QEvent>
#include <QKeyEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QTime>
#include <QTimer>
#include "MainMenu.hpp"

QT_BEGIN_NAMESPACE

#define Form this


class GameWindow : public QWidget
{
private:
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *widget;
    QWidget *GameSpace;
    QVBoxLayout *verticalLayout_2;
    QWidget *targetsArea;
    QWidget *widget_7;
    QWidget *widget_5;
    QWidget *PlatformArea;
    QWidget *freeArea;

    QPushButton *ball;
    float ball_x = 0.0f;
    float ball_y = 0.0f;
    float ball_speed_y = 2.5f;
    float ball_speed_x = 2.5f;

    time_t time;
    int frames = 0;
    unsigned int current_fps = 256;

    float platform_x = 0.0f;
    float platform_y = 0.0f;
    const float PLATFORM_SPEED_START = 5000.0f;
    float platform_speed = 5000.5f;
    float platform_speed_multiple = 1.0f;


    int platform_weight = 256;



    QWidget *gameWindow;
    QMainWindow *mainMenu;
    QPushButton *platform;





    bool eventFilter(QObject *object, QEvent *event)
    {
        //std::cout << std::time(0) << std::endl;
        if (std::time(0) != this->time){
            this->time = std::time(0);
            std::cout << "FPS = " << this->frames << std::endl;
            this->current_fps = this->frames;
            this->frames = 0;
        }
        else {
            frames++;
        }

//        if (m_frameCount == 0) {
//            m_time.start();
//        } else {
//            printf("FPS is %f ms\n", (float)m_time. / float(m_frameCount));
//        }
//        m_frameCount++;

        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_A or keyEvent->key() == Qt::Key_Left) {
                this->platform_speed = -1.0f * this->platform_speed_multiple * this->PLATFORM_SPEED_START;
                this->move_platform();
                std::cout << "L" << std::endl;
                return true;
            }
            if (keyEvent->key() == Qt::Key_D or keyEvent->key() == Qt::Key_Right) {
                this->platform_speed = this->platform_speed_multiple * this->PLATFORM_SPEED_START;
                this->move_platform();
                std::cout << "R" << std::endl;
                return true;
            }
            if (keyEvent->key() == Qt::Key_Escape) {
                std::cout << "ESC" << std::endl;
                Form->hide();
                Form->mainMenu->show();
                return true;
            }
        }
        return QWidget::eventFilter(object, event);
    }

    void setupUi()
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(625, 726);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_3 = new QWidget(Form);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMaximumSize(QSize(16777215, 32));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(64);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_2);

        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_3);

        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_4);

        widget = new QWidget(widget_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMaximumSize(QSize(16777215, 64));

        horizontalLayout->addWidget(widget);


        verticalLayout->addWidget(widget_3);

        GameSpace = new QWidget(Form);
        GameSpace->setObjectName(QString::fromUtf8("GameSpace"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(GameSpace->sizePolicy().hasHeightForWidth());
        GameSpace->setSizePolicy(sizePolicy2);
        GameSpace->setMinimumSize(QSize(512, 256));
        GameSpace->setStyleSheet(QString::fromUtf8("background-color: rgba(51, 209, 122, 25);"));
        verticalLayout_2 = new QVBoxLayout(GameSpace);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        targetsArea = new QWidget(GameSpace);
        targetsArea->setObjectName(QString::fromUtf8("targetsArea"));
        sizePolicy2.setHeightForWidth(targetsArea->sizePolicy().hasHeightForWidth());
        targetsArea->setSizePolicy(sizePolicy2);
        targetsArea->setStyleSheet(QString::fromUtf8("background-color: rgba(64, 155, 191, 52);"));

        verticalLayout_2->addWidget(targetsArea);

        widget_7 = new QWidget(GameSpace);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_7->sizePolicy().hasHeightForWidth());
        widget_7->setSizePolicy(sizePolicy3);
        widget_7->setMaximumSize(QSize(16777215, 210));
        widget_5 = new QWidget(widget_7);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(6, 184, 601, 16));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy4);
        widget_5->setMinimumSize(QSize(16, 16));
        widget_5->setMaximumSize(QSize(16777215, 16));
        widget_5->setStyleSheet(QString::fromUtf8("background-color: rgba(68, 8, 8, 175);"));
        PlatformArea = new QWidget(widget_7);
        PlatformArea->setObjectName(QString::fromUtf8("PlatformArea"));
        PlatformArea->setGeometry(QRect(6, 144, 591, 32));
        sizePolicy4.setHeightForWidth(PlatformArea->sizePolicy().hasHeightForWidth());
        PlatformArea->setSizePolicy(sizePolicy4);
        PlatformArea->setMinimumSize(QSize(32, 32));
        PlatformArea->setMaximumSize(QSize(16777215, 32));
        PlatformArea->setStyleSheet(QString::fromUtf8("background-color: rgb(97, 53, 13);"));

        platform = new QPushButton(GameSpace);
        //platform->resize(256, 32);
        platform->setGeometry(PlatformArea->x(), PlatformArea->y(), 256, 32);


        freeArea = new QWidget(widget_7);
        freeArea->setObjectName(QString::fromUtf8("freeArea"));
        freeArea->setGeometry(QRect(10, 10, 591, 128));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(100);
        sizePolicy5.setVerticalStretch(100);
        sizePolicy5.setHeightForWidth(freeArea->sizePolicy().hasHeightForWidth());
        freeArea->setSizePolicy(sizePolicy5);
        freeArea->setMinimumSize(QSize(32, 32));
        freeArea->setMaximumSize(QSize(16777215, 128));
        freeArea->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 92, 10);"));

        ball = new QPushButton(GameSpace);
        ball->setObjectName(QString::fromUtf8("ball"));
        ball->setGeometry(QRect(270, 0, 32, 32));
        ball->setMinimumSize(QSize(0, 24));
        ball->setMaximumSize(QSize(32, 32));
        ball->setStyleSheet(QString::fromUtf8("   border-style: outset;\n"
                                              "   border-width: 8px;\n"
                                              "   border-radius: 16px;\n"
                                              "   border-color: beige;\n"
                                              "   padding: 2px;"));



        verticalLayout_2->addWidget(widget_7);


        verticalLayout->addWidget(GameSpace);


        retranslateUi();

        QMetaObject::connectSlotsByName(Form);

    } // setupUi

    void retranslateUi()
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Arcanoid", nullptr));
        label->setText(QCoreApplication::translate("Form", "Score :", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "0000", nullptr));
        label_3->setText(QCoreApplication::translate("Form", "Level :", nullptr));
        label_4->setText(QCoreApplication::translate("Form", "0000", nullptr));
        ball->setText(QCoreApplication::translate("Form", "*", nullptr));
    } // retranslateUi

    void move_ball(){
        //QPoint position = this->ball->pos();
        //position.setY(position.y() - 1);
        if (current_fps < 1)
            current_fps = 1;
        this->ball_y += this->ball_speed_y / (float)this->current_fps;
        this->ball_x += this->ball_speed_x / (float)this->current_fps;
        this->ball->setGeometry({
                                        (int)this->ball_x,
                                        (int)this->ball_y,
                                        this->ball->width(),
                                        this->ball->width()
        });
        // std::cout << this->ball->x() << std::endl;
    }

    void move_platform(){
        if (current_fps < 1)
            current_fps = 1;
        //this->platform_y += this->platform_speed / (float)this->current_fps;
        if (this->platform_speed / (float)this->current_fps < 128.0f)
            this->platform_x += this->platform_speed / (float)this->current_fps;
        else
            this->platform_x += 128.0f;
        this->platform->setGeometry((int)platform_x, (int)platform_y, platform_weight, 32);

    }

public:
    void show(){
        if (this->mainMenu != nullptr)
            this->mainMenu->hide();
        this->grabKeyboard();
        this->installEventFilter(this);
        return QWidget::show();
    }
    void hide(){
        this->releaseKeyboard();
        this->mainMenu->installEventFilter(this->mainMenu);
        return QWidget::hide();
    }
    void init(auto* window){
        this->time = std::time(0);
        this->mainMenu = window;
        this->setupUi();

        this->platform_y = (float)this->height() - 94.0f;
        this->PlatformArea->setStyleSheet("background-color: rgba(97, 53, 13, 75);");
    }

    void new_game_iteration(){
        this->move_ball();
        if (this->ball_y > (float)this->GameSpace->height() - 32.0f)
            this->ball_speed_y *= -1.0f;
        if (this->ball_y < 0.0f)
            this->ball_speed_y *= -1.0f;
        if (this->ball_x > (float)this->GameSpace->width() - 32.0f)
            this->ball_speed_x *= -1.0f;
        if (this->ball_x < 0.0f)
            this->ball_speed_x *= -1.0f;

        if (this->ball_y + 32.0f > this->platform_y and this->ball_x + 0.0f < this->platform_x + this->platform->width() and this->ball_x > this->platform_x){
            //std::cout<<"Colide" << std::endl;
            this->ball_speed_y *= -1.0f;
        }

            //this->ball_speed_y *= -1.0f;
//        if (this->ball_y < 0.0f)
//            this->ball_speed_y *= -1.0f;

    }

};

namespace Ui {
    class GameWindow: public QWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif //ARCANOID_CPP_GAMEWINDOW_HPP
