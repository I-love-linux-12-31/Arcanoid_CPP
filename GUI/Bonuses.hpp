//
// Created by yaroslav_admin on 19.11.22.
//

#ifndef ARCANOID_CPP_BONUSES_HPP
#define ARCANOID_CPP_BONUSES_HPP


#include <QPushButton>
#include <QIcon>

#include <string>

#include "../fps_control.h++"

class Bonus: public QPushButton
{
public:
    bool to_delete = false;
    float pos_y;
    void init(std::string img_path){
        this->pos_y = this->y();

        auto* icon = new QIcon(img_path.c_str());
        this->setIcon(*icon);
        this->show();
    }

    void move(){
        std::cout << "Bonus located at " << this->x() << " " << this->y() << " Size is : " << this->size().width() << " X " << this->size().height() << std::endl;
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
