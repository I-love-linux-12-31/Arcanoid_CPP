//
// Created by yaroslav_admin on 16.11.22.
//

#ifndef ARCANOID_CPP_RANDOM_HPP
#define ARCANOID_CPP_RANDOM_HPP

#include <ctime>
#include <random>


void init_random(){
    srand((unsigned)time(nullptr));
}

int randint(int a, int b){
    return (rand()%b)+a;
}

#endif //ARCANOID_CPP_RANDOM_HPP
