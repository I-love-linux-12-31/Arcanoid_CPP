//
// Created by yaroslav_admin on 19.11.22.
//

#ifndef ARCANOID_CPP_BONUSES_HPP
#define ARCANOID_CPP_BONUSES_HPP


#include <QPushButton>
#include <QIcon>

#include <string>

#include "../fps_control.h++"
const unsigned int BONUS_TYPE_RANDOM = 0;
const unsigned int BONUS_TYPE_TRIPLE_BALL = 1;
const unsigned int BONUS_TYPE_TRIPLE_SPEED_UP2 = 2;

class Bonus: public QPushButton
{
private:
    void set_random_type(){
        switch (randint(0, 2)) {
            case 0:
                this->bonus_type = BONUS_TYPE_TRIPLE_BALL;
                break;
            case 1:
                this->bonus_type = BONUS_TYPE_TRIPLE_SPEED_UP2;
                break;
            default:
                std::cout << "Random bonus type set error : unknown randint ! Setting default" << std::endl;
                this->bonus_type = BONUS_TYPE_TRIPLE_SPEED_UP2;
                break;

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
        else
            this->bonus_type = _type;
        this->update_image();

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
