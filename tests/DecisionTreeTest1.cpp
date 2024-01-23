#include <iostream>
#include "../include/algorithms/DecisionTree.h"

int main(){
    DecisionTree d;
    d.loadData("LearningSet.csv");
    d.fit();

    d.displayNodes();

    DataLoader<double> dataloader;
    dataloader.loadFromFile("TestingSet.csv");

    for(int i=0; i<dataloader.data.size(); i++){
        std::cout<<d.predict(dataloader.data[i])<<"\t\t";
        std::cout<<"Actual: "<<dataloader.labels[i]<<std::endl;
    }
    return 0;
}