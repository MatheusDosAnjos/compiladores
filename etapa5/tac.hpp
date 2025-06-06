/*
27/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef TAC_HPP
#define TAC_HPP

#include <vector>
#include "ast.hpp"
#include "symbols.hpp"

enum class TacType {
    SYMBOL,
    MOVE, MOVE_IDX, IDX_ACCESS,
    IFZ, JUMP, LABEL, READ, PRINT, RETURN,
    ADD, SUB, MULT, DIV, LESS, GREATER, AND, OR, LE, GE, EQ, DIF, NOT,
};

struct Tac {
    TacType type;
    Symbol* res = nullptr;
    Symbol* op1 = nullptr;
    Symbol* op2 = nullptr;
    Tac* prev = nullptr;
    Tac* next = nullptr;

    public:
        Tac(TacType t, Symbol* r = nullptr, Symbol* o1 = nullptr, Symbol* o2 = nullptr):
            type(t), res(r), op1(o1), op2(o2) {}
};

void printInvertedTacList(Tac* tac);
Tac* generateCode(AstNode* node);

#endif