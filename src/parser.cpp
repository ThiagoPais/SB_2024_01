#include "../include/parser.h"
#include <string>
#include <algorithm>


IR parse(token_vector &tokens) {
    short int           current_memory_position = 0;

    symbol_table        st;
    use_table           use_table;
    def_table           def_table;

    vector<IRCommand>   ir_commands;
    vector<int>         memory_spaces;

    std::map<std::string, command>   commands   = initializeCommands();
    std::map<std::string, directive> directives = initializeDirectives();

    bool isModule = false;
    
    for (size_t i = 0; i < tokens.size(); i++) {
        // Labels   
        if (tokens[i].text.back() == ':') {
            verifyLabel(tokens[i]);

            string label = tokens[i].text.substr(0, tokens[i].text.size() - 1);
            if (i+1 < tokens.size() && tokens[i+1].text.back() == ':') {
                throw std::invalid_argument("SYNTAX ERROR! Label dobrada na mesma linha. Linha: " + to_string(tokens[i].line) + " Label: " + label);
            }

            if (st.count(label) && st[label].defined) {
                // Redefinição de label
                throw std::invalid_argument("SYNTAX ERROR! Redefinição de label. Linha: " + to_string(tokens[i].line) + " Label: " + label);
            }

            if (!st.count(label)) {
                // Label nunca antes vista
                if (i+1 < tokens.size() && tokens[i+1].line == tokens[i].line && tokens[i+1].text == "EXTERN") {
                    Symbol symbol(0, true, {}, true);
                    st[label] = symbol;
                    use_table[label] = {};
                    i++;
                } else {
                    Symbol symbol(current_memory_position, true, {});
                    st[label] = symbol;
                }
            } else {
                // Label na tabela de definições
                if (def_table.count(label)) {
                    def_table[label] = current_memory_position;
                }
                // Label já utilizada
                st[label].value = current_memory_position;

                // Volta para todas as ocasiões anteriores e substitui a label pelo valor da memória
                for (size_t pdc : st[label].pendency_list) {
                    replace(ir_commands[pdc].params.begin(), ir_commands[pdc].params.end(), label, to_string(st[label].value));
                }
                st[label].defined = true;
            }
        // Commands
        } else if (commands.count(tokens[i].text)) {
            IRCommand irCmd(commands[tokens[i].text], {});
            current_memory_position += 1;
            while (i+1 < tokens.size() && tokens[i+1].line == tokens[i].line) {
                i++;
                // Check label
                verifyLabel(tokens[i]);

                if (use_table.count(tokens[i].text)) {
                    use_table[tokens[i].text].push_back(current_memory_position);
                }
                
                if (st.count(tokens[i].text)) {
                    // Symbol on symbol table
                    if (st[tokens[i].text].defined) {
                        // Defined
                        irCmd.params.push_back(to_string(st[tokens[i].text].value));
                    } else {
                        // Not yet defined
                        irCmd.params.push_back(tokens[i].text);
                        st[tokens[i].text].pendency_list.push_back(ir_commands.size());
                    }
                } else {
                    // Symbol not on symbol table
                    irCmd.params.push_back(tokens[i].text);
                    Symbol symbol(-1, false, {(short)ir_commands.size()});
                    st[tokens[i].text] = symbol;
                }

                current_memory_position += 1;

            }
            if (irCmd.params.size() > irCmd.cmd.size - 1) {
                throw std::invalid_argument("SYNTAX ERROR! Too many arguments! Line: " + to_string(tokens[i].line) + " Command: " + to_string(irCmd.cmd.name));
            } else if (irCmd.params.size() < irCmd.cmd.size - 1) {
                throw std::invalid_argument("SYNTAX ERROR! Not enough arguments! Line: " + to_string(tokens[i].line) + " Command: " + to_string(irCmd.cmd.name));
            }
            ir_commands.push_back(irCmd);
            
        } else if (tokens[i].text == "PUBLIC") {
            if (i+1 < tokens.size() && tokens[i+1].line == tokens[i].line) {
                i++;
                def_table[tokens[i].text] =  {};
            }

        } else if (tokens[i].text == "BEGIN" || tokens[i].text == "END") {
            isModule = true;

        } else if (tokens[i].text == "CONST") {
            if (i+1 < tokens.size() && tokens[i+1].line == tokens[i].line) {
                i++;
                memory_spaces.push_back(stoi(tokens[i].text));
                current_memory_position += 1;

            } else if (i+2 < tokens.size() && tokens[i+2].line == tokens[i].line) {
                throw std::invalid_argument("SYNTAX ERROR! Argumentos demais! Linha: " + to_string(tokens[i].line));

            } else {
                throw std::invalid_argument("SYNTAX ERROR! Nenhum argumento apresentado para a diretiva CONST! Linha: " + to_string(tokens[i].line));
            }

        } else if (tokens[i].text == "SPACE") {
            if (i+1 < tokens.size() && tokens[i+1].line == tokens[i].line) {
                throw std::invalid_argument("SYNTAX ERROR! Diretiva SPACE nao aceita argumentos! Linha: " + to_string(tokens[i].line));
            }
            memory_spaces.push_back(0);
            current_memory_position += 1;

        } else {
            throw std::invalid_argument("SYNTAX ERROR! Comando ou diretiva nao reconhecido. Linha: " + to_string(tokens[i].line) + "Comando: " + tokens[i].text);
        }
    }

    for (auto pair : st) {
        if (!pair.second.defined) {
            throw std::invalid_argument("SEMANTIC ERROR! Label nunca definida. Label: " + pair.first);
        }
    }

    #ifdef DEBUG_SYMBOL_TABLE
    for (const auto& entry : st) {
        const std::string& symbol_name = entry.first;
        const Symbol& symbol = entry.second;
        
        std::cout << "Symbol: " << symbol_name << "\n";
        std::cout << "  Value: " << symbol.value << "\n";
        std::cout << "  Defined: " << (symbol.defined ? "true" : "false") << "\n";
        std::cout << "  Pendency List: [";
        for (size_t i = 0; i < symbol.pendency_list.size(); ++i) {
            std::cout << symbol.pendency_list[i];
            if (i != symbol.pendency_list.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
    #endif

    #ifdef DEBUG_USE_TABLE
    for (const auto& entry : use_table) {
        const std::string& symbol_name = entry.first;
        const vector<int> symbol_uses = entry.second;
        
        std::cout << "Symbol: " << symbol_name << "\n";
        std::cout << "  Use list: [";
        for (size_t i = 0; i < symbol_uses.size(); ++i) {
            std::cout << symbol_uses[i];
            if (i != symbol_uses.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
    #endif

    #ifdef DEBUG_DEF_TABLE
    for (const auto& entry : def_table) {
        const std::string& symbol_name = entry.first;
        const int symbol = entry.second;
        
        std::cout << "Symbol: " << symbol_name << "\n";
        std::cout << "  def: " << symbol << endl;
    }
    #endif

    IR ir(ir_commands, memory_spaces, isModule, use_table, def_table);
    return ir;
}

void verifyLabel(Token t) {
    string label = t.text;
    if (label.back() == ':') label = label.substr(0, t.text.size() - 1);

    if (isNumeric(label)) {
        throw std::invalid_argument("LEXICAL ERROR! Argumento inválido. Número no lugar de label. Linha: " + to_string(t.line) + " Label: " + label);
    }
    if (isNumeric(label[0])) {
        throw std::invalid_argument("LEXICAL ERROR! Label não pode iniciar com valores numéricos. Linha: " + to_string(t.line) + " Label: " + label);
    } 
    if (hasSpecialSymbols(label)) {
        throw std::invalid_argument("LEXICAL ERROR! Argumento inválido. Label contém caracteres especiais. Linha: " + to_string(t.line) + " Label: " + label);
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

bool isSpecialSymbol(char c) {
    if (!isalnum(c) && c != '_') {
        return true;
    }
    return false;
}

bool hasSpecialSymbols(string str) {
    for (char c : str) {
        if (isSpecialSymbol(c)) {
            return true; 
        }
    }
    return false; 
}