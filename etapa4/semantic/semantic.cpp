/*
01/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <map>
#include <set>
#include "../ast.hpp"
#include "../symbols.hpp"
#include "error_reporter.hpp"
#include "datatype.hpp"
#include "semantic.hpp"

using namespace std;

map<Symbol*, AstNode*> functionDeclarations;

static const map<AstNodeType, SymbolType> declarationTypeMap = {
    {AstNodeType::VAR_DECL, SymbolType::VARIABLE},
    {AstNodeType::ARRAY_DECL, SymbolType::ARRAY},
    {AstNodeType::FUNC_DECL, SymbolType::FUNCTION},
};

static const map<AstNodeType, DataType> dataTypeMap = {
    {AstNodeType::INT, DataType::INT},
    {AstNodeType::BYTE, DataType::BYTE},
    {AstNodeType::REAL, DataType::REAL},
};

void runSemanticAnalysis(AstNode* root) {
    for (AstNode* decl : root->children) {
        checkDeclarations(decl);
    }

    checkUndeclared();
    checkIdentifierUsage(root);
}

void checkArrayDeclaration(AstNode* arrayDecl, Symbol* symbol) {
    int arraySize = stoi(arrayDecl->symbol->text);
    if (arraySize <= 0) {
        errorReporter.report("Array size must be greater than 0");
    }

    AstNode* arrayInit = arrayDecl->children.size() > 1 ? arrayDecl->children[1] : nullptr;
    if (!arrayInit) return;

    for (auto* item : arrayInit->children) {
        if (!isCompatible(symbol->dataType, item->symbol->dataType)) {
            errorReporter.report("Incompatible types for array " + symbol->text);
        }
        continue;
    }
}

void checkDeclarations(AstNode* decl) {
    AstNode* identifierNode = decl->children[0];
    Symbol* symbol = identifierNode->symbol;

    if (symbol->type != SymbolType::IDENTIFIER) {
        errorReporter.report("Variable " + symbol->text + " redeclared");
        return;
    }

    symbol->type = declarationTypeMap.at(decl->type);
    symbol->dataType = dataTypeMap.at(identifierNode->children[0]->type);

    switch (decl->type) {
        case AstNodeType::VAR_DECL:
            if (!isCompatible(symbol->dataType, decl->children[1]->symbol->dataType)) {
                errorReporter.report("Incompatible types for variable " + symbol->text);
            }
            break;
        case AstNodeType::ARRAY_DECL:
            checkArrayDeclaration(decl, symbol);
            break;
        case AstNodeType::FUNC_DECL:{
            functionDeclarations[symbol] = decl;

            AstNode* paramList = decl->children[1];

            if (paramList) {
                for (auto* param : paramList->children) {
                    if (param->symbol->type != SymbolType::IDENTIFIER) {
                        errorReporter.report("Variable " + param->symbol->text + " redeclared");
                        return;
                    }

                    param->symbol->type = SymbolType::VARIABLE;
                    param->symbol->dataType = dataTypeMap.at(param->children[0]->type);
                }
            }
        }
        default:
            break;
    }
}

void checkUndeclared() {
    for (const auto& entry : symbolTable) {
        if (entry.second->type == SymbolType::IDENTIFIER) {
            errorReporter.report("Undeclared variable " + entry.first);
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
                errorReporter.report(sym->text + " cannot be used as a scalar variable");

            break;
        }

        case AstNodeType::SYMBOL: {
            Symbol* sym = node->symbol;

            if (!isLiteral(sym->type) && sym->type != SymbolType::VARIABLE)
                errorReporter.report(sym->text + " cannot be used as a scalar variable");

            break;
        }

        case AstNodeType::ARRAY_ELEM: {
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::ARRAY)
                errorReporter.report(sym->text + " cannot be used as an array");

            break;
        }

        case AstNodeType::FUNC_CALL: {
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::FUNCTION) {
                errorReporter.report(sym->text + " cannot be used as a function");
                break;
            }

            AstNode* funcDecl = functionDeclarations[sym];

            AstNode* paramList = funcDecl->children[1];
            AstNode* argList = node->children[0];

            if (paramList->children.size() != argList->children.size()) {
                errorReporter.report("Function " + sym->text + " called with wrong number of arguments");
            } else {
                // TODO: checar se os tipos dos argumentos são compatíveis com os tipos dos parâmetros
                // for (size_t i = 0; i < paramList->children.size(); ++i) {
                //     Symbol* paramSym = paramList->children[i]->symbol;
                //     fprintf(stderr, "paramSym: %s\n", paramSym->text.c_str());

                //     // AstNode* identifierNode = decl->children[0];
                //     // Symbol* symbol = identifierNode->symbol;

                //     Symbol* argSym = argList->children[i]->symbol;

                //     if (!isCompatible(paramSym->dataType, argSym->dataType)) {
                //         errorReporter.report("Incompatible types for function " + sym->text);
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