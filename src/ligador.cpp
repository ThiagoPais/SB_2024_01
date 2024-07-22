#include <fstream>
#include <iostream>
#include <string>
#include "../include/utils.h"
#include "../include/parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3) throw std::invalid_argument("Not enough arguments!");
    string main_file = argv[1];
    string second_file = argv[2];
    string file_name = main_file.substr(0, main_file.find_last_of('.'));

    if (main_file.substr(main_file.find_last_of('.'), -1) != ".obj" || second_file.substr(main_file.find_last_of('.'), -1) != ".obj" ) {
        throw invalid_argument("Formatos não reconhecidos. Utilizar apenas .obj.");
    }

    //Read .obj files
    string_vector textA = readFile(main_file);
    string_vector textB = readFile(second_file);

    //Declaration of tables for each module
    string_vector uso_A;
    string_vector uso_B;
    string_vector def_A;
    string_vector def_B;
    string_vector code_A;
    string_vector code_B;

    //auxiliary variables
    std::string real_B;
    int correction;

    //Extracting tables from .obj files
    for(size_t i = 1; i < textA.size(); i++){
        if(textA[i-1] == "USO" && textA[i] != ""){
            uso_A = split(textA[i], ' ');
        }
        else if(textA[i-1] == "DEF" && textA[i] != ""){
            def_A = split(textA[i], ' ');
        }
        else if(i == textA.size()-1){
            code_A = split(textA[i], ' ');
        }
    }

    for(size_t i = 1; i < textB.size(); i++){
        if(textB[i-1] == "USO" && textB[i] != ""){
            uso_B = split(textB[i], ' ');
        }
        else if(textB[i-1] == "DEF" && textB[i] != ""){
            def_B = split(textB[i], ' ');
        }
        else if(textB[i-1] == "REAL" && textB[i] != ""){
            real_B = textB[i];
        }
        else if(i == textB.size()-1){
            code_B = split(textB[i], ' ');
        }
    }

    correction = code_A.size();


    //Application of correction factors in module B 
    for(size_t i = 0; i < real_B.size(); i++){
        if(real_B[i] == '1'){
            int aux = std::atoi(code_B[i].c_str());
            aux += correction;
            code_B[i] = std::to_string(aux);
        }
    }

    //Replacing external variables in module A
    std::string label;
    for(size_t i = 0; i < uso_A.size(); i++){
        if(!isNumeric(uso_A[i])){
            label = uso_A[i];
        }
        else{
            for(size_t j = 0; j < def_B.size(); j++){
                if(def_B[j] == label){
                    int pos = std::atoi(uso_A[i].c_str());
                    int aux = std::atoi(def_B[j+1].c_str());
                    code_A[pos] = std::to_string(aux + correction);
                    break;
                }
            }
        }
    }

    //Replacing external variables in module B
    for(size_t i = 0; i < uso_B.size(); i++){
        if(!isNumeric(uso_B[i])){
            label = uso_B[i];
        }
        else{
            for(size_t j = 0; j < def_A.size(); j++){
                if(def_A[j] == label){
                    int pos = std::atoi(uso_B[i].c_str());
                    int aux = std::atoi(def_A[j+1].c_str());
                    code_B[pos] = std::to_string(aux);
                    break;
                }
            }
        }
    }


    //Generating final file
    string_vector new_code = concatenate(code_A, code_B);

    createExeFile(new_code, file_name, ".e");

    return 0;
}