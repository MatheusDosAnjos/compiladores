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
    UNKNOWN, SYMBOL, DECL_LIST, BYTE, INT, REAL,
    VAR_DECL, VAR_DEF, ARRAY_DECL, ARRAY_INIT, FUNC_DECL, PARAM_LIST,
    CMD_LIST, ASSIGN, ARRAY_ELEM, IF, IF_ELSE, WHILE_DO, DO_WHILE, READ, PRINT, RETURN,
    ADD, SUB, MULT, DIV, LESS, GREATER, AND, OR, LE, GE, EQ, DIF, NOT,
    FUNC_CALL, ARG_LIST
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

inline std::vector<AstNode*>* createAstNodeList(AstNode* node) {
    auto nodeList = new std::vector<AstNode*>();
    nodeList->push_back(node);
    return nodeList;
}

inline std::vector<AstNode*>* insertAstNodeItem(AstNode* node, std::vector<AstNode*>* nodeList) {
    nodeList->insert(nodeList->begin(), node);
    return nodeList;
}

std::string decompileAstNode(AstNode* node);
void printAst(AstNode* node, int level = 0);

#endif