#include <iostream>
#include "../include/DataLoader.h"

template<> int DataLoader<int>::convert(std::string s){
    return std::stoi(s);
}
template<> long DataLoader<long>::convert(std::string s){
    return std::stoi(s);
}
template<> float DataLoader<float>::convert(std::string s){
    return std::stof(s);
}
template<> double DataLoader<double>::convert(std::string s){
    return std::stod(s);
}
template<> std::string DataLoader<std::string>::convert(std::string s){
    return s;
}

