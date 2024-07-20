#include "../include/utils.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>


string_vector readFile(const string& filename) {
    string_vector lines;
    ifstream file(filename.c_str());
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        throw std::invalid_argument("Unable to open file: " + filename);
    }

    return lines;
}

bool createFile(string_vector data, string filename, string extension){
    ofstream output;
    output.open ((filename + extension).c_str());
    if (!output) return false;

    for (auto& line : data) output << line << endl;

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