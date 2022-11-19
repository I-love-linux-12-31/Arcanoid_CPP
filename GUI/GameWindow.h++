//
// Created by yaroslav_admin on 22.10.22.
//

#ifndef ARCANOID_CPP_GAMEWINDOW_HPP
#define ARCANOID_CPP_GAMEWINDOW_HPP

#include <QtCore/QVariant>
#include <QtCore/QEvent>
#include <QKeyEvent>
#include <QGridLayout>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QTime>
#include <QTimer>

#include<vector>
#include<string>

#include "MainMenu.hpp"
#include "../fps_control.h++"
#include "../random.h++"
#include "../level_files_handler.h++"
#include "../game_consts_and_globals.hpp"

#include "Ball.hpp"
#include "TargetBlock.hpp"
#include "Bonuses.hpp"

QT_BEGIN_NAMESPACE

#define Form this

const bool DEBUG_BACKGROUND = false;


class GameWindow : public QWidget
{
public:
    std::vector<Bonus*> bonuses;
    QWidget *GameSpace;
    float platform_x = 0.0f;
    float platform_y = 0.0f;
    float platform_speed = 5000.5f;
    float platform_speed_multiple = 1.0f;


    int platform_weight = 256;
    QPushButton *platform;


    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
private:
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;

    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *targetsArea;
    QWidget *widget_7;
    QWidget *widget_5;
    QWidget *PlatformArea;
    QWidget *freeArea;

    //QPushButton *ball;
    Ball* ball;
    float ball_x = 256.0f;
    float ball_y = 512.0f;

    const float BALL_SPEED_START = 128.0f;
    float ball_speed_y = BALL_SPEED_START;
    float ball_speed_x = BALL_SPEED_START;
    const float BALL_SIZE = 16.0f;

    time_t time;
    int frames = 0;
    unsigned int current_fps = 256;

    QWidget *gameWindow;
    QMainWindow *mainMenu;

    QGridLayout *targetsLayout;

    std::vector<std::vector<TargetBlock*>> targets;

    std::vector<Ball*> balls;





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
//        if (event->type() == QEvent::Resize){
//            std::cout << "resizeEvent !2\n";
//            this->onResize();
//        }
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_A or keyEvent->key() == Qt::Key_Left) {
                this->platform_speed = -1.0f * this->platform_speed_multiple * PLATFORM_SPEED_START;
                this->move_platform();
                return true;
            }
            if (keyEvent->key() == Qt::Key_D or keyEvent->key() == Qt::Key_Right) {
                this->platform_speed = this->platform_speed_multiple * PLATFORM_SPEED_START;
                this->move_platform();
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
        if (DEBUG_BACKGROUND)
            GameSpace->setStyleSheet(QString::fromUtf8("background-color: rgba(51, 209, 122, 25);"));
        verticalLayout_2 = new QVBoxLayout(GameSpace);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        targetsArea = new QWidget(GameSpace);
        targetsArea->setObjectName(QString::fromUtf8("targetsArea"));
        sizePolicy2.setHeightForWidth(targetsArea->sizePolicy().hasHeightForWidth());
        targetsArea->setSizePolicy(sizePolicy2);
        if (DEBUG_BACKGROUND)
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
        if (DEBUG_BACKGROUND)
            widget_5->setStyleSheet(QString::fromUtf8("background-color: rgba(68, 8, 8, 175);"));
        PlatformArea = new QWidget(widget_7);
        PlatformArea->setObjectName(QString::fromUtf8("PlatformArea"));
        PlatformArea->setGeometry(QRect(6, 144, 591, 32));
        sizePolicy4.setHeightForWidth(PlatformArea->sizePolicy().hasHeightForWidth());
        PlatformArea->setSizePolicy(sizePolicy4);
        PlatformArea->setMinimumSize(QSize(32, 32));
        PlatformArea->setMaximumSize(QSize(16777215, 32));
        if (DEBUG_BACKGROUND)
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
        if (DEBUG_BACKGROUND)
            freeArea->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 92, 10);"));

        ball = new Ball();
        ball->setParent(GameSpace);
        ball->init();
//        ball = new QPushButton(GameSpace);
//        ball->setObjectName(QString::fromUtf8("ball"));
//        ball->setGeometry(QRect(256, 256, BALL_SIZE, BALL_SIZE));
//        ball->setMinimumSize(QSize(16, 16));
//        ball->setMaximumSize(QSize(BALL_SIZE, BALL_SIZE));
//        ball->setStyleSheet(QString::fromUtf8("   border-style: outset;\n"
//                                              "   border-width: 2px;\n"
//                                              "   border-radius: 8px;\n"
//                                              "   border-color: beige;\n"
//                                              "   padding: 2px;"));
        this->balls.push_back(ball);



        verticalLayout_2->addWidget(widget_7);


        verticalLayout->addWidget(GameSpace);

        targetsLayout = new QGridLayout(targetsArea);
