/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <string>

enum class SymbolType {
    IDENTIFIER, INT, CHAR, REAL, STRING
};

enum class SymbolDataType {
    INT, CHAR, REAL, STRING
};

struct Symbol {
    SymbolType type;
    SymbolDataType dataType;
    std::string text;
    public: Symbol(SymbolType t, std::string s): type(t), text(s) {}
};

Symbol* addSymbol(SymbolType type, char* text);
void printSymbolTable(void);

#endif