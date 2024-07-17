#include "../include/tokenizer.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

// MAIN DE TESTES

int main() {
    string_vector code = readFile("teste.asm");
    
    token_vector tokens = tokenize(code);

    for (const auto &token : tokens) {
        cout << "Token: " << token.text << ", Line: " << token.line << endl;
    }

    return 0;
}
