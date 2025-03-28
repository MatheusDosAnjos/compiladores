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

map <string, SYMBOL*> symbolTable;

SYMBOL* addSymbol(SymbolType type, char* text) {
    string txtString = string(text);

    if (type == INT || type == REAL) {
        txtString = _reverseNumericString(txtString);
    }
    
    if (symbolTable.find(txtString) != symbolTable.end()) {
        return symbolTable[txtString];
    }

    SYMBOL* symbol = new SYMBOL(type, txtString);
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
            case IDENTIFIER:
                fprintf(stderr, "Symbol[IDENTIFIER, ");
                break;
            case INT:
                fprintf(stderr, "Symbol[INT, ");
                break;
            case CHAR:
                fprintf(stderr, "Symbol[CHAR, ");
                break;
            case REAL:
                fprintf(stderr, "Symbol[REAL, ");
                break;
            case STRING:
                fprintf(stderr, "Symbol[STRING, ");
        }

        fprintf(stderr, "%s]\n", x.first.c_str());
    }
}