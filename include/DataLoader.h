#ifndef DataLoader_H
#define DataLoader_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <typeinfo>
#include "Utilities.h"

template <typename T>
class DataLoader{
private:
    T convert (std::string s);  //converts parsed data from std::string to T type
public:
    std::vector< std::vector<T> > data; //data starting from second row of the file data, excluding last column
    std::vector<std::string> headers;   //first row of file data
    std::vector<std::string> labels;    //data starting from second row of the file data, includes the last column only

    DataLoader() = default;
    virtual ~DataLoader(){};

    bool loadFromFile(const std::string& filename);   //loads data and returns true if successful
    void displayData(int cell_length=14) const;
};





//template definitions

template<typename T> T DataLoader<T>::convert(std::string s){
    throw (std::string)("Data type conversion failed. Data type unsupported by DataLoader object.");
}
template<> int DataLoader<int>::convert(std::string s);
template<> long DataLoader<long>::convert(std::string s);
template<> float DataLoader<float>::convert(std::string s);
template<> double DataLoader<double>::convert(std::string s);
template<> std::string DataLoader<std::string>::convert(std::string s);

template<typename T> void DataLoader<T>::displayData(int cell_length) const{
    std::cout<<std::left;
    std::cout<<std::showpoint;
    std::cout<<std::setw(1+headers.size()*(cell_length+1))<<std::setfill('-')<<""<<std::endl;
    for(int i=0; i<headers.size(); i++){
        std::cout<<std::setw(cell_length)<<std::setfill(' ')<<headers[i];
    }
    std::cout<<"Data type: "<<typeid(T).name();
    std::cout<<std::endl;
    std::cout<<std::setw(1+headers.size()*(cell_length+1))<<std::setfill('-')<<""<<std::endl;
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<data[i].size(); j++){
            std::cout<<std::setw(cell_length)<<std::setfill(' ')<<data[i][j];
        }
        std::cout<<std::setw(cell_length)<<std::setfill(' ')<<"->   "+labels[i];
        std::cout<<std::endl;
    }
}

template<typename T> bool DataLoader<T>::loadFromFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file.good()){
        std::cout<<"An error occured while trying to open the file. File does not exist or is not accessible."<<std::endl;
        return false;
    }

    std::string extension;
    try{
        extension = parse_extension(filename);
    }
    catch(std::string error_message){
        std::cout<<error_message<<std::endl;
        return false;
    }
    
    std::string line;
    std::stringstream ss;

    //parse headers
    getline(file, line);
    ss.str(line);
    std::string temp;
    while(ss.rdbuf()->in_avail() != 0){
        if(extension == ".txt"){
            ss>>temp;
        } 
        else if(extension == ".csv"){
            getline(ss, temp, ',');
        }
        headers.push_back(temp);
    }

    //load data
    while(getline(file, line)){
        ss.clear();
        ss.str(line);
        std::vector<T> v;
        std::string s;
        for(int i=0; i<headers.size()-1; i++){
            if(extension == ".txt"){
                ss>>s;
            }
            else if(extension == ".csv"){
                getline(ss, s, ',');
            }

            try{
                v.push_back(convert(s));
            }
            catch(std::string error_message){
                std::cout<<error_message<<std::endl;
                return false;
            }
        }
        ss>>s;
        labels.push_back(s);
        data.push_back(v);
    }

    return true;
}
#endif //DataLoader_H