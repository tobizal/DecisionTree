#include "Condition.h"

template<typename T> struct Node{
    Condition<T> condition;
    Node<T>* left;
    Node<T>* right;
    double entropy;
    int label;

    Node(): left(nullptr), right(nullptr){}
};