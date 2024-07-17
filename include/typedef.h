#pragma once
#include <fstream>
#include <vector>
#include <map>

using namespace std;

#define string_vector vector<string>
#define token_vector  vector<Token>

struct Token {
    Token(string text = "", short int line = 0)
    : text(text), line(line) {};

    string text;
    short int line;

    template<typename T> void operator+= (T rhs){ text += rhs; }
    template<typename T> void operator=  (T rhs){ text = rhs;  }
    bool operator== (string rhs){ return text == rhs; }
    bool operator!= (string rhs){ return text != rhs; }
    bool empty (){ return text.empty() || text == ""; }
};

struct Symbol {
    Symbol(short int value = 0, bool defined = false, vector<short int> pendency_list = {})
    : value(value), defined(defined), pendency_list(pendency_list) {};

    short int value;
    bool defined;
    vector<short int> pendency_list;
};

typedef map<std::string, Symbol> symbol_table;