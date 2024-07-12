#pragma once
#include <fstream>
#include <vector>

using namespace std;

#define string_vector vector<string>
#define token_vector  vector<Token>

struct Token {
    Token(string text = "", int line = 0)
    : text(text), line(line) {};

    string text;
    int line;

    template<typename T> void operator+= (T rhs){ text += rhs; }
    template<typename T> void operator=  (T rhs){ text = rhs;  }
    bool operator== (string rhs){ return text == rhs; }
    bool operator!= (string rhs){ return text != rhs; }
    bool empty (){ return text.empty() || text == ""; }
};