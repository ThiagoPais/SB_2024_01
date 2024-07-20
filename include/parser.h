#include "utils.h"
#include "dictionary.h"
struct IRCommand {
    IRCommand(command cmd, string_vector params) : cmd(cmd), params(params) {};

    command cmd;
    string_vector params;
};

struct IR {
    vector<IRCommand> commands;
    vector<int> memory_spaces;
    
    IR(vector<IRCommand> commands, vector<int> memory_spaces) : commands(commands), memory_spaces(memory_spaces) {};
    IR() : commands({}), memory_spaces({}) {};
    
};

IR parse(token_vector &tokens);

void verifyLabel(Token t);

bool isNumeric (std::string s);

bool isNumeric (char c);

bool containsSpecialSymbols(std::string s);
