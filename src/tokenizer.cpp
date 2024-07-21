#include "../include/tokenizer.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>


token_vector tokenize(string_vector &sourceCode) {
    token_vector tokens;
    string line;
    int lineNumber = 0;

    for (auto line : sourceCode) {
        lineNumber++;

        if (line.empty()) continue;

        if (line.find(',')) std::replace( line.begin(), line.end(), ',', ' ');
        
        // Disconsiders comments
        size_t commentPos = line.find(';');
        if (commentPos != string::npos) {
            line = line.substr(0, commentPos);
        }

        // Split the line into words and trim them
        vector<string> words = split(line, ' ');
        for (auto &word : words) {
            if (word.empty()) continue;
            toUpperCase(word);
            tokens.push_back(Token(word, lineNumber));
        }
        
    }
    return tokens;
}

void toUpperCase(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); });
}