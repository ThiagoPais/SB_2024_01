#include "../include/utils.h"
#include <string>

string_vector readFile(string filename) {
    ifstream input(filename);

    string_vector res;

    string temp;

    while(getline(input, temp)){
        res.push_back(string(temp.c_str()));
    }

    return res;
};

bool createFile(string_vector data, string filename, string extension){
    ofstream output;
    output.open ((filename + extension).c_str());
    if (!output) return false;

    for (auto& line : data) output << line;

    output.close();

    return true;
}

// overload for single string
bool createFile(string data, string filename, string extension){
    ofstream output;
    output.open ((filename + extension).c_str());
    if (!output) return false;

    output << data;

    output.close();

    return true;
}