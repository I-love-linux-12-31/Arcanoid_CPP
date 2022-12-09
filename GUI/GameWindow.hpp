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
#include <QMessageBox>

#ifndef MAINNDWLFU_H
#include "MainMenu.hpp"
#endif

#include "../fps_control.hpp"
#include "../random.hpp"
#include "../level_files_handler.hpp"
#include "../game_consts_and_globals.hpp"

#include "Ball.hpp"
#include "TargetBlock.hpp"
#include "Bonuses.hpp"
#include "../physics.hpp"

QT_BEGIN_NAMESPACE

#define Form this

const bool DEBUG_BACKGROUND = false;


class GameWindow : public QWidget
{
public:
    bool aborted_by_esc = false;
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
    int level_number = 0;
    bool level_bonus = false;
    std::string _level_path = "";

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

    const float BALL_SIZE = 16.0f;

    time_t time;
    int frames = 0;
    unsigned int current_fps = 256;

    QMainWindow *mainMenu;

    std::vector<std::vector<TargetBlock*>*> targets;

    std::vector<Ball*> balls;





    bool eventFilter(QObject *object, QEvent *event)
    {
        //std::cout << std::time(0) << std::endl;
        if (std::time(nullptr) != this->time){
            this->time = std::time(nullptr);
            std::cout << "FPS = " << this->frames << std::endl;
            this->current_fps = this->frames;
            this->frames = 0;
        }
        else {
            frames++;
        }

        if (event->type() == QEvent::KeyPress) {
            auto* keyEvent = dynamic_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_A or keyEvent->key() == Qt::Key_Left) {
                this->platform_speed = -1.0f * this->platform_speed_multiple * PLATFORM_SPEED_START;
                this->move_platform();
            }
            if (keyEvent->key() == Qt::Key_D or keyEvent->key() == Qt::Key_Right) {
                this->platform_speed = this->platform_speed_multiple * PLATFORM_SPEED_START;
                this->move_platform();
            }
            if (keyEvent->key() == Qt::Key_Escape) {
                std::cout << "ESC" << std::endl;
                Form->hide();
                Form->mainMenu->show();
                this->aborted_by_esc = true;
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
        platform->setEnabled(false);
        //platform->resize(256, 32);
        platform->setGeometry(PlatformArea->x(), PlatformArea->y(), 256, 32);
        platform->setStyleSheet(QString::fromUtf8("border-style: outset;\n"
                                                  "border-width: 4px;\n"
                                                  "border-radius: 8px;\n"
                                                  "border-color: #888899;\n"
                                                  "padding: 6px;\n"
                                                  "background-color: rgb(153, 193, 241);"));


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

        if (abs(this->platform_speed) / (float) get_main_thread_fps() < 128.0f)
            this->platform_x += this->platform_speed / (float) get_main_thread_fps();
        else
            this->platform_x += 128.0f;

        if (this->platform_x <= 0.0f)
            this->platform_x = 0.0f;
        if (platform_x + (float)this->platform->width() > (float)this->width() - 24.0f)
            this->platform_x = (float)this->width() - 24.0f - (float)this->platform->width();
        this->platform->setGeometry((int)platform_x, (int)platform_y, platform_weight, 32);


    }

    void onResize(){
        std::cout << "onResize !\n";
        this->platform_y = (float)this->height() - 94.0f;
        this->platform->setGeometry((int)platform_x, (int)platform_y, platform_weight, 32);


        for (auto block : this->targets){
            for (auto target : *block) {
                float dy = (float) (this->GameSpace->height() - 256 - 8) / (float) (this->targets.size()) * 1.1f;
                float dx = (float) (this->GameSpace->width() - 8) / (float) (this->targets[0]->size()) * 1.0f;
                float pos_y = (float) target->get_row() * dy + 4;
                float pos_x = (float) target->get_col() * dx + 4;
                target->setGeometry((int)pos_x, (int)pos_y, (int)dx, (int)dy);
                std::cout << "RESIZE ::" << (int)pos_x << " " << (int)pos_y << " " << (int)dx << " " << (int)dy << std::endl;
            }
        }
    }



    void wipe_targets_data(){
        this->platform_weight = 256;
        score = 0;
        for (int n = 0 ; n < this->bonuses.size(); n++){
            delete this->bonuses[n];
        }
        this->bonuses.clear();

        for (auto* block : this->targets) {
            // WTF block is vector<vector> !!!
            for (int i = 0; i < block->size(); i++) {
                for (int j = 0; j < block[i].size(); j++)
                    delete block[i][j];
                block[i].clear();

            }
            block->clear();
        }
        this->targets.clear();


    }
    bool is_lose(){
        return this->balls.empty();
    }
    bool is_win(){
        if (
                std::all_of(
                        this->targets.begin(),
                        this->targets.end(),
                        [](std::vector<TargetBlock *>* line)
                        {
                            return std::all_of(line->begin(), line->end(),
                                               [](TargetBlock* i)
                                               {
                                                   return i->is_dead();
                                               }
                                               );
                        }))
        {
            return true;
        }
        return false;
    }


    void check_win_or_lose(){
        int return_code;
        if (this->is_win()){
            std::cout << "You win !!!" << std::endl;
            this->aborted_by_esc = false;
            return_code = QMessageBox::information(this, "Win", "Level completed !", QMessageBox::Ok | QMessageBox::Close);
            if (return_code == QMessageBox::Ok){
                if (this->level_number < get_main_levels_count() and !this->level_bonus or
                this->level_number < get_bonus_levels_count() and this->level_bonus) {
                    std::cout << "Next level!" << std::endl;
                    this->play_level(this->level_number + 1, this->level_bonus);
                }
                else{
                    std::cout << "Last level completed !!!" << std::endl;
                    return_code = QMessageBox::warning(this, "THE END!", "You win! It was last level.", QMessageBox::Escape);
                    this->hide();
                    this->mainMenu->show();
                }
            }
            else { // return_code == QMessageBox::Escape
                std::cout << "Escape to main menu!" << std::endl;
                this->hide();
                this->mainMenu->show();
            }
        }
        if (this->is_lose()){
            this->aborted_by_esc = true;
            return_code = QMessageBox::information(this, "GameOver", "You lose !", QMessageBox::Retry | QMessageBox::Close);
            if (return_code == QMessageBox::Retry){
                std::cout << "Retrying..." << std::endl;
                //this->rest_game();
                if (!this->_level_path.empty())
                    this->play_level_by_path(this->_level_path);
                else
                    this->play_level(this->level_number, this->level_bonus);

            }
            else {
                this->mainMenu->show();
                this->hide();
            }
        }


    }
    void load_level_data(std::string &file_path, int _level_number = 0, bool _is_bonus_level = false)
    {
        this->rest_game();
        this->ball->set_y(this->platform_y - 128);
        this->ball->set_x(this->platform_x);
        std::vector<std::vector<int>> data = get_map(file_path);

        //this->targets.clear();
        for (int i = 0 ; i < data.size(); i++){
            this->targets.push_back(new std::vector<TargetBlock*>());
            for (int j = 0 ; j < data[0].size(); j++){
                this->targets[i]->push_back(new TargetBlock());
                (*this->targets[i])[j]->setParent(this->GameSpace);
                (*this->targets[i])[j]->set_row(i);
                (*this->targets[i])[j]->set_col(j);
                if (data[i][j] >= 0) {
                    (*this->targets[i])[j]->set_bonus(false);
                    (*this->targets[i])[j]->set_hp(data[i][j]);
                }
                else {
                    (*this->targets[i])[j]->set_bonus(true);
                    (*this->targets[i])[j]->set_hp(data[i][j] * -1);
                }

            }
        }

        this->level_bonus = _is_bonus_level;
        this->level_number = _level_number;
        ball->rest_speed();
        this->move_platform();

        this->onResize();
    }

    void apply_bonus_triple_ball(bool _recursion = false){
        float k = 1.5f;
        int iteration = 0;
        Ball* _ball = new Ball();
        _ball->set_id((int)this->balls.size());
        _ball->setParent(this->GameSpace);
//        this->balls[this->balls.size() - 1]->x() + (float)(randint((int)BALL_SIZE, (int)(BALL_SIZE * 1.5f))) * get_random_inversion() <<
//        " $$$ " <<
//        this->balls[this->balls.size() - 1]->y() + (float)(randint((int)BALL_SIZE, (int)(BALL_SIZE * 1.5f))) * get_random_inversion()<< std::endl;
        _ball->init(
                (int)this->balls[this->balls.size() - 1]->get_x() + (randint((int)BALL_SIZE,(int)(BALL_SIZE * 1.5f))) * (int)get_random_inversion(),
                (int)this->balls[this->balls.size() - 1]->get_y() + (randint((int)BALL_SIZE, (int)(BALL_SIZE * 1.5f))) * (int)get_random_inversion());
        this->ball->change_movement_vector((int)this->balls[this->balls.size() - 1]->get_x(), (int)this->balls[this->balls.size() - 1]->get_y());
        bool good_spawn = false;
        while(!good_spawn){
            iteration++;
            good_spawn = true;
            for (Ball* other_ball : this->balls){
                if (is_collide(other_ball, _ball)){
                    std::cout << "Spawn collide with ball №" << other_ball->get_id() << std::endl;
                    good_spawn = false;
                }
            }
            if (!good_spawn){
                std::cout << "Failed to plant new ball at :" << _ball->get_x() << ", " << _ball->get_y() << std::endl;
                if (iteration > 16 and k < 50.0f){
                    iteration = 0;
                    k += 0.2f;
                }
                _ball->set_y((float)this->balls[this->balls.size() - 1]->y() + (float)(randint((int)BALL_SIZE, (int)(BALL_SIZE * k))) * get_random_inversion());
                _ball->set_x((float)this->balls[this->balls.size() - 1]->x() + (float)(randint((int)BALL_SIZE, (int)(BALL_SIZE * k))) * get_random_inversion());
            }
        }
        _ball->show();

        //_ball->set_x((float)this->balls[0]->x());
        //_ball->set_y((float)this->balls[0]->y());
        if (!_recursion)
            this->apply_bonus_triple_ball(true);
        this->balls.push_back(_ball);
    }
public:
    void play_level(unsigned int level_id, bool bonus = false){
        this->_level_path = "";
        std::cout << "Loading level ..." << std::endl;
        std::string level_path = get_level_path_by_id((int)level_id, bonus);
        if (bonus)
            this->label_4->setText(("Bonus " + std::to_string(level_id)).c_str());
        else
            this->label_4->setText(std::to_string(level_id).c_str());
        this->load_level_data(level_path, (int)level_id, bonus);
        this->show();

    }
    void play_level_by_path(std::string _filepath){
        this->_level_path = _filepath;
        std::cout << "Loading level by path..." << std::endl;
        this->label_4->setText(("Custom level: " + _filepath).c_str());
        this->load_level_data(_filepath);
        this->show();

    }
    void update_score(){
        this->label_2->setText(std::to_string(score).c_str());
    }
    void show(){
        if (this->mainMenu != nullptr)
            this->mainMenu->hide();
        this->grabKeyboard();
        this->installEventFilter(this);
        for (auto* ball : this->balls){
            ball->freeze_ball();
        }
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

        // this->create_demo_blocks();
        this->wipe_targets_data();

        std::cout << "Level path :" << std::endl;
        std::string file_path = "../levels/level_b01.level";
        //std::cin >> file_path;
        load_level_data(file_path);
    }

    void new_game_iteration(){
        //this->process_ball_collisions();
        //this->move_ball();
        //startBallsProcessing:
        for (int i; i < this->balls.size();i++){
        // for (Ball* _ball : this->balls){
            Ball* _ball = this->balls[i];
            _ball->process_ball_collisions(platform_x, platform_y, (float)platform->width(), (float)this->platform->height(), &this->targets, this->GameSpace, &this->bonuses, this->GameSpace);
            _ball->process_ball_collisions_with_other_balls(&this->balls);
            _ball->move();
            if(_ball->y() + _ball->height() > (int)this->platform_y + platform->height()){
                if (this->balls[i] != this->ball)
                {
                    this->balls[i]->hide();
                    delete this->balls[i];
                }
                else {
                    this->ball->set_y(-64);
                }
                this->balls.erase(this->balls.begin() + i);
                //goto startBallsProcessing;
                return this->new_game_iteration();
            }
            std::cout << "";
        }
        for (Bonus* _bonus : this->bonuses){
            _bonus->move();
        }

        update_score();
        process_bonus_collisions();
        check_win_or_lose();

    }
    bool check_bonus_collisions(Bonus* bonus){
        if (bonus->isHidden() or bonus->to_delete)
            return false;
        if (is_collide(bonus, this->platform)){
            std::cout << "Bonus collide !" << std::endl;
            bonus->hide();
            bonus->to_delete = true;
            return true;
        }
        return false;
    }

    void process_bonus_collisions(){
        for (auto bonus : bonuses){
            if (check_bonus_collisions(bonus)){
                switch (bonus->bonus_type) {
                    case BONUS_TYPE_TRIPLE_BALL:
                        this->apply_bonus_triple_ball();
                        score += 5;
                        break;
                    case BONUS_TYPE_TRIPLE_SPEED_UP2:
                        this->balls[randint(0, (int)this->balls.size())]->multiply_ball_speed(1.5f);
                        //std::cout << "Speedbust\n";
                        score += 10;
                        break;
                    case BONUS_TYPE_SCORE:
                        score += 45;
                        break;
                    case BONUS_TYPE_PLATFORM_SIZE_UP:
                        this->platform_weight += 64;
                        this->move_platform();
                        break;
                }
            }
        }
    }

    void rest_game(){
        this->wipe_targets_data();
        //load_level_data(file_path);

        for (auto* _ball : this->balls){
            if (_ball != this->ball)
                delete _ball;
            else{
                _ball->set_x(platform_x);
                _ball->set_y(platform_y - 128);
            }
        }
        this->balls.clear();
        this->balls.push_back(this->ball);

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
