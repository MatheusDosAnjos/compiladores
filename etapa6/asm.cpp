/*
27/06/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <string>
#include <sstream>
#include <map>
#include "ast.hpp"
#include "tac.hpp"

using namespace std;

map<Symbol*, string> stringIdxMap;

string generateDataSection() {
    stringstream ss;

    for (const auto& [text, symbol] : symbolTable) {
        if (symbol->type == SymbolType::VARIABLE || symbol->type == SymbolType::ARRAY) {
            ss << symbol->text << ":\n";
            if (symbolInitializers[symbol].empty()) {
                ss << "    .long    0\n";
            } else {
                for (const auto& init : symbolInitializers[symbol]) {
                    ss << "    .long    " << init->text << "\n";
                }
            }
        } else if (symbol->type == SymbolType::STRING) {
            stringIdxMap[symbol] = ".str_" + to_string(stringIdxMap.size());
            ss << stringIdxMap[symbol] << ":\n";
            ss << "    .string    " << symbol->text << "\n";
        }
    }
        
    return ss.str();
}

string generateAsm(Tac* tacList) {
    stringstream ss;

    ss << generateDataSection();

    for (; tacList; tacList = tacList->next) {
        switch (tacList->type) {
            case TacType::BEGIN_FUNC:
                ss << "    .globl    " << tacList->res->text << "\n";
                ss << tacList->res->text << ":\n";
                ss << "    pushq    %rbp\n";
                ss << "    movq    %rsp, %rbp\n";
                break;
            case TacType::END_FUNC:
                ss << "    popq    %rbp\n";
                ss << "    ret\n";
                break;
            case TacType::PRINT:
                if (tacList->res->type == SymbolType::STRING) {
                    ss << "    leaq    " << stringIdxMap[tacList->res] << "(%rip), %rax\n";
                    ss << "    movq    %rax, %rdi\n";
                    ss << "    call    printf@PLT\n";
                }
                break;
        }
    }

    return ss.str();
}