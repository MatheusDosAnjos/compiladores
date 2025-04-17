/*
15/04/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <algorithm>
#include <string>
#include <map>

#include "symbols.hpp"
#include "ast.hpp"

using namespace std;

const char* astNodeTypeLabel[] = {
    "UNKNOWN", "SYMBOL", "DECL_LIST", "BYTE", "INT", "REAL",
    "CMD_LIST","ASSIGN", "ARRAY_ELEM", "IF", "IF_ELSE", "WHILE_DO", "DO_WHILE", "READ", "PRINT", "RETURN",
    "ADD", "SUB", "MULT", "DIV", "LESS", "GREATER", "AND", "OR", "LE", "GE", "EQ", "DIF", "NOT",
    "FUNC_CALL", "ARG_LIST"
};

void printAst(AstNode* node, int level) {
    if (!node) return;

    for (int i = 0; i < level; i++) {
        fprintf(stderr, "  ");
    }
    
    fprintf(stderr, "%s", astNodeTypeLabel[static_cast<int>(node->type)]);

    if (node->symbol)
        fprintf(stderr, ": %s", node->symbol->text.c_str());

    fprintf(stderr, "\n");

    for (AstNode* child : node->children) {
        printAst(child, level + 1);
    }
}
