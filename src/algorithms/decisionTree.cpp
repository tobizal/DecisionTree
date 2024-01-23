#include "../../include/algorithms/DecisionTree.h"
#include "../../include/Utilities.h"
#include <iostream>

bool DecisionTree::loadData(std::string filename){
     data = new DataLoader<double>;
     if(!data->loadFromFile(filename)){
        std::cout<<"DataLoader::load() - couldnt retrieve data."<<std::endl;
        dataCorrupted=true;
        return false;
    }
    num_of_features=data->headers.size()-1;
    num_of_rows = data->data.size();

    //display message
    std::cout<<"Data loading successful.\nFeatures found("<<num_of_features<<"): ";
    for(int i=0; i<num_of_features-1; i++) std::cout<<data->headers[i]<<", ";
    std::cout<<data->headers[num_of_features-1]<<std::endl;

    dataCorrupted=false;
    //data labels std::string -> double
    fillLabelsDict();
    display_vector_contents(labels_dict);

    //data convert to entries
    for(int row=0; row<num_of_rows; row++){
        std::vector<double> entry;
        for(int column=0; column<num_of_features; column++){
            entry.push_back(data->data[row][column]);
        }
        entry.push_back(dictLabelLookup(data->labels[row]));
        entries.push_back(entry);
    }

    data->data.clear();
    display_vector_contents(entries);
    return true;
}

void DecisionTree::fit(){
    if(dataCorrupted){
        std::cout<<"No data or data corrupted. Load data before fitting."<<std::endl;
        return;
    }

    std::vector< std::vector<double>* > v;
    for(int i=0; i<entries.size(); i++){
        v.push_back(&entries[i]);
    }
    //display_vector_contents(v);
    fitNode(root, v, 0);

    

}
void DecisionTree::fitNode(Node<double>* node, std::vector< std::vector<double>* > &v, int depth_level){
    double own_entropy = calcEntropy(v);
    node->entropy = own_entropy;
   
    if(own_entropy == 0){
        node->label = v[0]->at(num_of_features);
        //std::cout<<"LEAF NODE: "<<node->label<<"    DEPTH: "<<depth_level<<std::endl;
        return;
    }
    
    Condition<double> best_condition;
    double best_information_gain=-1;

    for(int feature=0; feature<num_of_features; feature++){
        for(int i=0; i<v.size(); i++){
            Condition<double> test_condition(feature, v[i]->at(feature));
            double information_gain = calcInformationGain(test_condition, v, own_entropy);
            //std::cout<<"info gain: "<<information_gain<<std::endl; 
            if(information_gain > best_information_gain){
                best_information_gain = information_gain;
                best_condition = test_condition;
            }
        }
    }
    //std::cout<<"BEST information_gain: "<<best_information_gain<<std::endl;
    node->condition = best_condition;

    std::vector< std::vector<double>* > left;
    std::vector< std::vector<double>* > right;
    for(int i=0; i<v.size(); i++){
        if(*v[i] <= best_condition) left.push_back(v[i]);
        else right.push_back(v[i]);
    }
    //std::cout<<"BEST CONDITION: "<<best_condition.featureID<<"   "<<best_condition.value<<" DEPTH: "<<depth_level<<std::endl;
    //std::cout<<"Pushed left: "<<left.size()<<std::endl;
    //display_vector_contents(left);
    //std::cout<<"Pushed right: "<<right.size()<<std::endl;
    //display_vector_contents(right);

    if(left.size() > 0){
        node->left = new Node<double>;
        fitNode(node->left, left, depth_level+1);
    }
    if(right.size() > 0){
        node->right = new Node<double>;
        fitNode(node->right, right, depth_level+1);
    }

}
double DecisionTree::calcInformationGain(Condition<double> c, std::vector< std::vector<double>* > &v, double parent_entropy){
    std::vector< std::vector<double>* > left;
    std::vector< std::vector<double>* > right;

    for(int i=0; i<v.size(); i++){
        //std::cout<<"*v[i]: ";
        //display_vector_contents(*v[i]);
        //std::cout<<"C.value: "<<c.value<<std::endl;
        if(*v[i] <= c) left.push_back(v[i]);
        else right.push_back(v[i]);
    }

    double entropy_right = calcEntropy(right);
    double entropy_left = calcEntropy(left);
    double p_left = ((double)left.size())/(double)(v.size());
    double p_right = ((double)right.size())/(double)(v.size());

    return parent_entropy - p_left*entropy_left - p_right*entropy_right;
}

double DecisionTree::calcEntropy(std::vector< std::vector<double>* > &v){
    if(v.size()==0) return 0;
    double entropy=0;
    std::vector<int> labels_count;
    for(int i=0; i<num_of_labels; i++){
        labels_count.push_back(0);
    }
    for(int i=0; i<v.size(); i++){
        int label = v[i]->at(num_of_features);
        labels_count[label] += 1;
    }
    for(int i=0; i<num_of_labels; i++){
        double p = (float)(labels_count[i])/(float)(v.size());
        entropy += -p*log_base(num_of_labels,p);
    }
    return entropy;
}

void DecisionTree::fillLabelsDict(){
    for(int i=0; i<data->labels.size(); i++){
        std::string key= data->labels[i];
        int index = find(labels_dict, key);
        if(index < 0){
            labels_dict.push_back(key);
        }
    }
    num_of_labels = labels_dict.size();
}

double DecisionTree::dictLabelLookup(std::string s){
    for(int i=0; i<labels_dict.size(); i++){
        if(labels_dict[i]==s) return i;
    }
    std::cout<<"Critical error: dictionary label unresolved."<<std::endl;
    exit(1);
}
std::string DecisionTree::dictLabelLookup(int i){
    return labels_dict[i];
}

std::string DecisionTree::predict(const std::vector<double> &v){
    int label = predictNode(v, root, 0);
    return dictLabelLookup(label);
 }

int DecisionTree::predictNode(const std::vector<double> &v, Node<double>* node, int depth_level){
    if(node->left == nullptr && node->right == nullptr){
        int label = node->label;
        return label;
    }
    if(node->left == nullptr) return predictNode(v, node->right, depth_level+1);
    if(node->right == nullptr) return predictNode(v, node->left, depth_level+1);

    if(v <= node->condition) return predictNode(v, node->left, depth_level+1);
    else return predictNode(v, node->right, depth_level+1);
}

 int DecisionTree::mostOccuredLabel(std::vector< std::vector<double>* > &v){
    int most_occured = 0;
    int occurences = 0;
    for(int i=0; i<num_of_labels; i++){
        int counter = 0;
        for(int entry=0; entry<v.size(); entry++){
            if(v[i]->at(num_of_features) == i) counter++;
        }
        if(counter > occurences){
            occurences = counter;
            most_occured = i;
        }
    }
    return most_occured;
 }

 void DecisionTree::displayNodes(){
    printNode(root);
 }
 void DecisionTree::printNode(Node<double>* node){
    std::cout<<"NODE: "<<node->condition.featureID<<" "<<node->condition.value<<"   ";
    if(node->left != nullptr ) std::cout<<"LEFT: "<<node->left->condition.featureID<<" "<<node->left->condition.value<<"   ";
    else std::cout<<"left null.";
    if(node->right != nullptr )std::cout<<"RIGHT: "<<node->right->condition.featureID<<" "<<node->right->condition.value<<" ";
    else std::cout<<"right null.";
    std::cout<<std::endl;

    if(node->left != nullptr ) printNode(node->left);
    if(node->right != nullptr) printNode(node->right);

 }