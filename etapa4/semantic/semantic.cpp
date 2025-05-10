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

    if (arraySize == 0) {
        errorReporter.report(ErrorType::INVALID_ARRAY_SIZE_1, {symbol->text});
        return;
    }

    AstNode* arrayInit = arrayDecl->children.size() > 1 ? arrayDecl->children[1] : nullptr;

    if (!arrayInit) return;

    if (arrayInit->children.size() != static_cast<size_t>(arraySize)) {
        errorReporter.report(ErrorType::INVALID_ARRAY_SIZE_2, {symbol->text});
        return;
    }

    for (auto* item : arrayInit->children) {
        DataType itemDataType = item->symbol->dataType;

        if (!isCompatible(symbol->dataType, itemDataType)) {
            errorReporter.report(
                ErrorType::INCOMPATIBLE_INIT,
                {getDataTypeLabel(symbol->dataType), getDataTypeLabel(itemDataType), symbol->text}
            );        
        }
    }
}

void checkDeclarations(AstNode* decl) {
    AstNode* identifierNode = decl->children[0];
    Symbol* symbol = identifierNode->symbol;

    if (symbol->type != SymbolType::IDENTIFIER) {
        errorReporter.report(ErrorType::REDECLARED_VARIABLE, {symbol->text});
        return;
    }

    symbol->type = declarationTypeMap.at(decl->type);
    symbol->dataType = dataTypeMap.at(identifierNode->children[0]->type);

    switch (decl->type) {
        case AstNodeType::VAR_DECL: {
            DataType initDataType = decl->children[1]->symbol->dataType;

            if (!isCompatible(symbol->dataType, initDataType)) {
                errorReporter.report(
                    ErrorType::INCOMPATIBLE_INIT,
                    {getDataTypeLabel(symbol->dataType), getDataTypeLabel(initDataType), symbol->text}
                );
            }
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
                        errorReporter.report(ErrorType::REDECLARED_VARIABLE, {param->symbol->text});
                        continue;
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
            errorReporter.report(ErrorType::UNDECLARED_VARIABLE, {entry.first});
        }
    }
}

void checkIdentifierUsage(AstNode* node) {
    if (!node) return;

    switch (node->type) {
        case AstNodeType::ASSIGN: {
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::VARIABLE){
                errorReporter.report(ErrorType::INVALID_SCALAR_USAGE, {sym->text});
            }

            DataType exprDataType = inferType(node->children[0]);

            if (!isCompatible(sym->dataType, exprDataType)) {
                errorReporter.report(
                    ErrorType::INCOMPATIBLE_ASSIGN,
                    {getDataTypeLabel(sym->dataType), getDataTypeLabel(exprDataType), decompileAstNode(node)}
                );
            }

            break;
        }

        case AstNodeType::ASSIGN_ARRAY_ELEM: {
            Symbol* sym = node->children[0]->symbol;

            DataType exprDataType = inferType(node->children[1]);

            if (!isCompatible(sym->dataType, exprDataType)) {
                errorReporter.report(
                    ErrorType::INCOMPATIBLE_ASSIGN,
                    {getDataTypeLabel(sym->dataType), getDataTypeLabel(exprDataType), decompileAstNode(node)}
                );
            }

            break;
        }

        case AstNodeType::SYMBOL: {
            Symbol* sym = node->symbol;

            if (!isLiteral(sym->type) && sym->type != SymbolType::VARIABLE)
                errorReporter.report(ErrorType::INVALID_SCALAR_USAGE, {sym->text});

            break;
        }

        case AstNodeType::ARRAY_ELEM: {
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::ARRAY)
                errorReporter.report(ErrorType::INVALID_ARRAY_USAGE, {sym->text});

            break;
        }

        case AstNodeType::FUNC_CALL: {
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::FUNCTION) {
                errorReporter.report(ErrorType::INVALID_FUNCTION_USAGE, {sym->text});
                break;
            }

            AstNode* funcDecl = functionDeclarations[sym];

            AstNode* paramList = funcDecl->children[1];
            AstNode* argList = node->children[0];

            if (!paramList) break;

            if (!argList) {
                errorReporter.report(ErrorType::INVALID_FUNCTION_CALL_1, {sym->text});
                break;
            }

            if (paramList->children.size() != argList->children.size()) {
                errorReporter.report(ErrorType::INVALID_FUNCTION_CALL_1, {sym->text});
            } else {
                for (size_t i = 0; i < paramList->children.size(); ++i) {
                    DataType paramDataType = paramList->children[i]->symbol->dataType;
                    DataType argDataType = inferType(argList->children[i]);

                    if (!isCompatible(paramDataType, argDataType)) {
                        errorReporter.report(
                            ErrorType::INVALID_FUNCTION_CALL_2,
                            {getDataTypeLabel(paramDataType), getDataTypeLabel(argDataType), sym->text}
                        );
                    }
                }
            }
        }

        default:
            break;
        }

    for (auto c : node->children){
        checkIdentifierUsage(c);
    }
}

DataType inferType(AstNode* node) {
    if (!node) return DataType::NONE;

    switch (node->type) {
        case AstNodeType::SYMBOL:
        case AstNodeType::ARRAY_ELEM:
        case AstNodeType::FUNC_CALL:
            return node->symbol->dataType;
            break;

        case AstNodeType::ADD:
        case AstNodeType::SUB:
        case AstNodeType::MULT:
        case AstNodeType::DIV: {
            DataType left = inferType(node->children[0]);
            DataType right = inferType(node->children[1]);

            if (isArithmeticOperation(left, right)) {
                node->dataType = left;
            } else {
                errorReporter.report(ErrorType::INVALID_ARITHMETIC_EXPR, {decompileAstNode(node)});
            }
            break;
        }

        case AstNodeType::LESS:
        case AstNodeType::GREATER:
        case AstNodeType::LE:
        case AstNodeType::GE:
        case AstNodeType::EQ:
        case AstNodeType::DIF: {
            DataType left = inferType(node->children[0]);
            DataType right = inferType(node->children[1]);

            if (isArithmeticOperation(left, right)) {
                node->dataType = DataType::BOOL;
            } else {
                errorReporter.report(ErrorType::INVALID_RELATIONAL_EXPR, {decompileAstNode(node)});
            }
            break;
        }

        case AstNodeType::AND:
        case AstNodeType::OR: {
            DataType left = inferType(node->children[0]);
            DataType right = inferType(node->children[1]);

            if (left == DataType::BOOL && right == DataType::BOOL) {
                node->dataType = DataType::BOOL;
            } else {
                errorReporter.report(ErrorType::INVALID_LOGICAL_EXPR, {decompileAstNode(node)});
            }
            break;
        }

        case AstNodeType::NOT: {
            DataType child = inferType(node->children[0]);

            if (child == DataType::BOOL) {
                node->dataType = DataType::BOOL;
            } else {
                errorReporter.report(ErrorType::INVALID_LOGICAL_EXPR, {decompileAstNode(node)});
            }
            break;
        }

        default:
            for (auto child : node->children) inferType(child);
            return DataType::NONE;
    }

    return node->dataType;
}
