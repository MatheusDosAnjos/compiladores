/*
27/06/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef ASM_HPP
#define ASM_HPP

#include <string>
#include "ast.hpp"
#include "tac.hpp"

std::string generateAsm(Tac* tacList, AstNode* root);

#endif