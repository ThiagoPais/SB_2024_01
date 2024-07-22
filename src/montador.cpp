#include <fstream>
#include <iostream>
#include <string>
#include "../include/preprocessor.h"
#include "../include/assembler.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) throw std::invalid_argument("Not enough arguments!");
    string op = argv[1];
    string file = argv[2];
    string file_name = file.substr(0, file.find_last_of('.'));


    string_vector code = readFile(file);
    
    // atualizar code com a funcao de preprocessamento
    token_vector tokens = tokenize(code);
    token_vector preprocessed_code = preprocess(tokens);

    if (op == "-p") { // Pre-processamento
        createFile(preprocessed_code, file_name, ".pre");
        return 0;
    }
    
    else if (op == "-o") { // Montagem
        IR parsed_code = parse(preprocessed_code);

        string_vector assembled = assemble(parsed_code);

        createFile(assembled, file_name, ".o");
        // string_vector code = readFile("teste.o");
        // for (auto c : code) {
        //     cout << c << endl;
        // }

        return 0;
    }

    else {
        throw std::invalid_argument("Nenhum comando reconhecido.");
    }
}