/*
27/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include "tac.hpp"
#include "ast.hpp"

using namespace std;

void printTac(Tac* tac);
void printInvertedTacList(Tac* tac);
Tac* joinTacs(Tac* first, Tac* second);

const char* tacTypeLabel[] = {
    "SYMBOL", "ADD"
};

void printTac(Tac* tac) {
    if (!tac) return;

    fprintf(stderr, "Tac(%s", tacTypeLabel[static_cast<int>(tac->type)]);
    fprintf(stderr, ",%s", tac->res ? tac->res->text.c_str() : "-");
    fprintf(stderr, ",%s", tac->op1 ? tac->op1->text.c_str() : "-");
    fprintf(stderr, ",%s)\n", tac->op2 ? tac->op2->text.c_str() : "-");
}

void printInvertedTacList(Tac* tac) {
    for (; tac; tac = tac->prev) {
        printTac(tac);
    }
}

Tac* generateCode(AstNode* node) {
    if (!node) return nullptr;

    Tac* result = nullptr;
    std::vector<Tac*> codes;

    for (auto& child : node->children) {
        codes.push_back(generateCode(child));
    }

    Tac* codeList = nullptr;
    for (Tac* code : codes) {
        codeList = joinTacs(codeList, code);
    }

    switch (node->type) {
        case AstNodeType::SYMBOL:
            result = new Tac(TacType::SYMBOL, node->symbol);
            break;
        case AstNodeType::ADD:
            result = new Tac(TacType::ADD, createTempSymbol(), codes[0]->res, codes[1]->res);
            result = joinTacs(codeList, result);
            break;
        default:
            result = codeList;
    }

    return result;
}

Tac* joinTacs(Tac* first, Tac* second) {
    if (!first) return second;
    if (!second) return first;

    Tac* cur = second;
    for (; cur->prev; cur = cur->prev);

    cur->prev = first;

    return second;
}