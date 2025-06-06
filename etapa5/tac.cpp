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
Tac* generateIfElseCode(Tac* condition, Tac* ifCode, Tac* elseCode);

const map<TacType, const char*> tacTypeLabel = {
    {TacType::SYMBOL, "SYMBOL"},
    {TacType::MOVE, "MOVE"},
    {TacType::MOVE_IDX, "MOVE_IDX"},
    {TacType::IDX_ACCESS, "IDX_ACCESS"},
    {TacType::IF, "IF"},
    {TacType::IF_ELSE, "IF_ELSE"},
    {TacType::WHILE_DO, "WHILE_DO"},
    {TacType::DO_WHILE, "DO_WHILE"},
    {TacType::IFZ, "IFZ"},
    {TacType::JUMP, "JUMP"},
    {TacType::LABEL, "LABEL"},
    {TacType::READ, "READ"},
    {TacType::PRINT, "PRINT"},
    {TacType::RETURN, "RETURN"},
    {TacType::ADD, "ADD"},
    {TacType::SUB, "SUB"},
    {TacType::MULT, "MULT"},
    {TacType::DIV, "DIV"},
    {TacType::LESS, "LESS"},
    {TacType::GREATER, "GREATER"},
    {TacType::AND, "AND"},
    {TacType::OR, "OR"},
    {TacType::LE, "LE"},
    {TacType::GE, "GE"},
    {TacType::EQ, "EQ"},
    {TacType::DIF, "DIF"},
    {TacType::NOT, "NOT"}
};

const map<AstNodeType, TacType> astToTacType = {
    {AstNodeType::ADD, TacType::ADD},
    {AstNodeType::SUB, TacType::SUB},
    {AstNodeType::MULT, TacType::MULT},
    {AstNodeType::DIV, TacType::DIV},
    {AstNodeType::LESS, TacType::LESS},
    {AstNodeType::GREATER, TacType::GREATER},
    {AstNodeType::LE, TacType::LE},
    {AstNodeType::GE, TacType::GE},
    {AstNodeType::EQ, TacType::EQ},
    {AstNodeType::DIF, TacType::DIF},
    {AstNodeType::AND, TacType::AND},
    {AstNodeType::OR, TacType::OR}
};

void printTac(Tac* tac) {
    if (!tac) return;

    fprintf(stderr, "Tac(%s", tacTypeLabel.at(tac->type));
    fprintf(stderr, ", %s", tac->res ? tac->res->text.c_str() : "-");
    fprintf(stderr, ", %s", tac->op1 ? tac->op1->text.c_str() : "-");
    fprintf(stderr, ", %s)\n", tac->op2 ? tac->op2->text.c_str() : "-");
}

void printInvertedTacList(Tac* tac) {
    for (; tac; tac = tac->prev) {
        if (tac->type == TacType::SYMBOL) continue;
        printTac(tac);
    }
}

Tac* joinTacs(Tac* first, Tac* second) {
    if (!first) return second;
    if (!second) return first;

    Tac* cur = second;
    for (; cur->prev; cur = cur->prev);

    cur->prev = first;

    return second;
}

Tac* generateCode(AstNode* node) {
    if (!node) return nullptr;

    Tac* result = nullptr;
    std::vector<Tac*> codes;

    for (auto& child : node->children) {
        codes.push_back(generateCode(child));
    }

    switch (node->type) {
        case AstNodeType::SYMBOL:
            result = new Tac(TacType::SYMBOL, node->symbol);
            break;
        case AstNodeType::ASSIGN:
            result = new Tac(TacType::MOVE, node->symbol, codes[0]->res);
            result = joinTacs(codes[0], result);
            break;
        case AstNodeType::ASSIGN_ARRAY_ELEM:
            result = new Tac(TacType::MOVE_IDX, node->symbol, codes[0]->res, codes[1]->res);
            result = joinTacs(joinTacs(codes[0], codes[1]), result);
            break;
        case AstNodeType::ARRAY_ELEM:
            result = new Tac(TacType::IDX_ACCESS, makeSymbol(), node->symbol, codes[0]->res);
            result = joinTacs(codes[0], result);
            break;
        // TODO
        case AstNodeType::IF:
        case AstNodeType::IF_ELSE:
            break;
        // TODO
        case AstNodeType::WHILE_DO:
            break;
        // TODO
        case AstNodeType::DO_WHILE:
            break;
        case AstNodeType::READ:
            result = new Tac(TacType::READ, node->symbol);
            break;
        case AstNodeType::PRINT:
            for (Tac* code : codes) {
                Tac* printTac = new Tac(TacType::PRINT, code->res);
                result = joinTacs(joinTacs(result, code), printTac);
            }
            break;
        case AstNodeType::RETURN:
            result = new Tac(TacType::RETURN, codes[0]->res);
            result = joinTacs(codes[0], result);
            break;
        case AstNodeType::ADD:
        case AstNodeType::SUB:
        case AstNodeType::MULT:
        case AstNodeType::DIV:
        case AstNodeType::LESS:
        case AstNodeType::GREATER:
        case AstNodeType::LE:
        case AstNodeType::GE:
        case AstNodeType::EQ:
        case AstNodeType::DIF:
        case AstNodeType::AND:
        case AstNodeType::OR:
            result = new Tac(astToTacType.at(node->type), makeSymbol(), codes[0]->res, codes[1]->res);
            result = joinTacs(joinTacs(codes[0], codes[1]), result);
            break;
        case AstNodeType::NOT:
            result = new Tac(TacType::NOT, makeSymbol(), codes[0]->res);
            result = joinTacs(codes[0], result);
            break;
        default:
            for (Tac* code : codes) {
                result = joinTacs(result, code);
            }
            break;
    }

    return result;
}