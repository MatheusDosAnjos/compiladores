/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <string>

struct SYMBOL {
    int type;
    std::string text;
    public: SYMBOL(int t, std::string s): type(t), text(s) {}
};

SYMBOL* addSymbol(int type, char* text);
void printSymbolTable();

#endif