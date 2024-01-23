template<typename T> struct Condition{
    T value;
    int featureID;

    Condition(int fID=-1, T val=-1)
    :value(val), featureID(fID) {}
};

template<typename T> bool operator<= (const std::vector<T>& entry, const Condition<T>& c){
    //std::cout<<"entry[c.featureID]:"<< entry[c.featureID]<<"    c.value"<<c.value<<std::endl;
    return entry[c.featureID]<=c.value;
}
