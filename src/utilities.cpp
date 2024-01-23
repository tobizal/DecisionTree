#include "../include/Utilities.h"

std::string parse_extension(std::string filename){
    int pos = filename.find(".txt");
    if(pos == filename.size()-4)
        return ".txt";

    pos = filename.find(".csv");
    if(pos == filename.size()-4)
        return ".csv";

    
    throw (std::string)("Unknown file extension. Supported extensions are .txt and .csv");
}

