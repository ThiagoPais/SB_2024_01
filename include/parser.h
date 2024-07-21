#include "utils.h"
#include "dictionary.h"
struct IRCommand {
    IRCommand(command cmd, string_vector params) : cmd(cmd), params(params) {};

    command         cmd;
    string_vector   params;
};

struct IR {
    vector<IRCommand>   commands;
    vector<int>         memory_spaces;

    bool                     isModule;
    map<string, vector<int>> use_table;
    map<string, int>         def_table;
    
    IR(vector<IRCommand> commands, vector<int> memory_spaces, bool isModule, map<string, vector<int>> use_table, map<string, int> def_table) : commands(commands), memory_spaces(memory_spaces), isModule(isModule), use_table(use_table), def_table(def_table) {};
    IR() : commands({}), memory_spaces({}), isModule(false), use_table(use_table), def_table(def_table) {};
    
};

IR parse(token_vector &tokens);

void verifyLabel(Token t);

bool isNumeric (std::string s);

bool isNumeric (char c);

bool hasSpecialSymbols(std::string s);

bool isSpecialSymbol(char c);
