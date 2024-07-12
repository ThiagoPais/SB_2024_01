#pragma once
#include <iostream>
#include <map>

enum COMMANDCODE {     
    ADD,    
    SUB,    
    MUL,   
    DIV,    
    JMP,    
    JMPN,   
    JMPP,   
    JMPZ,   
    COPY,   
    LOAD,   
    STORE,  
    INPUT,  
    OUTPUT, 
    STOP    
};

struct command {
    command(COMMANDCODE name, unsigned short int opcode, short int size) : name(name), opcode(opcode) {};
    
    COMMANDCODE name;
    unsigned short int opcode;
    short int size;
};

enum DIRECTIVECODE { 
    SECTION, 
    SPACE,   
    CONST,   
    EQU,     
    IF,      
    MACRO,   
    ENDMACRO 
};


struct directive {
    directive(DIRECTIVECODE name, unsigned short int param_count, short int size) : name(name), param_count(param_count), size(size) {};
    
    DIRECTIVECODE name;
    unsigned short int param_count;
    short int size; 
};

namespace dictionary {
    static std::map<std::string, command> commands = {
        {"ADD", command(ADD, 1, 2)},
        {"SUB", command(SUB, 2, 2)},
        {"MUL", command(MULT, 3, 2)},
        {"DIV", command(DIV, 4, 2)},
        {"JMP", command(JMP, 5, 2)},
        {"JMPN", command(JMPN, 6, 2)},
        {"JMPP", command(JMPP, 7, 2)},
        {"JMPZ", command(JMPZ, 8, 2)},
        {"COPY", command(COPY, 9, 3)},
        {"LOAD", command(LOAD, 10, 2)},
        {"STORE", command(STORE, 11, 2)},
        {"INPUT", command(INPUT, 12, 2)},
        {"OUTPUT", command(OUTPUT, 13, 2)},
        {"STOP", command(STOP, 14, 1)}
    };

    static std::map<std::string, directive> directives = {
        {"SPACE", directive(SPACE, 1, -1)},
        {"CONST", directive(CONST, 1, 1)},
        {"EQU", directive(EQU, 1, 0)},
        {"IF", directive(IF, 1, 0)}
    };
}