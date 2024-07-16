#include "../include/tokenizer.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>


token_vector tokenize(const string &sourceCode) {
    token_vector tokens;
    istringstream stream(sourceCode);
    string line;
    int lineNumber = 0;

    while (getline(stream, line)) {
        lineNumber++;

        if (line.empty()) continue;

        // Disconsiders comments
        size_t commentPos = line.find(';');
        if (commentPos != string::npos) {
            line = line.substr(0, commentPos);
        }

        // Split the line into words and trim them
        vector<string> words = split(line, ' ');
        for (const auto &word : words) {
            if (word.empty()) continue;
            tokens.push_back(Token(word, lineNumber));
        }
    }
    return tokens;
}