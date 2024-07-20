#include "../include/dictionary.h"

std::map<std::string, command> initializeCommands() {
    std::map<std::string, command> commands;

    commands["ADD"] = command(ADD, 1, 2);
    commands["SUB"] = command(SUB, 2, 2);
    commands["MUL"] = command(MUL, 3, 2);
    commands["DIV"] = command(DIV, 4, 2);
    commands["JMP"] = command(JMP, 5, 2);
    commands["JMPN"] = command(JMPN, 6, 2);
    commands["JMPP"] = command(JMPP, 7, 2);
    commands["JMPZ"] = command(JMPZ, 8, 2);
    commands["COPY"] = command(COPY, 9, 3);
    commands["LOAD"] = command(LOAD, 10, 2);
    commands["STORE"] = command(STORE, 11, 2);
    commands["INPUT"] = command(INPUT, 12, 2);
    commands["OUTPUT"] = command(OUTPUT, 13, 2);
    commands["STOP"] = command(STOP, 14, 1);

    return commands;
}

std::map<std::string, directive> initializeDirectives() {
    std::map<std::string, directive> directives;

    directives["SPACE"] = directive(SPACE, 1, -1);
    directives["CONST"] = directive(CONST, 1, 1);
    directives["EQU"] = directive(EQU, 1, 0);
    directives["IF"] = directive(IF, 1, 0);
    directives["BEGIN"] = directive(BEGIN, 0, 0);
    directives["END"] = directive(END, 0, 0);
    directives["EXTERN"] = directive(EXTERN, 0, 0);
    directives["PUBLIC"] = directive(PUBLIC, 0, 0);

    return directives;
}