#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>


//declarations
std::string parse_extension(std::string filename);
template<typename T> double log_base(T var);
template<typename T> T* find_min(std::vector<T> v);
template<typename T> T* find_max(std::vector<T> v);
template<typename T> int find(const std::vector<T>&  v, T key);
template<typename T> void display_vector_contents(std::vector<T> v);
template<typename T> void display_vector_contents(std::vector< std::vector<T> > v);




//template definitions

template <typename T>double log_base(double base, T var){
    double v = (double)var;
    if(base <= 0){
        std::cout<<"Error. Log base <= 0."<<std::endl;
        exit(1);
    }
    if(var==0) return 0;
    return (log(v)/log(base));
}
template<typename T> T* find_min(std::vector<T> v){
    T* smallest = v.begin();
    for(int i=1; i<v.size(); i++){
        if(v[i]<*smallest) smallest = &v[i];
    }
    return smallest;
}
template<typename T> T* find_max(std::vector<T> v){
    T* greatest = v.begin();
    for(int i=1; i<v.size(); i++){
        if(v[i]>*greatest) greatest = &v[i];
    }
    return greatest;
}
template<typename T> int find(const std::vector<T>&  v, T key){
    for(int i=0; i<v.size(); i++){
        if(v[i]==key) return i;
    }
    return -1;
}
template<typename T> void display_vector_contents(std::vector<T> v){
    int space = 10;
    std::cout<<"Vector contents: "<<std::endl;
    std::cout<<std::setw(space)<<"Index   Value"<<std::endl;
    for(int i=0; i<v.size(); i++){
        std::cout<<i<<" "<<v[i]<<std::endl;
    }
    return;
}
template<typename T> void display_vector_contents(std::vector< std::vector<T> > v){
    int space = 10;
    std::cout<<std::setw(space)<<"Vector contents: "<<std::endl;
    std::cout<<std::setw(space)<<"Index"<<std::setw(space)<<"Contents"<<std::endl;
    for(int i=0; i<v.size(); i++){
        std::cout<<std::setw(space)<<i;
        for(int j=0; j<v[i].size(); j++){
            std::cout<<std::setw(space)<<v[i][j];
        }
        std::cout<<std::endl;
    }
    return;
}
template<typename T> void display_vector_contents(std::vector< std::vector<T>* > v){
    int space = 10;
    std::cout<<std::setw(space)<<"Vector contents: "<<std::endl;
    std::cout<<std::setw(space)<<"Index"<<std::setw(space)<<"Contents"<<std::endl;
    for(int i=0; i<v.size(); i++){
        std::cout<<std::setw(space)<<i;
        for(int j=0; j<v[i]->size(); j++){
            std::cout<<std::setw(space)<<v[i]->at(j);
        }
        std::cout<<std::endl;
    }
    return;
}

#endif