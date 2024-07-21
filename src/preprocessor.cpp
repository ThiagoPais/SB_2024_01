#include "../include/preprocessor.h"

token_vector preprocess(token_vector tokens) {
    token_vector preprocessed_vector = tokens;
    token_vector result;

    //resolve EQU
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i].text == "EQU") {
            string label = tokens[i-1].text.substr(0, tokens[i].text.size() - 1);
            for (size_t j = 0; j < preprocessed_vector.size(); j++) {
                if (preprocessed_vector[j].text == label) {
                    preprocessed_vector[j].text = tokens[i+1].text;
                }
                if (preprocessed_vector[j].line == tokens[i].line) {
                    preprocessed_vector[j].text = "";
                }
            }
        }
    }
    
    tokens = preprocessed_vector;

    //resolve IF
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i].text == "IF") {
            if (tokens[i+1].text == "0") {
                for (size_t j = 0; j < preprocessed_vector.size(); j++) {
                    if (preprocessed_vector[j].line == tokens[i].line + 1) {
                        preprocessed_vector[j].text = "";
                    }
                }
            }
            for (size_t j = 0; j < preprocessed_vector.size(); j++) {
                if (preprocessed_vector[j].line == tokens[i].line) {
                        preprocessed_vector[j].text = "";
                }
            }
        }
    }

    for (auto token : preprocessed_vector) {
        if (token.text != "") {
            result.push_back(token);
        }
    }

    // for (auto token : result ) {
    //     std::cout << token.text << endl;
    // }

    return result;
}