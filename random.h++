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

float get_random_percent(){
    return (float)(randint(0, 101)) / 100;
}

float get_random_little_multiplier(){
    return (float)(randint(955, 1005)) / 1000;
}
float get_random_inversion(){
    int a = randint(0, 128);
    if (a % 2 == 0){
        return 1.0f;
    }
    return -1.0f;
}


#endif //ARCANOID_CPP_RANDOM_HPP
