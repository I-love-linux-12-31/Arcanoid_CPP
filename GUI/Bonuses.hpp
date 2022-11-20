//
// Created by yaroslav_admin on 19.11.22.
//

#ifndef ARCANOID_CPP_BONUSES_HPP
#define ARCANOID_CPP_BONUSES_HPP


#include <QPushButton>
#include <QIcon>

#include <string>

#include "../fps_control.h++"
const unsigned int BONUS_TYPE_TRIPLE_BALL = 1;
const unsigned int BONUS_TYPE_TRIPLE_SPEED_UP2 = 2;

class Bonus: public QPushButton
{
public:
    bool to_delete = false;
    float pos_y;
    unsigned int bonus_type;
    int get_x(){
        return this->x();
    }
    void init(std::string img_path, unsigned int _type){
        this->bonus_type = _type;
        this->pos_y = (float)this->y();

        //auto* icon = new QIcon(img_path.c_str());
        this->setAutoFillBackground(true);
        //icon->pixmap(64, 64);
        //this->setIcon(*icon);
        this->setStyleSheet("background-image: url(../icons/Ball_triple_ico.png);border: none");
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
