//
// Created by yaroslav_admin on 19.11.22.
//

#ifndef ARCANOID_CPP_BALL_HPP
#define ARCANOID_CPP_BALL_HPP

#include <vector>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

#include "../game_consts_and_globals.hpp"
#include "../fps_control.hpp"

#include "TargetBlock.hpp"
#include "Bonuses.hpp"
#include "../physics.hpp"

#include <thread>

#include<unistd.h>


class Ball : public QPushButton
{
private:
    float ball_x = 9999.0f;
    float ball_y = 9999.0f;
    float ball_speed_y = BALL_SPEED_START;
    float ball_speed_x = BALL_SPEED_START;

    int _id = 0;

    void update_qt_pos(){
        this->setGeometry(QRect((int)this->ball_x, (int)this->ball_y, (int)BALL_SIZE, (int)BALL_SIZE));
    }

public:
    void rest_speed(){
        auto thread_func = [this]() {
            this->ball_speed_x = 0.0f;
            this->ball_speed_y = 0.0f;
            sleep(1);
            this->ball_speed_x = BALL_SPEED_START;
            this->ball_speed_y = BALL_SPEED_START;
            return;
        };
        std::thread thr(thread_func);
        thr.detach();
    }
    void freeze_ball(){
        auto thread_func = [this]() {
            float old_sx = this->ball_speed_x;
            float old_sy = this->ball_speed_y;
            this->ball_speed_x = 0.0f;
            this->ball_speed_y = 0.0f;
            sleep(1);
            this->ball_speed_x = old_sx;
            this->ball_speed_y = old_sy;
            if (old_sx == 0.0f and old_sy == 0.0f){
                this->ball_speed_x = BALL_SPEED_START;
                this->ball_speed_y = BALL_SPEED_START;
            }
            return;
        };
        std::thread thr(thread_func);
        thr.detach();
    }
    void set_id(int id){
        this->_id = id;
        this->setText(std::to_string(id).c_str());
    }
    void multiply_ball_speed(float m){
        this->ball_speed_x *= m;
        this->ball_speed_y *= m;
    }
    int get_id(){
        return this->_id;
    }
    float get_x(){
        return this->ball_x;
    }
    float get_y(){
        return this->ball_y;
    }
    void set_y(float y){
        this->ball_y = y;
        update_qt_pos();
    }
    void set_x(float x){
        this->ball_x = x;
        update_qt_pos();
    }
    void init(int x  = 256, int y = 256){
        this->setObjectName(QString::fromUtf8("ball"));
        this->setGeometry(QRect(x, y, (int)BALL_SIZE, (int)BALL_SIZE));
        this->setMinimumSize(QSize(16, 16));
        this->setMaximumSize(QSize((int)BALL_SIZE, (int)BALL_SIZE));
        this->setStyleSheet(QString::fromUtf8("   border-style: outset;\n"
                                              "   border-width: 4px;\n"
                                              "   border-radius: 8px;\n"
                                              "   border-color: #888899;\n"
                                              "   padding: 6px;\n"
                                              "   color: #FF8888;\n"));
        this->ball_x = (float)x;
        this->ball_y = (float)y;

    }

    void change_movement_vector(int x, int y){
        if (x > 0 and this->ball_speed_x < 0 or x < 0 and this->ball_speed_x > 0)
            this->ball_speed_x *= -1.0f;
        if (y > 0 and this->ball_speed_y < 0 or y < 0 and this->ball_speed_y > 0)
            this->ball_speed_y *= -1.0f;
    }

    void move(){
        if (current_fps < 1)
            current_fps = 256;
        this->ball_y += this->ball_speed_y / (float)get_main_thread_fps();
        this->ball_x += this->ball_speed_x / (float)get_main_thread_fps();
        this->setGeometry({
                                  (int)this->ball_x,
                                  (int)this->ball_y,
                                  this->width(),
                                  this->width()
                          });
    }

