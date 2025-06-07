/*
01/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include <map>
#include "ast.hpp"

extern std::map<Symbol*, AstNode*> functionDeclarations;

void runSemanticAnalysis(AstNode* node);
bool hasSematicErrors();

#endif