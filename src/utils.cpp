#include "../include/utils.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

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

string_vector split(const string &s, char delimiter) {
    string_vector tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}