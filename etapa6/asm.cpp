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

    for (const auto& pair : symbolTable) {
        Symbol* symbol = pair.second;

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
        
        if (symbol->type == SymbolType::INT || symbol->type == SymbolType::CHAR) {
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
            case TacType::MOVE_IDX:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";   // index -> eax
                ss << "    movl    _" << tacList->op2->text << "(%rip), %edx\n";   // value -> edx
                ss << "    leaq    _" << tacList->res->text << "(%rip), %rcx\n";   // base array address -> rcx (RIP-relative addressing)
                ss << "    movl    %edx, (%rcx, %rax, 4)\n";                       // value -> array[index]
                break;
            case TacType::IDX_ACCESS:
                ss << "    movl    _"   << tacList->op2->text << "(%rip), %eax\n";   // index -> eax
                ss << "    leaq    _" << tacList->op1->text << "(%rip), %rcx\n";     // base array address -> rcx (RIP-relative addressing)
                ss << "    movl    (%rcx, %rax, 4), %eax\n";                         // array[index] -> eax
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";     // eax -> res
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
            case TacType::LABEL:
                ss << tacList->res->text << ":\n";
                break;
            case TacType::JUMP:
                ss << "    jmp    " << tacList->res->text << "\n";
                break;
            case TacType::IFZ:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    testl   %eax, %eax\n";
                ss << "    jz      " << tacList->res->text << "\n";
                break;
            case TacType::READ:
                ss << "    leaq    _" << tacList->res->text << "(%rip), %rsi\n";
                ss << "    leaq    .printInt(%rip), %rdi\n";
                ss << "    call    scanf@PLT\n";
                break;
            case TacType::PRINT: {
                DataType dt = tacList->res->dataType;

                if (dt == DataType::STRING) {
                    ss << "    leaq    " << stringIdxMap[tacList->res] << "(%rip), %rax\n";
                    ss << "    movq    %rax, %rdi\n";
                    ss << "    call    printf@PLT\n";
                } else if (dt == DataType::INT || dt == DataType::NONE) {
                    ss << "    movl    _" << tacList->res->text << "(%rip), %eax\n";
                    ss << "    movl    %eax, %esi\n";
                    ss << "    leaq    .printInt(%rip), %rax\n";
                    ss << "    movq    %rax, %rdi\n";
                    ss << "    call    printf@PLT\n";
                } else if (dt == DataType::CHAR) {
                    ss << "    movl    _" << tacList->res->text << "(%rip), %eax\n";
                    ss << "    movl    %eax, %edi\n";
                    ss << "    call    putchar@PLT\n";
                }
                break;
            }
            case TacType::RETURN:
                ss << "    movl    _" << tacList->res->text << "(%rip), %eax\n";
                ss << "    popq    %rbp\n";
                ss << "    ret\n";
                break;
            case TacType::FUNC_CALL:
                ss << "    call    " << tacList->op1->text << "\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::ARG:
                ss << "    movl    _" << tacList->res->text << "(%rip), %eax\n";
                ss << "    movl    %eax, _" << tacList->op2->text << "(%rip)\n";
                break;
            case TacType::ADD:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    addl    _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::SUB:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    subl    _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::MULT:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    imull   _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::DIV:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    cltd\n";
                ss << "    idivl   _" << tacList->op2->text << "(%rip)\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::LESS:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    cmpl    _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    setl    %al\n";
                ss << "    movzbl  %al, %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::GREATER:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    cmpl    _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    setg    %al\n";
                ss << "    movzbl  %al, %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::LE:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    cmpl    _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    setle   %al\n";
                ss << "    movzbl  %al, %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::GE:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    cmpl    _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    setge   %al\n";
                ss << "    movzbl  %al, %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::EQ:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    cmpl    _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    sete    %al\n";
                ss << "    movzbl  %al, %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::DIF:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    cmpl    _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    setne   %al\n";
                ss << "    movzbl  %al, %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::AND:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    andl    _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::OR:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    orl     _" << tacList->op2->text << "(%rip), %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            case TacType::NOT:
                ss << "    movl    _" << tacList->op1->text << "(%rip), %eax\n";
                ss << "    cmpl    $0, %eax\n";
                ss << "    sete    %al\n";
                ss << "    movzbl  %al, %eax\n";
                ss << "    movl    %eax, _" << tacList->res->text << "(%rip)\n";
                break;
            default:
                break;
        }
    }

    return ss.str();
}