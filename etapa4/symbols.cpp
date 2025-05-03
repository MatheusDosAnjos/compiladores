/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <algorithm>
#include <string>
#include <map>

#include "symbols.hpp"

using namespace std;

string _reverseNumericString(string text);

static const map<SymbolType, SymbolDataType> typeMap = {
    {SymbolType::IDENTIFIER, SymbolDataType::NONE},
    {SymbolType::INT, SymbolDataType::INT},
    {SymbolType::CHAR, SymbolDataType::CHAR},
    {SymbolType::REAL, SymbolDataType::REAL},
    {SymbolType::STRING, SymbolDataType::STRING},
};

map <string, Symbol*> symbolTable;

Symbol* addSymbol(SymbolType type, char* text) {
    string txtString = string(text);

    // if (type == SymbolType::INT || type == SymbolType::REAL) {
    //     txtString = _reverseNumericString(txtString);
    // }
    
    if (symbolTable.find(txtString) != symbolTable.end()) {
        return symbolTable[txtString];
    }

    Symbol* symbol = new Symbol(type, typeMap.at(type), txtString);
    symbolTable[txtString] = symbol;

    return symbol;
}

string _reverseNumericString(string text) {
    auto div = text.find('/');

    if (div == string::npos) {
        // (INT) No '/', reverses whole string
        reverse(text.begin(), text.end());
    } else {
        // (REAL) Has '/', reverses numeric characters
        reverse(text.begin(), text.begin() + div);
        reverse(text.begin() + div + 1, text.end());
    }

    return text;
}

void printSymbolTable() {
    fprintf(stderr, "\nPrinting symbol table:\n");

    for (auto const& x : symbolTable) {
        switch (x.second->type) {
            case SymbolType::IDENTIFIER:
                fprintf(stderr, "Symbol[IDENTIFIER, ");
                break;
            case SymbolType::VARIABLE:
                fprintf(stderr, "Symbol[VARIABLE, ");
                break;
            case SymbolType::ARRAY:
                fprintf(stderr, "Symbol[ARRAY, ");
                break;
            case SymbolType::FUNCTION:
                fprintf(stderr, "Symbol[FUNCTION, ");
                break;
            case SymbolType::INT:
                fprintf(stderr, "Symbol[INT, ");
                break;
            case SymbolType::CHAR:
                fprintf(stderr, "Symbol[CHAR, ");
                break;
            case SymbolType::REAL:
                fprintf(stderr, "Symbol[REAL, ");
                break;
            case SymbolType::STRING:
                fprintf(stderr, "Symbol[STRING, ");
        }

        fprintf(stderr, "%s]", x.first.c_str());

        switch (x.second->dataType) {
            case SymbolDataType::NONE:
                fprintf(stderr, " = NONE\n");
                break;
            case SymbolDataType::INT:
                fprintf(stderr, " = INT\n");
                break;
            case SymbolDataType::BYTE:
                fprintf(stderr, " = BYTE\n");
                break;
            case SymbolDataType::CHAR:
                fprintf(stderr, " = CHAR\n");
                break;
            case SymbolDataType::REAL:
                fprintf(stderr, " = REAL\n");
                break;
            case SymbolDataType::STRING:
                fprintf(stderr, " = STRING\n");
                break;
        }
    }
}