//        for (auto _row: this->targets){
//            for (auto target: _row) {
//                targetsLayout->addWidget(target, target->get_row(), target->get_col());
//            }
//        }


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

    void move_platform(){
        if (current_fps < 1)
            current_fps = 256;
        //this->platform_y += this->platform_speed / (float)this->current_fps;

        if (this->platform_speed / (float) this->current_fps < 128.0f)
            this->platform_x += this->platform_speed / (float) this->current_fps;
        else
            this->platform_x += 128.0f;

        if (this->platform_x <= 0.0f)
            this->platform_x = 0.0f;
        if (platform_x + (float)this->platform->width() > this->width() - 24.0f)
            this->platform_x = (float)this->width() - 24.0f - (float)this->platform->width();
        this->platform->setGeometry((int)platform_x, (int)platform_y, platform_weight, 32);


    }

    void onResize(){
        std::cout << "onResize !\n";
        this->platform_y = (float)this->height() - 94.0f;
        this->platform->setGeometry((int)platform_x, (int)platform_y, platform_weight, 32);


        for (auto block : this->targets){
            for (auto target : block) {
                float dy = (float) (this->GameSpace->height() - 256 - 8) / (float) (12) * 1.1f;
                float dx = (float) (this->GameSpace->width() - 8) / (float) (12) * 1.0f;
                float pos_y = (float) target->get_row() * dy + 4;
                float pos_x = (float) target->get_col() * dx + 4;
                target->setGeometry(pos_x, pos_y, dx, dy);
            }
        }
    }

    void create_demo_blocks(){
        for (int row = 0; row < 12;row++){
            std::vector<TargetBlock*> current_row;
            for (int col = 0; col < 12;col++){
                current_row.push_back(new TargetBlock());
                current_row[current_row.size() - 1]->set_hp(-1);
                current_row[current_row.size() - 1]->set_row(row);
                current_row[current_row.size() - 1]->set_col(col);
                current_row[current_row.size() - 1]->setParent(this->GameSpace);
                float dy = (float)(this->GameSpace->height() - 128 - 8) / (float)(12) * 1.1f;
                float dx = (float)(this->GameSpace->width() - 8) / (float)(12) * 1.0f;
                float pos_y = (float)current_row[current_row.size() - 1]->get_row() * dy + 4;
                float pos_x = (float)current_row[current_row.size() - 1]->get_col() * dx + 4;
                current_row[current_row.size() - 1]->setGeometry(pos_x, pos_y, dx, dy);

                //this->targetsLayout->addWidget(current_row[current_row.size() - 1], row, col);

            }
            this->targets.push_back(current_row);
        }
    }

    void wipe_targets_data(){
        score = 0;
        // todo : Lock main game thread ?!!!
       // int new_hp = randint(1, 4);
        for (auto block : this->targets){
//            while (!block.empty()){
//                delete block[0];
//                block.erase(block.begin());
//            }

            for (auto* element : block){
                element->set_hp(0); // randint(1, 4)
                element->update_color();

            }
        }


    }
    void load_level_data(std::string &file_path)
    {
        std::vector<std::vector<int>> data = get_map(file_path);
        for (int i = 0 ; i < this->targets.size(); i++){
            if (i >= data.size())
                continue;

            for (int j = 0 ; j < this->targets[i].size(); j++){
                if (j >= data[i].size())
                    continue;
                if (data[i][j] >= 0)
                    this->targets[i][j]->set_hp(data[i][j]);
                else {
                    this->targets[i][j]->set_bonus(true);
                    this->targets[i][j]->set_hp(data[i][j] * -1);
                }

            }
        }
    }
public:
    void update_score(){
        this->label_2->setText(std::to_string(score).c_str());
    }
    void show(){
        if (this->mainMenu != nullptr)
            this->mainMenu->hide();
        this->grabKeyboard();
        this->installEventFilter(this);
        return QWidget::show();
    }


    void resizeEvent(QResizeEvent* event) override{
        this->onResize();
        return QWidget::resizeEvent(event);

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
        if (DEBUG_BACKGROUND)
            this->PlatformArea->setStyleSheet("background-color: rgba(97, 53, 13, 75);");

        this->create_demo_blocks();
        this->wipe_targets_data();

        std::cout << "Level path :" << std::endl;
        std::string file_path = "../levels/level_b01.level";
        //std::cin >> file_path;
        load_level_data(file_path);
    }

    void new_game_iteration(){
        //this->process_ball_collisions();
        //this->move_ball();
        for (Ball* _ball : this->balls){
            _ball->process_ball_collisions(platform_x, platform_y, (float)platform->width(), (float)this->platform->height(), &targets, this->GameSpace, &this->bonuses, this->GameSpace);
            _ball->move();
        }
        for (Bonus* _bonus : this->bonuses){
            _bonus->move();
        }


    }

    void rest_game(){
        this->wipe_targets_data();
        std::cout << "Level path :" << std::endl;
        std::string file_path = "../levels/debug_b1.level";
        //std::cin >> file_path;
        load_level_data(file_path);


        this->ball_x = 256.0f;
        this->ball_y = 512.0f;

        // create_demo_blocks();
        // delete &this->targets;

        // this->resizeEvent(nullptr);
    }

};

namespace Ui {
    class GameWindow: public QWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif //ARCANOID_CPP_GAMEWINDOW_HPP
