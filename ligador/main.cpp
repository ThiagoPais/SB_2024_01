#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    string main_file = argv[1];
    string second_file = argv[2];
    string file_name = main_file.substr(0, main_file.find_last_of('.'));

    if (main_file.substr(main_file.find_last_of('.'), -1) != ".obj" || second_file.substr(main_file.find_last_of('.'), -1) != ".obj" ) {
        throw invalid_argument("Formatos não reconhecidos. Utilizar apenas .obj.");
    }


}