#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    string op = argv[1];
    string file = argv[2];
    string file_name = file.substr(0, file.find_last_of('.'));

    if (op == "-p") { // Pre-processamento
        // fazer pre-processamento
        // object pre_processed_file
        // pre_processed_file = preprocess(file)
        // createFile(pre_processed_file, '.pre')
    } 
    
    else if (op == "-o") { // Montagem
        // montagem
    }

    else {
        throw std::invalid_argument("Nenhum comando reconhecido.");
    }
}