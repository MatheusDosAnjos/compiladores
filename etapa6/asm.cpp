/*
27/06/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <string>
#include <sstream>
#include "ast.hpp"
#include "tac.hpp"

using namespace std;

string generateDataSection(AstNode* root) {
    stringstream ss;
    ss << "    .section    .rodata\n";
        
    return ss.str();
}

string generateAsm(Tac* tacList, AstNode* root) {
    stringstream ss;

    string dataSection = generateDataSection(root);

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
        }
    }

    return ss.str();
}