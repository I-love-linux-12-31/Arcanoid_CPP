//
// Created by yaroslav_admin on 16.11.22.
//

#ifndef ARCANOID_CPP_LEVEL_FILES_HANDLER_HPP
#define ARCANOID_CPP_LEVEL_FILES_HANDLER_HPP

#include <vector>
#include <fstream>

#include <iostream>


bool is_delimiter(char c){
    for (char i : " \t\n;")
        if (c == i)
            return true;
    return false;
}


std::vector<int> split(std::string &str){
    std::vector<int> result;
    std::string buffer;
    int int_buffer;
    for(char i : str){
        if (!is_delimiter(i)){
            buffer += i;
        }
        else {
            if (!buffer.empty())
                sscanf(buffer.c_str(), "%d", &int_buffer);
            result.push_back(int_buffer);
            buffer.clear();
        }
    }
    if (!buffer.empty()) {
        //result.push_back(buffer);
        sscanf(buffer.c_str(), "%d", &int_buffer);
        result.push_back(int_buffer);
    }
    return result;
}


std::vector<std::vector<int>> get_map(std::string &file_path){
    std::vector<std::vector<int>> result;

    std::ifstream file;
    file.open(file_path.c_str());
    if (!file){
        std::cout << "\033[1mFile opening error ! File :" << file_path << "\033[0m" << std::endl;
        file.close();
        return result;
    }

    std::string buffer;
    std::cout << " Reading..." << std::endl;
    while(getline(file, buffer)){
        result.push_back(split(buffer));
    }
    return result;
}


std::string get_level_path_by_id(int id, bool bonus = false){
    std::string level_str = std::to_string(id);
    if (id < 10)
        level_str = "0" + level_str;
    if (bonus)
        return "../levels/level_b" + level_str + ".level";
    return "../levels/level_" + level_str + ".level";
}


unsigned int get_main_levels_count(){
    return 8;
}
unsigned int get_bonus_levels_count(){
    return 5;
}


#endif //ARCANOID_CPP_LEVEL_FILES_HANDLER_HPP
