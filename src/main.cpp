#include "../include/tokenizer.h"
#include "../include/assembler.h"

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

    // token_vector tokens2 = preprocessar(tokens)

    IR parsed_code = parse(tokens);

    string test = assemble(parsed_code);

    cout << test << endl;

    return 0;
}
