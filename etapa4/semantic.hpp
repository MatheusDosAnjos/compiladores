/*
01/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include "ast.hpp"

void runSemanticAnalysis(AstNode* node);
bool hasSematicErrors();

#endif