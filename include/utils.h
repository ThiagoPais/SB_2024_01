#include "typedef.h"

// Read the file provided and returns a string vector
string_vector readFile(string filename);

// Creates file with the given data
bool createFile(string data, string filename, string extension);
bool createFile(string_vector data, string filename, string extension);

// Returns a string_vector with substrings separated by the given delimiter
string_vector split(const string &s, char delimiter);