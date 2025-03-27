/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <string>
#include <map>

#include "symbols.hpp"
#include "tokens.h"

using namespace std;

map <string, SYMBOL*> symbolTable;

SYMBOL* addSymbol(int type, char *text) {
    string txtString = string(text);

    if (symbolTable.find(txtString) != symbolTable.end()) {
        return symbolTable[txtString];
    }

    SYMBOL* symbol = new SYMBOL(type, txtString);
    symbolTable[txtString] = symbol;

    return symbol;
}

void printSymbolTable() {
    fprintf(stderr, "\nPrinting symbol table:\n");

    for (auto const& x : symbolTable) {
        switch (x.second->type) {
            case TK_IDENTIFIER:
                fprintf(stderr, "TK_IDENTIFIER ");
                break;
            case LIT_INT:
                fprintf(stderr, "LIT_INT ");
                break;
            case LIT_CHAR:
                fprintf(stderr, "LIT_CHAR ");
                break;
            case LIT_REAL:
                fprintf(stderr, "LIT_REAL ");
                break;
            case LIT_STRING:
                fprintf(stderr, "LIT_STRING ");
        }

        fprintf(stderr, "%s\n", x.first.c_str());
    }
}