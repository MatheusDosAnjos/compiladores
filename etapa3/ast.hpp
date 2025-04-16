/*
15/04/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

#include "symbols.hpp"

enum class AstNodeType {
    UNKNOWN, SYMBOL, DECL_LIST,
    ADD, SUB, MULT, DIV, LESS, GREATER, AND, OR, LE, GE, EQ, DIF, NOT, ASSIGN,
};

struct AstNode {
    AstNodeType type;
    std::vector<AstNode*> children;
    Symbol* symbol;
    public: AstNode(AstNodeType t, std::vector<AstNode*> c, Symbol* s): type(t), children(c), symbol(s) {}
};

inline AstNode* createAstNode(AstNodeType t, const std::vector<AstNode*> c, Symbol* s = nullptr) {
    return new AstNode(t, c, s);
}

void printAst(AstNode* node, int level = 0);

#endif