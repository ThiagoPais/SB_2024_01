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
    command(COMMANDCODE name, unsigned short int opcode, short int size)
     : name(name), opcode(opcode), size(size) {};

    command() : name(COMMANDCODE()), opcode(0), size(0) {}; // Default constructor
    
    COMMANDCODE name;
    unsigned short int opcode;
    short int size;
};

enum DIRECTIVECODE { 
    SPACE,   
    CONST,   
    EQU,     
    IF,
    BEGIN,
    END,
    EXTERN,
    PUBLIC
};

struct directive {
    directive(DIRECTIVECODE name, unsigned short int param_count, short int size)
        : name(name), param_count(param_count), size(size) {}

    directive() : name(DIRECTIVECODE()), param_count(0), size(0) {} // Default constructor

    DIRECTIVECODE name;
    unsigned short int param_count;
    short int size;
};


std::map<std::string, command>   initializeCommands();
std::map<std::string, directive> initializeDirectives();


