//
// Created by yaroslav_admin on 21.11.22.
//

#ifndef ARCANOID_CPP_PHYSICS_HPP
#define ARCANOID_CPP_PHYSICS_HPP
#include <QWidget>


bool is_collide(QWidget* first, QWidget* second){
    int points[4][2];
    points[0][0] = first->x();
    points[0][1] = first->y();

    points[1][0] = first->x() + first->width();
    points[1][1] = first->y();

    points[2][0] = first->x();
    points[2][1] = first->y() + first->height();

    points[3][0] = first->x() + first->width();
    points[3][1] = first->y() + first->height();

    bool y_collide;
    bool x_collide;

    for (auto p : points){
        y_collide = false;
        x_collide = false;
        if (p[1] > second->y() and p[1] < second->y()+  second->height())
            y_collide = true;
        if (p[0] > second->x() and p[0] < second->x() + second->width())
            x_collide = true;
        if (y_collide and x_collide){
            return true;
        }
    }
    return false;
}
bool is_collide(QWidget first, QWidget second){
    return is_collide(&first, &second);
}

#endif //ARCANOID_CPP_PHYSICS_HPP
