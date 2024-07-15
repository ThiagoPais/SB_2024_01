#include <fstream>
#include <iostream>
#include <string>
#include "../include/utils.h"

using namespace std;

int main(int argc, char *argv[]) {
    string op = argv[1];
    string file = argv[2];
    string file_name = file.substr(0, file.find_last_of('.'));

    string_vector read_file = readFile(file);
    // fazer pre-processamento

    if (op == "-p") { // Pre-processamento
        // createFile(pre_processed_file, file_name, '.pre')
        // retorna objeto pre-processado
        return 0;
    } 
    
    else if (op == "-o") { // Montagem
        // montagem
        return 0;
    }

    else {
        throw std::invalid_argument("Nenhum comando reconhecido.");
    }
}