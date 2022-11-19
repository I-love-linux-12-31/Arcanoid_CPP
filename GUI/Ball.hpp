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
#include "../fps_control.h++"

#include "TargetBlock.hpp"


class Ball : public QPushButton
{
private:
    float ball_x = 256.0f;
    float ball_y = 512.0f;
    float ball_speed_y = BALL_SPEED_START;
    float ball_speed_x = BALL_SPEED_START;

public:
    float get_x(){
        return this->ball_x;
    }
    float get_y(){
        return this->ball_y;
    }
    void init(int x  = 256, int y = 256){
        this->setObjectName(QString::fromUtf8("ball"));
        this->setGeometry(QRect(x, y, (int)BALL_SIZE, (int)BALL_SIZE));
        this->setMinimumSize(QSize(16, 16));
        this->setMaximumSize(QSize((int)BALL_SIZE, (int)BALL_SIZE));
        this->setStyleSheet(QString::fromUtf8("   border-style: outset;\n"
                                              "   border-width: 2px;\n"
                                              "   border-radius: 8px;\n"
                                              "   border-color: beige;\n"
                                              "   padding: 2px;"));
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

    void process_ball_collisions(float platform_x, float platform_y, float platform_w, float platform_h, std::vector<std::vector<TargetBlock*>>* targets, QWidget* GameSpace){
        bool next_move_required = false;
        // Walls
        if (this->ball_y > (float)GameSpace->height() - BALL_SIZE)
            this->ball_speed_y *= -1.0f;
        if (this->ball_y < 0.0f)
            this->ball_speed_y *= -1.0f;
        if (this->ball_x > (float)GameSpace->width() - BALL_SIZE)
            this->ball_speed_x *= -1.0f;
        if (this->ball_x < 0.0f)
            this->ball_speed_x *= -1.0f;

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
            for (auto target : row){
                if (!target->is_dead()) {
                    // Vertical
                    if (this->ball_y < target->y() + target->height() and this->ball_y + BALL_SIZE > target->y() and this->ball_x + BALL_SIZE / 2 < target->x() + target->width() and
                        this->ball_x + BALL_SIZE / 2 > target->x()) {
                        //target->setText("X");
                        target->hit_block();
                        //target->kill_target();
                        //score += 1;
                        this->ball_speed_y *= -1.0f;
                        next_move_required = true;
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
                        target->hit_block();
                        this->ball_speed_x *= -1.0f;
                        next_move_required = true;
                    }
                }
            }
        }
        if (next_move_required){
            //this->move_ball();
            // this->move_ball();
            this->move();
            next_move_required = false;
        }
    }
};

#endif //ARCANOID_CPP_BALL_HPP
