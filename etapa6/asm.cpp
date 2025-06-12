/*
27/06/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <string>
#include <sstream>
#include <map>
#include "ast.hpp"
#include "datatype.hpp"
#include "tac.hpp"

using namespace std;

map<Symbol*, string> stringIdxMap;

string generateDataSection() {
    stringstream ss;

    ss << "    .text\n    .data\n";
    ss << ".printInt:\n    .string    \"%d\"\n";

    for (const auto& [text, symbol] : symbolTable) {
        if (symbol->type == SymbolType::STRING) {
            stringIdxMap[symbol] = ".str_" + to_string(stringIdxMap.size());
            ss << stringIdxMap[symbol] << ":\n";
            ss << "    .string    " << symbol->text << "\n";
            continue;
        }

        if (symbol->type == SymbolType::VARIABLE || symbol->type == SymbolType::ARRAY) {
            ss << "_" << symbol->text << ":\n";
            if (symbolInitializers[symbol].empty()) {
                ss << "    .long    0\n";
            } else {
                for (const auto& init : symbolInitializers[symbol]) {
                    ss << "    .long    " << init->text << "\n";
                }
            }
            continue;
        } 
        
        if (symbol->type == SymbolType::INT) {
            ss << "_" << symbol->text << ":\n    .long    " << symbol->text << "\n";
        } else if (symbol->type == SymbolType::IDENTIFIER) {
            ss << "_" << symbol->text << ":\n    .long    0\n";
        }
    }

    ss << "    .text\n";
        
    return ss.str();
}

string generateAsm(Tac* tacList) {
    stringstream ss;

    ss << generateDataSection();

    for (; tacList; tacList = tacList->next) {
        switch (tacList->type) {
            case TacType::MOVE:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
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
                if (tacList->res->dataType == DataType::STRING) {
                    ss << "    leaq    " << stringIdxMap[tacList->res] << "(%rip), %rax\n";
                    ss << "    movq    %rax, %rdi\n";
                    ss << "    call    printf@PLT\n";
                } else if (tacList->res->dataType == DataType::INT) {
                    ss << "    movl    _" << tacList->res->text << "(%rip), %eax\n";
                    ss << "    movl    %eax, %esi\n";
                    ss << "    leaq    .printInt(%rip), %rax\n";
                    ss << "    movq    %rax, %rdi\n";
                    ss << "    call    printf@PLT\n";
                } else if (tacList->res->dataType == DataType::CHAR) {
                    ss << "    movl    _" << tacList->res->text << "(%rip), %eax\n";
                    ss << "    movl    %eax, %edi\n";
                    ss << "    call    putchar@PLT\n";
                }
                break;
        }
    }

    return ss.str();
}