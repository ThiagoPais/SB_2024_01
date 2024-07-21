#include "typedef.h"
#include <string>

// Read the file provided and returns a string vector
string_vector readFile(const string& filePath);

// Creates file with the given data
bool createFile(string data, string filename, string extension);
bool createFile(string_vector data, string filename, string extension);
bool createFile(token_vector data, string filename, string extension);

// Returns a string_vector with substrings separated by the given delimiter
string_vector split(const string &s, char delimiter);