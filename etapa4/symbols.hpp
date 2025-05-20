/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <map>
#include <set>
#include <string>

#include "datatype.hpp"

enum class SymbolType {
    IDENTIFIER, VARIABLE, ARRAY, FUNCTION, INT, CHAR, REAL, STRING
};

struct Symbol {
    SymbolType type;
    DataType dataType;
    std::string text;
    public: Symbol(SymbolType t, DataType dt, std::string s): type(t), dataType(dt), text(s) {}
};

extern std::map<std::string, Symbol*> symbolTable;

Symbol* addSymbol(SymbolType type, char* text);
void printSymbolTable(void);

bool isLiteral(SymbolType type) noexcept;

#endif