#include "../include/parser.h"
#include <string>

struct IRCommand {
    IRCommand(command cmd, string_vector params) : cmd(cmd), params(params) {};

    command cmd;
    string_vector params;
};

void parse(token_vector &tokens) {
    short int currentMemoryPosition = 0;
    symbol_table st;
    for (size_t i = 0; i < tokens.size(); i++) {
        // Labels   
        if (tokens[i].text.back() == ':') {
            string label = tokens[i].text.substr(0, tokens[i].text.size() - 1);
            if (st.count(label) && st[label].defined) {
                // Redefinição de label
                throw std::invalid_argument("ERROR: Redefinição de label. Linha: " + to_string(tokens[i].line) + " Label: " + label);
            }

            if (!st.count(label)) {
                // Label nunca antes vista
                Symbol symbol(currentMemoryPosition, true, {});
                st[label] = symbol;
            } else {
                // Label já utilizada
                st[label].value = currentMemoryPosition;
                // Volta para todas as ocasiões anteriores e substitui a label pelo valor da memória
                for (auto pendency : st[label].pendency_list) {
                    //
                }
                st[label].defined = true;
            }
        // Commands
        } else if (dictionary::commands.count(tokens[i].text)) {
            IRCommand irCmd(dictionary::commands[tokens[i].text], {});
            irCmd.cmd = dictionary::commands[tokens[i].text];
            while (++i < tokens.size() && tokens[i].line == tokens[i-1].line) {
                // Check label
                if (isNumeric(tokens[i].text)) {
                    // Just a number
                    irCmd.params.push_back(tokens[i].text);
                } else if (st.count(tokens[i].text)) {
                    // Symbol on symbol table
                    if (st[tokens[i].text].defined) {
                        // Defined
                        irCmd.params.push_back(to_string(st[tokens[i].text].value));
                    } else {
                        // Not yet defined
                        irCmd.params.push_back(tokens[i].text);
                        st[tokens[i].text].pendency_list.push_back(tokens[i].line);
                    }
                } else {
                    // Symbol not on symbol table
                    irCmd.params.push_back(tokens[i].text);
                    Symbol symbol(-1, false, {tokens[i].line});
                    st[tokens[i].text] = symbol;
                }

                if (irCmd.params.size() > irCmd.cmd.size - 1) {
                    throw std::invalid_argument("ERROR: Too many arguments! Line: " + to_string(tokens[i].line) + " Command: " + tokens[i].text);
                } else if (irCmd.params.size() < irCmd.cmd.size - 1) {
                    throw std::invalid_argument("ERROR: Not enough arguments! Line: " + to_string(tokens[i].line) + " Command: " + tokens[i].text);
                }
            }
            // ir.commands.push_back(irCmd);
            currentMemoryPosition += irCmd.cmd.size;
        }

    }
}


bool isNumeric (std::string s){
    for (auto c : s)
        if (!isNumeric(c))
            return false;
    return true;
}

bool isNumeric (char c){
    return (c >= '0' && c <= '9');
}