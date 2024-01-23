#include <iostream>
#include "../include/DataLoader.h"
#include "../include/Utilities.h"

int main(){ 
    DataLoader<std::string> data1;
    data1.loadFromFile("file2.csv");
    data1.displayData();

    DataLoader<float> data2;
    data2.loadFromFile("file1.txt");
    data2.displayData();

    DataLoader<long> data3;
    data3.loadFromFile("file2.csv");
    data3.displayData();

    DataLoader<int> data4;
    data4.loadFromFile("file2.csv");
    data4.displayData();

    DataLoader<double> data5;
    data5.loadFromFile("file2.csv");
    data5.displayData();

    DataLoader<long long> data6;
    data6.loadFromFile("file2.csv");
    data6.displayData();
    return 0;
}