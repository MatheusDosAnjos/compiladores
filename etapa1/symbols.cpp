/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include "symbols.hpp"
#include <string>
#include <map>

using namespace std;

map <string, SYMBOL*> symbolTable;

SYMBOL* addSymbol(int type, char *text)
{
    string txtString = string(text);

    if (symbolTable.find(txtString) != symbolTable.end()) {
        return symbolTable[txtString];
    }

    SYMBOL* symbol = new SYMBOL(type, txtString);
    symbolTable[txtString] = symbol;

    return symbol;
}

void printSymbolTable()
{
    for (auto const& x : symbolTable)
    {
        fprintf(stderr, "%s %d\n", x.first.c_str(), x.second->type);
    }
}