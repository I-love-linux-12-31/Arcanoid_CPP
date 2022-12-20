//
// Created by yaroslav_admin on 19.11.22.
//

#ifndef ARCANOID_CPP_BONUSES_HPP
#define ARCANOID_CPP_BONUSES_HPP


#include <QPushButton>
#include <QIcon>

#include <string>

#include "../fps_control.hpp"
const unsigned int BONUS_TYPE_RANDOM = 0;
const unsigned int BONUS_TYPE_TRIPLE_BALL = 1;
const unsigned int BONUS_TYPE_TRIPLE_SPEED_UP2 = 2;
const unsigned int BONUS_TYPE_SCORE = 3;
const unsigned int BONUS_TYPE_PLATFORM_SIZE_UP = 4;
const unsigned int BONUS_TYPE_PLATFORM_SIZE_MIN = 44;
const unsigned int BONUS_TYPE_PLATFORM_SPEED_MIN = 45;
const unsigned int BONUS_TYPE_RANDOM_POSITIVE = 32;
const unsigned int BONUS_TYPE_RANDOM_NEGATIVE = 33;


class Bonus: public QPushButton
{
private:
    void set_random_type(){
        int rnd = randint(1, 6);
        switch (rnd) {
            case BONUS_TYPE_TRIPLE_BALL: // 1
                this->bonus_type = BONUS_TYPE_TRIPLE_BALL;
                break;
            case BONUS_TYPE_TRIPLE_SPEED_UP2: // 2
                this->bonus_type = BONUS_TYPE_TRIPLE_SPEED_UP2;
                break;
            case BONUS_TYPE_SCORE: // 3
                this->bonus_type = BONUS_TYPE_SCORE;
                break;
            case BONUS_TYPE_PLATFORM_SIZE_UP: // 4
                this->bonus_type = BONUS_TYPE_PLATFORM_SIZE_UP;
                break;
            case 5: // 5
                this->bonus_type = BONUS_TYPE_PLATFORM_SIZE_MIN;
                break;
            case 6: // 6
                this->bonus_type = BONUS_TYPE_PLATFORM_SPEED_MIN;
                break;
            default:
                std::cout << "Random bonus type set error : unknown randint : " << rnd << " ! Setting default" << std::endl;
                this->bonus_type = BONUS_TYPE_SCORE;
                break;

        }

    }
    void set_random_negative_type(){
        int i = randint(44, 45);
        std::cout << "\033[32mRandom type = " << i << "\033[0m\n";
        for (unsigned int j : {
                BONUS_TYPE_PLATFORM_SPEED_MIN,
                BONUS_TYPE_PLATFORM_SIZE_MIN}
                )
        {
            if (i == j){
                this->bonus_type = i;
                this->update_image();
                return;
            }
        }
    }

    void update_image(){
        switch (this->bonus_type) {
            case BONUS_TYPE_TRIPLE_BALL:
                this->setStyleSheet("background-image: url(../icons/Ball_triple_ico.png);border: none");
                break;
            case BONUS_TYPE_TRIPLE_SPEED_UP2:
                    this->setStyleSheet("background-image: url(../icons/Ball_speed_up_ico.png);border: none");
                    break;
            case BONUS_TYPE_SCORE:
                this->setStyleSheet("background-image: url(../icons/bonus_score_ico.png);border: none");
                break;
            case BONUS_TYPE_PLATFORM_SIZE_UP:
                this->setStyleSheet("background-image: url(../icons/Platform_size_up_ico.png);border: none");
                break;
            case BONUS_TYPE_PLATFORM_SIZE_MIN:
                this->setStyleSheet("background-image: url(../icons/Platform_size_min_ico.png);border: none");
                break;
            case BONUS_TYPE_PLATFORM_SPEED_MIN:
                this->setStyleSheet("background-image: url(../icons/Platform_speed_slow_ico.png);border: none");
                break;
            default:
                std::cout << "\033[31m[Error] Failed to set bonus icon! Unknown type :\033[0m" << this->bonus_type << std::endl;
                break;
        }
    }
public:
    bool to_delete = false;
    float pos_y;
    unsigned int bonus_type;
    int get_x(){
        return this->x();
    }
    void init(unsigned int _type = BONUS_TYPE_RANDOM){
        if (_type == BONUS_TYPE_RANDOM)
            this->set_random_type();
        else {
            if (_type == BONUS_TYPE_RANDOM_NEGATIVE) {
                this->set_random_negative_type();
            }
            else{
                this->bonus_type = _type;
            }
        }
        this->update_image();
        std::cout << "Bonus type set :" <<  this->bonus_type << std::endl;

        this->pos_y = (float)this->y();

        this->setAutoFillBackground(true);
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->show();
    }

    void move(){
        //std::cout << "Bonus located at " << this->x() << " " << this->y() << " Size is : " << this->size().width() << " X " << this->size().height() << std::endl;
        if (current_fps < 1)
            current_fps = 256;
        this->pos_y += 128.0f / (float)get_main_thread_fps();
        this->setGeometry({
                                  this->x(),
                                  (int)(this->pos_y),
                                  this->width(),
                                  this->width()
                          });
    }
};



#endif //ARCANOID_CPP_BONUSES_HPP
