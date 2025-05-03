/*
01/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <map>
#include <set>
#include "ast.hpp"
#include "semantic.hpp"
#include "symbols.hpp"

using namespace std;

extern map<string, Symbol*> symbolTable;

map<Symbol*, AstNode*> functionDeclarations;

static const map<AstNodeType, SymbolType> declarationTypeMap = {
    {AstNodeType::VAR_DECL, SymbolType::VARIABLE},
    {AstNodeType::ARRAY_DECL, SymbolType::ARRAY},
    {AstNodeType::FUNC_DECL, SymbolType::FUNCTION},
};

static const map<AstNodeType, SymbolDataType> dataTypeMap = {
    {AstNodeType::INT, SymbolDataType::INT},
    {AstNodeType::BYTE, SymbolDataType::BYTE},
    {AstNodeType::REAL, SymbolDataType::REAL},
};

static const set<pair<SymbolDataType, SymbolDataType>> compatibleDataTypes = {
    {SymbolDataType::INT,  SymbolDataType::INT},
    {SymbolDataType::INT,  SymbolDataType::CHAR},
    {SymbolDataType::REAL, SymbolDataType::REAL},
    {SymbolDataType::BYTE, SymbolDataType::INT},
    {SymbolDataType::BYTE, SymbolDataType::CHAR},
};

constexpr bool isLiteral(SymbolType type) noexcept {
    return type == SymbolType::INT || 
           type == SymbolType::CHAR || 
           type == SymbolType::REAL || 
           type == SymbolType::STRING;
}

static void error(const std::string &msg) {
    fprintf(stderr, "\033[0;31mERROR:\033[0m %s\n", msg.c_str());
}

bool areTypesCompatible(SymbolDataType from, SymbolDataType to) {
    return compatibleDataTypes.count({from, to}) > 0;
}

void runSemanticAnalysis(AstNode* node) {
    checkDeclarations(node);
    // checkUndeclared();
    // checkIdentifierUsage(node);
}

void checkArrayDeclaration(AstNode* arrayDecl, Symbol* symbol) {
    int arraySize = stoi(arrayDecl->symbol->text);
    if (arraySize <= 0) {
        error("Array size must be greater than 0");
    }

    AstNode* arrayInit = arrayDecl->children.size() > 1 ? arrayDecl->children[1] : nullptr;
    if (!arrayInit) return;

    for (auto* item : arrayInit->children) {
        if (!areTypesCompatible(symbol->dataType, item->symbol->dataType)) {
            error("Incompatible types for array " + symbol->text);
        }
        continue;
    }
}

void checkDeclarations(AstNode* declList) {
    for (AstNode* decl : declList->children) {
        AstNode* identifierNode = decl->children[0];
        Symbol* symbol = identifierNode->symbol;

        if (symbol->type != SymbolType::IDENTIFIER) {
            error("Variable " + symbol->text + " redeclared");
            continue;
        }

        symbol->type = declarationTypeMap.at(decl->type);
        symbol->dataType = dataTypeMap.at(identifierNode->children[0]->type);

        switch (decl->type) {
            case AstNodeType::VAR_DECL:
                if (!areTypesCompatible(symbol->dataType, decl->children[1]->symbol->dataType)) {
                    error("Incompatible types for variable " + symbol->text);
                }
                break;
            case AstNodeType::ARRAY_DECL:
                checkArrayDeclaration(decl, symbol);
                break;
            case AstNodeType::FUNC_DECL:
                functionDeclarations[symbol] = decl;
                // TODO: declarar parametroes da função
            default:
                break;
        }
    }
}

void checkUndeclared() {
    for (const auto& entry : symbolTable) {
        if (entry.second->type == SymbolType::IDENTIFIER) {
            error("Undeclared variable " + entry.first);
        }
    }
}

void checkIdentifierUsage(AstNode* node) {
    if (!node) return;

    switch (node->type) {
        case AstNodeType::ASSIGN: {
            // TODO: checar se o tipo sendo assigned é compatível com o tipo da variável
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::VARIABLE)
                error(sym->text + " cannot be used as a scalar variable");

            break;
        }

        case AstNodeType::SYMBOL: {
            Symbol* sym = node->symbol;

            if (!isLiteral(sym->type) && sym->type != SymbolType::VARIABLE)
                error(sym->text + " cannot be used as a scalar variable");

            break;
        }

        case AstNodeType::ARRAY_ELEM: {
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::ARRAY)
                error(sym->text + " cannot be used as an array");

            break;
        }

        case AstNodeType::FUNC_CALL: {
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::FUNCTION) {
                error(sym->text + " cannot be used as a function");
                break;
            }

            AstNode* funcDecl = functionDeclarations[sym];

            AstNode* paramList = funcDecl->children[1];
            AstNode* argList = node->children[0];

            if (paramList->children.size() != argList->children.size()) {
                error("Function " + sym->text + " called with wrong number of arguments");
            } else {
                // TODO: checar se os tipos dos argumentos são compatíveis com os tipos dos parâmetros
                // for (size_t i = 0; i < paramList->children.size(); ++i) {
                //     Symbol* paramSym = paramList->children[i]->symbol;
                //     fprintf(stderr, "paramSym: %s\n", paramSym->text.c_str());

                //     // AstNode* identifierNode = decl->children[0];
                //     // Symbol* symbol = identifierNode->symbol;

                //     Symbol* argSym = argList->children[i]->symbol;

                //     if (!areTypesCompatible(paramSym->dataType, argSym->dataType)) {
                //         error("Incompatible types for function " + sym->text);
                //     }
                // }
            }
        }

        default:
            break;
        }

    for (auto c : node->children)
        checkIdentifierUsage(c);
}