/*
15/04/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

#include "semantic/datatype.hpp"
#include "symbols.hpp"

enum class AstNodeType {
    DECL_LIST, VAR_DECL, ARRAY_DECL, ARRAY_INIT, FUNC_DECL, PARAM_LIST,
    VAR_DEF, SYMBOL, BYTE, INT, REAL,
    CMD_BLOCK, CMD_LIST, ASSIGN, ASSIGN_ARRAY_ELEM, ARRAY_ELEM,
    IF, IF_ELSE, WHILE_DO, DO_WHILE, READ, PRINT, RETURN,
    ADD, SUB, MULT, DIV, LESS, GREATER, AND, OR, LE, GE, EQ, DIF, NOT,
    FUNC_CALL, ARG_LIST
};

struct AstNode {
    AstNodeType type;
    DataType dataType = DataType::NONE;
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