    void process_ball_collisions(float platform_x, float platform_y, float platform_w, float platform_h, std::vector<std::vector<TargetBlock*>*>* targets, QWidget* GameSpace, std::vector<Bonus*>* bonuses, QWidget* parent){
        bool next_move_required = false;
        // Walls
        if (this->ball_y > (float)GameSpace->height() - BALL_SIZE) {
            if (this->ball_y - ((float)GameSpace->height() - BALL_SIZE) > BALL_SIZE / 4){
                this->ball_y = (float)GameSpace->height() - BALL_SIZE * 1.25f;
            }
            this->ball_speed_y *= -1.0f;
        }
        if (this->ball_y < 0.0f) {
            this->ball_y = 1.0f;
            this->ball_speed_y *= -1.0f;

        }
        if (this->ball_x > (float)GameSpace->width() - BALL_SIZE) {
            if (this->ball_x - ((float)GameSpace->width() - BALL_SIZE) > BALL_SIZE / 4){
                this->ball_x = (float)GameSpace->width() - BALL_SIZE - 1;
            }

            this->ball_speed_x *= -1.0f;
        }
        if (this->ball_x < 0.0f) {
            this->ball_x = 1.0f;
            this->ball_speed_x *= -1.0f;
        }

        // Platform
        if (this->ball_y + BALL_SIZE > platform_y and this->ball_x + 0.0f < platform_x + platform_w and this->ball_x > platform_x){
            //std::cout<<"Colide" << std::endl;
            this->ball_speed_y *= -1.0f;
            next_move_required = true;
        }
        if (
                (this->ball_y + BALL_SIZE / 2 > platform_y and this->ball_y + BALL_SIZE / 2 < platform_y + platform_h
                 and this->ball_x + BALL_SIZE > platform_x and this->ball_x < platform_x)
                or
                (this->ball_y + BALL_SIZE / 2 > platform_y and this->ball_y + BALL_SIZE / 2 < platform_y + platform_h
                 and this->ball_x + BALL_SIZE > platform_x + platform_w and this->ball_x < platform_x + platform_w)
                ) {

            this->ball_speed_x *= -1.0f;
        }

        // blocks
        for (auto row : *targets){
            for (auto target : *row){
                if (!target->is_dead()) {
                    // Vertical
                    if (this->ball_y < target->y() + target->height() and this->ball_y + BALL_SIZE > target->y() and this->ball_x + BALL_SIZE / 2 < target->x() + target->width() and
                        this->ball_x + BALL_SIZE / 2 > target->x()) {
                        //target->setText("X");
                        if (target->hit_block() and target->is_bonus()){
                            bonuses->push_back(new Bonus());
                            (*bonuses)[bonuses->size() - 1]->setParent(parent);
                            (*bonuses)[bonuses->size() - 1]->setGeometry(this->ball_x, this->ball_y, 64, 64);
                            (*bonuses)[bonuses->size() - 1]->init();

                            std::cout << "Bonus !!!!" << std::endl;
                        }
                        //target->kill_target();
                        //score += 1;
                        this->ball_speed_y *= -1.0f;
                        next_move_required = true;
                        while (this->ball_y < target->y() + target->height() and this->ball_y + BALL_SIZE > target->y() and this->ball_x + BALL_SIZE / 2 < target->x() + target->width() and
                               this->ball_x + BALL_SIZE / 2 > target->x())
                            this->move();
                    }
                    // Horizont
                    if (
                            (this->ball_y + BALL_SIZE / 2 > (float)target->y() and this->ball_y + BALL_SIZE / 2 < (float)target->y() + (float)target->height()
                             and this->ball_x + BALL_SIZE > (float)target->x() and this->ball_x < (float)target->x())
                            or
                            (this->ball_y + BALL_SIZE / 2 > (float)target->y() and this->ball_y + BALL_SIZE / 2 < (float)target->y() + (float)target->height()
                             and this->ball_x + BALL_SIZE > (float)target->x() + (float)target->width() and this->ball_x < (float)target->x() + (float)target->width())
                            ) {
                        //target->setText("X");
                        //target->kill_target();
                        //score += 1;
                        if (target->hit_block() and target->is_bonus()){
                            bonuses->push_back(new Bonus());
                            (*bonuses)[bonuses->size() - 1]->setParent(parent);
                            (*bonuses)[bonuses->size() - 1]->setGeometry(this->ball_x, this->ball_y, 64, 64);
                            (*bonuses)[bonuses->size() - 1]->init();

                            std::cout << "Bonus !!!!" << std::endl;
                        }
                        this->ball_speed_x *= -1.0f;
                        next_move_required = true;
                        while  (
                                (this->ball_y + BALL_SIZE / 2 > (float)target->y() and this->ball_y + BALL_SIZE / 2 < (float)target->y() + (float)target->height()
                                 and this->ball_x + BALL_SIZE > (float)target->x() and this->ball_x < (float)target->x())
                                or
                                (this->ball_y + BALL_SIZE / 2 > (float)target->y() and this->ball_y + BALL_SIZE / 2 < (float)target->y() + (float)target->height()
                                 and this->ball_x + BALL_SIZE > (float)target->x() + (float)target->width() and this->ball_x < (float)target->x() + (float)target->width())
                                )
                            this->move();
                    }
                }
            }
        }
        if (next_move_required){
            //this->move_ball();
            // this->move_ball();
            //this->move();
            next_move_required = false;
            }
    }
    void do_balls_collision(Ball* other_ball){
        float sx = abs(this->ball_speed_x) + abs(other_ball->ball_speed_x);
        float sy = abs(this->ball_speed_y) + abs(other_ball->ball_speed_y);
        if (this->ball_speed_x > other_ball->ball_speed_x){
            this->ball_speed_x = -0.6f * sx;
            other_ball->ball_speed_x = 0.4f * sx;
        }
        else{
            this->ball_speed_x = 0.5f * sx;
            other_ball->ball_speed_x = -0.5f * sx;
        }

        if (this->ball_speed_y > other_ball->ball_speed_y){
            this->ball_speed_y = -0.6f * sy;
            other_ball->ball_speed_y = 0.4f * sy;
        }
        else{
            this->ball_speed_y = 0.5f * sy;
            other_ball->ball_speed_y = -0.5f * sy;
        }

    }


