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
    bool hit_block(){
        if (this->hp > 1024){
            std::cout << "\033[31m[Error]\033[0m Bad hp value !" << std::endl;
            this->hp = 1;
        }
        this->hp -= 1;
        if (this->hp < 1){
            score += (int)this->level;
            this->kill_target();
            this->update_color();
            return true;
        }
        this->update_color();
        return false;
    }
    void update_color(){
        std::string _color_a;
        std::string _color_b;
        this->setText("");
        switch (this->hp) {
            case 0:
                this->hide();
                this->setStyleSheet("");
                return;
            case 1:
                if (this->is_bonus())
                    _color_a = "255, 255, 255, 255";
                else
                    _color_a = "135, 184, 128, 255";
                _color_b = _color_a;
                break;
            case 2:
                if (this->is_bonus())
                    _color_a = "0, 255, 245, 255";
                else
                    _color_a = "2, 65, 255, 255";
                _color_b = _color_a;
                break;
            case 3:
                _color_a = "92, 255, 2, 255";
                _color_b = _color_a;
                break;
            case 4:
                _color_a = "139, 166, 15, 255";
                _color_b = _color_a;
                break;
            case 5:
                _color_a = "255, 191, 0, 255";
                _color_b = _color_a;
                break;
            case 6:
                _color_a = "255, 98, 0, 255";
                _color_b = _color_a;
                break;
            case 7:
                _color_a = "225, 19, 19, 255";
                _color_b = _color_a;
                break;
            case 8:
                _color_a = "109, 17, 17, 255";
                _color_b = _color_a;
                break;
            default:
                _color_a = "0, 0, 0, 255";
                this->setText((std::to_string(this->hp)).c_str());
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
};

#endif //ARCANOID_CPP_TARGETBLOCK_HPP
