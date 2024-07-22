#include "../include/assembler.h"

string_vector assemble(IR ir) {
    string_vector module;
    string_vector assembled_code;
    string res;
    string real;

    for (auto cmd : ir.commands) {
        assembled_code.push_back(to_string(cmd.cmd.opcode));
        real += "0";
        for (auto param : cmd.params) {
            assembled_code.push_back(param);
            real += "1";
        }
    }
    for (auto memory : ir.memory_spaces) {
        assembled_code.push_back(to_string(memory));
        real += "0";
    }

    for (auto ass : assembled_code) {
        res.append(ass);
        res.append(" ");
    }
    if (!ir.isModule) {
        return {res};
    }

    module.push_back("USO");
    string uso_line;
    for (auto symbol : ir.use_table) {
        uso_line += symbol.first;
        for (auto use : symbol.second) {
            uso_line += " ";
            uso_line += to_string(use);
        }
        uso_line += " ";
    }
    module.push_back(uso_line);

    module.push_back("DEF");
    string def_line;
    for (auto symbol : ir.def_table) {
        def_line += symbol.first;
        def_line += " ";
        def_line += to_string(symbol.second);
        def_line += " ";
    }
    
    module.push_back(def_line);

    module.push_back("REAL");
    module.push_back(real);

    module.push_back("");
    module.push_back(res);

    return module;
}