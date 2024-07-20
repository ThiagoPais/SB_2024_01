#include "../include/assembler.h"

string assemble(IR ir) {
    string_vector assembled_code;
    string res;
    for (auto cmd : ir.commands) {
        assembled_code.push_back(to_string(cmd.cmd.opcode));
        for (auto param : cmd.params) {
            assembled_code.push_back(param);
        }
    }
    for (auto memory : ir.memory_spaces) {
        assembled_code.push_back(to_string(memory));
    }

    for (auto ass : assembled_code) {
        res.append(ass);
        res.append(" ");
    }
    return res;
}