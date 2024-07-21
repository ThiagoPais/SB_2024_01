#include "../include/tokenizer.h"
#include "../include/assembler.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

// MAIN DE TESTES

// int main() {
//     string_vector code = readFile("teste.asm");
    
//     token_vector tokens = tokenize(code);

//     // token_vector tokens2 = preprocessar(tokens)

//     IR parsed_code = parse(tokens);

//     string_vector test = assemble(parsed_code);
//     for (auto tst : test) {
//         cout << tst << endl;
//     }

//     createFile(test, "teste", ".o");

//     return 0;
// }
