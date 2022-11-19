//
// Created by yaroslav_admin on 19.11.22.
//

#ifndef ARCANOID_CPP_TARGETBLOCK_HPP
#define ARCANOID_CPP_TARGETBLOCK_HPP

#include <QtWidgets/QPushButton>

#include "../game_consts_and_globals.hpp"

class TargetBlock : public QPushButton
{
    unsigned int level = 1;
    unsigned int hp = 1;
    int column = 0, row = 0;
    bool bonus = false;
public:
    bool is_bonus(){
        return this->bonus;
    }
    void set_bonus(bool status){
        this->bonus = status;
    }
    void hit_block(){
        this->hp -= 1;
        if (this->hp < 1){
            score += (int)this->level;
            this->kill_target();
        }
        this->update_color();
    }
    void update_color(){
        std::string _color_a = "68, 8, 8, 175";
        std::string _color_b = "68, 8, 8, 175";
        switch (this->hp) {
            case 0:
                this->hide();
                this->setStyleSheet("");
                return;
            case 1:
                if (this->is_bonus())
                    _color_a = "255, 255, 255, 229";
                else
                    _color_a = "135, 184, 128, 229";
                _color_b = _color_a;
                break;
            case 2:
                if (this->is_bonus())
                    _color_a = "0, 255, 245, 229";
                else
                    _color_a = "2, 65, 255, 175";
                _color_b = _color_a;
                break;
            case 3:
                _color_a = "92, 255, 2, 175";
                _color_b = _color_a;
                break;
            default:
                _color_a = "0, 0, 0, 255";
                _color_b = _color_a;
                break;

        }
        this->show();
        this->setStyleSheet((" background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,     stop: 0 rgba(" + _color_a + "), stop: 1 rgba(" + _color_b + "));").c_str());
    }
    bool is_dead(){
        return this->hp == 0;
    }
    void set_level(int &_level){
        this->level = _level;
    }
    void set_hp(int _hp){
        this->hp = _hp;
        this->update_color();
    }
    int get_col(){
        return this->column;
    }
    int get_row(){
        return this->row;
    }
    void set_col(int col){
        this->column = col;
    }
    void set_row(int _row){
        this->row = _row;
    }
    void kill_target(){
        this->hp = 0;
        //this->setStyleSheet(" background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,     stop: 0 rgba(68, 8, 8, 175), stop: 1 rgba(68, 8, 8, 175));");
        this->hide();
    }
    void create(int _col, int _row){
        this->set_col(_col);
        this->set_row(_row);
    }
};

#endif //ARCANOID_CPP_TARGETBLOCK_HPP
