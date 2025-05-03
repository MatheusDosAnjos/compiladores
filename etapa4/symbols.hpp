/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <string>

enum class SymbolType {
    IDENTIFIER, VARIABLE, ARRAY, FUNCTION, INT, CHAR, REAL, STRING
};

enum class SymbolDataType {
    NONE, INT, BYTE, CHAR, REAL, STRING
};

struct Symbol {
    SymbolType type;
    SymbolDataType dataType;
    std::string text;
    public: Symbol(SymbolType t, SymbolDataType dt, std::string s): type(t), dataType(dt), text(s) {}
};

Symbol* addSymbol(SymbolType type, char* text);
void printSymbolTable(void);

#endif