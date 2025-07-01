/*
03/06/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include "ast.hpp"
#include "tac.hpp"
#include "semantic.hpp"
#include "symbols.hpp"

using namespace std;

void printTacList(Tac* tac);
Tac* joinTacs(Tac* first, Tac* second);
Tac* generateIfElseCode(Tac* condition, Tac* ifCode, Tac* elseCode);
Tac* generateWhileDoCode(Tac* condition, Tac* code);
Tac* generateDoWhileCode(Tac* condition, Tac* code);
Tac* generateFuncCallCode(Tac* args, Symbol* funcName);

map<Symbol*, std::vector<Symbol*>> symbolInitializers;

const map<TacType, const char*> tacTypeLabel = {
    {TacType::SYMBOL, "SYMBOL"},
    {TacType::BEGIN_FUNC, "BEGIN_FUNC"},
    {TacType::END_FUNC, "END_FUNC"},
    {TacType::MOVE, "MOVE"},
    {TacType::MOVE_IDX, "MOVE_IDX"},
    {TacType::IDX_ACCESS, "IDX_ACCESS"},
    {TacType::IFZ, "IFZ"},
    {TacType::JUMP, "JUMP"},
    {TacType::LABEL, "LABEL"},
    {TacType::READ, "READ"},
    {TacType::PRINT, "PRINT"},
    {TacType::RETURN, "RETURN"},
    {TacType::FUNC_CALL, "FUNC_CALL"},
    {TacType::ARG, "ARG"},
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

const map<AstNodeType, TacType> binaryOpAstToTac = {
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

string printTac(Tac* tac) {
    if (!tac) return "";

    std::stringstream ss;

    ss << "Tac(" << tacTypeLabel.at(tac->type)
       << ", " << (tac->res ? tac->res->text : "-")
       << ", " << (tac->op1 ? tac->op1->text : "-")
       << ", " << (tac->op2 ? tac->op2->text : "-")
       << ")";

    fprintf(stderr, "%s\n", ss.str().c_str());

    return ss.str();
}

void printTacList(Tac* tac) {
    for (; tac; tac = tac->next) {
        if (tac-> type == TacType::LABEL) {
            fprintf(stderr, "-> %s:\n", tac->res->text.c_str());
            continue;
        }
        
        if (tac->type != TacType::SYMBOL)
            printTac(tac);
    }
}

Tac* invertTacList(Tac* tac) {
    if (!tac) return nullptr;

    Tac* curr = tac;
    for (; curr->prev; curr = curr->prev) {
        curr->prev->next = curr;
    }

    return curr;
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
        case AstNodeType::VAR_DECL: {
            Symbol* varName = node->children[0]->symbol;
            Symbol* varValue = node->children[1]->symbol;

            symbolInitializers[varName].push_back(varValue);
        }
            break;
        case AstNodeType::ARRAY_DECL: {
            unsigned int arraySize = stoul(node->symbol->text);
            Symbol* varName = node->children[0]->symbol;

            auto& initializers = symbolInitializers[varName];
            if (node->children.size() > 1) {
                for (auto* item : node->children[1]->children) {
                    initializers.push_back(item->symbol);
                }
            } else {
                string zeroStr = "0";
                static Symbol* zero = makeSymbol(zeroStr);
                initializers.resize(arraySize, zero);
            }
        }
            break;
        case AstNodeType::FUNC_DECL: {
            Symbol* funcName = node->children[0]->symbol;
            result = new Tac(TacType::BEGIN_FUNC, funcName);
            result = joinTacs(result, codes[2]);
            result = joinTacs(result, new Tac(TacType::END_FUNC, funcName));
            break;
        }
        case AstNodeType::ASSIGN:
            result = new Tac(TacType::MOVE, node->symbol, codes[0]->res);
            result = joinTacs(codes[0], result);
            break;
        case AstNodeType::ASSIGN_ARRAY_ELEM:
            result = new Tac(TacType::MOVE_IDX, codes[0]->op1, codes[0]->op2, codes[1]->res);
            result = joinTacs(joinTacs(codes[0], codes[1]), result);
            break;
        case AstNodeType::ARRAY_ELEM:
            result = new Tac(TacType::IDX_ACCESS, makeSymbol(), node->symbol, codes[0]->res);
            result = joinTacs(codes[0], result);
            break;
        case AstNodeType::IF:
        case AstNodeType::IF_ELSE:
            result = generateIfElseCode(codes[0], codes[1], codes.size() > 2 ? codes[2] : nullptr);
            break;
        case AstNodeType::WHILE_DO:
            result = generateWhileDoCode(codes[0], codes[1]);
            break;
        case AstNodeType::DO_WHILE:
            result = generateDoWhileCode(codes[1], codes[0]);
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
        case AstNodeType::FUNC_CALL:
            result = generateFuncCallCode(codes[0], node->symbol);
            break;
        case AstNodeType::ARG_LIST: {
            Tac* computationCode = nullptr;
            Tac* argPassingCode = nullptr;

            // Joins all the code that computes the argument values.
            // This ensures all inner function calls are resolved first.
            for (Tac* code : codes) {
                computationCode = joinTacs(computationCode, code);
            }

            // Creates a clean, contiguous block of ARG TACs for argument passing.
            for (Tac* code : codes) {
                argPassingCode = joinTacs(argPassingCode, new Tac(TacType::ARG, code->res));
            }
            
            result = joinTacs(computationCode, argPassingCode);
        }
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
            result = new Tac(binaryOpAstToTac.at(node->type), makeSymbol(), codes[0]->res, codes[1]->res);
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

Tac* generateIfElseCode(Tac* condition, Tac* ifCode, Tac* elseCode) {
    Symbol* elseLabel = makeLabel();
    Symbol* endLabel = makeLabel();
    
    Tac* elseLabelTac = new Tac(TacType::LABEL, elseLabel);
    Tac* endLabelTac = new Tac(TacType::LABEL, endLabel);
    
    Tac* ifzTac = new Tac(TacType::IFZ, elseLabel, condition->res);
    Tac* jumpEndTac = new Tac(TacType::JUMP, endLabel);

    return joinTacs(condition,
            joinTacs(ifzTac,
            joinTacs(ifCode,
            joinTacs(jumpEndTac,
            joinTacs(elseLabelTac,
            joinTacs(elseCode, endLabelTac))))));
}

Tac* generateWhileDoCode(Tac* condition, Tac* code) {
    Symbol* startLabel = makeLabel();
    Symbol* endLabel = makeLabel();

    Tac* startLabelTac = new Tac(TacType::LABEL, startLabel);
    Tac* endLabelTac = new Tac(TacType::LABEL, endLabel);
    
    Tac* ifzTac = new Tac(TacType::IFZ, endLabel, condition->res);
    Tac* jumpStartTac = new Tac(TacType::JUMP, startLabel);

    return joinTacs(startLabelTac,
            joinTacs(condition,
            joinTacs(ifzTac,
            joinTacs(code,
            joinTacs(jumpStartTac, endLabelTac)))));
}

Tac* generateDoWhileCode(Tac* condition, Tac* code) {
    Symbol* startLabel = makeLabel();
    Symbol* endLabel = makeLabel();

    Tac* startLabelTac = new Tac(TacType::LABEL, startLabel);
    Tac* endLabelTac = new Tac(TacType::LABEL, endLabel);

    Tac* ifzTac = new Tac(TacType::IFZ, endLabel, condition->res);
    Tac* jumpStartTac = new Tac(TacType::JUMP, startLabel);

    return joinTacs(startLabelTac,
            joinTacs(code,
            joinTacs(condition,
            joinTacs(ifzTac,
            joinTacs(jumpStartTac, endLabelTac)))));
}

Tac* generateFuncCallCode(Tac* args, Symbol* funcName) {
    Tac* funcCallTac = new Tac(TacType::FUNC_CALL, makeSymbol(), funcName);

    AstNode* funcDecl = functionDeclarations[funcName];
    AstNode* paramList = funcDecl->children[1];

    if (paramList) {
        size_t currArgIndex = paramList->children.size();

        Tac* currArg = args;
        while (currArg && currArgIndex > 0) {
            if (currArg->type == TacType::ARG) {
                currArgIndex--;
                currArg->op1 = funcName;
                currArg->op2 = paramList->children[currArgIndex]->symbol;
            }
            currArg = currArg->prev;
        }
    }

    return joinTacs(args, funcCallTac);
}