    void process_ball_collisions_with_other_balls(std::vector<Ball*>* balls){
        int count = 0;
        for (Ball* ball : *balls){
            if (this == ball)
                continue;
            while(is_collide(this, ball)){
                count++;
                //std::cout << "### Balls collide!!" << std::endl;
                //this->multiply_ball_speed(-1.0f);
                //ball->multiply_ball_speed(-1.0f);
                if (count > 3){
                    spawn_on_random_good_place(balls);
                    break;

                }
                else{
                    this->do_balls_collision(ball);
                    this->move();
                }
            }
        }
    }

    void spawn_on_random_good_place(std::vector<Ball*>* balls){
        float k = 1.0f;
        int iteration;
        bool good_spawn = false;
        while(!good_spawn){
            iteration++;
            good_spawn = true;
            for (Ball* other_ball : *balls){
                if (is_collide(other_ball, this)){
                    std::cout << "Spawn collide with ball №" << other_ball->get_id() << std::endl;
                    good_spawn = false;
                }
            }
            if (!good_spawn){
                std::cout << "Failed to plant new ball at :" << this->get_x() << ", " << this->get_y() << std::endl;
                if (iteration > 16 and k < 50.0f){
                    iteration = 0;
                    k += 0.2f;
                }
                this->set_y((*balls)[balls->size() - 1]->y() + (float)(randint((int)BALL_SIZE, (int)(BALL_SIZE * k))) * get_random_inversion());
                this->set_x((*balls)[balls->size() - 1]->x() + (float)(randint((int)BALL_SIZE, (int)(BALL_SIZE * k))) * get_random_inversion());
            }
        }
    }

};

#endif //ARCANOID_CPP_BALL_HPP
