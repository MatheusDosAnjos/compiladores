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

void checkDeclarations(AstNode* node);
void checkIdentifierUsage(AstNode* node);
void checkUndeclared();
void checkCommand(AstNode* cmd, DataType returnDataType);
DataType inferDataType(AstNode* node);

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

bool runSemanticAnalysis(AstNode* root) {
    for (AstNode* decl : root->children) {
        checkDeclarations(decl);
    }

    checkUndeclared();
    checkIdentifierUsage(root);

    for (AstNode* decl : root->children) {
        if (decl->type != AstNodeType::FUNC_DECL) continue;

        checkCommand(decl->children[2], decl->children[0]->symbol->dataType);
    }

    return hasErrors();

}

void checkArrayDeclaration(AstNode* arrayDecl, Symbol* symbol) {
    int arraySize = stoi(arrayDecl->symbol->text);

    if (arraySize == 0) {
        reportError(ErrorType::INVALID_ARRAY_SIZE_1, {symbol->text});
        return;
    }

    AstNode* arrayInit = arrayDecl->children.size() > 1 ? arrayDecl->children[1] : nullptr;

    if (!arrayInit) return;

    if (arrayInit->children.size() != static_cast<size_t>(arraySize)) {
        reportError(ErrorType::INVALID_ARRAY_SIZE_2, {symbol->text});
        return;
    }

    for (auto* item : arrayInit->children) {
        DataType itemDataType = item->symbol->dataType;

        if (!isCompatible(symbol->dataType, itemDataType)) {
            reportError(
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
        reportError(ErrorType::REDECLARED_VARIABLE, {symbol->text});
        return;
    }

    symbol->type = declarationTypeMap.at(decl->type);
    symbol->dataType = dataTypeMap.at(identifierNode->children[0]->type);

    switch (decl->type) {
        case AstNodeType::VAR_DECL: {
            DataType initDataType = decl->children[1]->symbol->dataType;

            if (!isCompatible(symbol->dataType, initDataType)) {
                reportError(
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
                        reportError(ErrorType::REDECLARED_VARIABLE, {param->symbol->text});
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
            reportError(ErrorType::UNDECLARED_VARIABLE, {entry.first});
        }
    }
}

void checkIdentifierUsage(AstNode* node) {
    if (!node) return;

    switch (node->type) {
        case AstNodeType::ASSIGN: {
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::VARIABLE){
                reportError(ErrorType::INVALID_SCALAR_USAGE, {sym->text});
            }

            DataType exprDataType = inferDataType(node->children[0]);

            if (!isCompatible(sym->dataType, exprDataType)) {
                reportError(
                    ErrorType::INCOMPATIBLE_ASSIGN,
                    {getDataTypeLabel(sym->dataType), getDataTypeLabel(exprDataType), decompileAstNode(node)}
                );
            }

            break;
        }

        case AstNodeType::ASSIGN_ARRAY_ELEM: {
            Symbol* sym = node->children[0]->symbol;

            DataType exprDataType = inferDataType(node->children[1]);

            if (!isCompatible(sym->dataType, exprDataType)) {
                reportError(
                    ErrorType::INCOMPATIBLE_ASSIGN,
                    {getDataTypeLabel(sym->dataType), getDataTypeLabel(exprDataType), decompileAstNode(node)}
                );
            }

            break;
        }

        case AstNodeType::SYMBOL: {
            Symbol* sym = node->symbol;

            if (!isLiteral(sym->type) && sym->type != SymbolType::VARIABLE)
                reportError(ErrorType::INVALID_SCALAR_USAGE, {sym->text});

            break;
        }

        case AstNodeType::ARRAY_ELEM: {
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::ARRAY)
                reportError(ErrorType::INVALID_ARRAY_USAGE, {sym->text});

            break;
        }

        case AstNodeType::FUNC_CALL: {
            Symbol* sym = node->symbol;

            if (sym->type != SymbolType::FUNCTION) {
                reportError(ErrorType::INVALID_FUNCTION_USAGE, {sym->text});
                break;
            }

            AstNode* funcDecl = functionDeclarations[sym];

            AstNode* paramList = funcDecl->children[1];
            AstNode* argList = node->children[0];

            if (!paramList) break;

            if (!argList) {
                reportError(ErrorType::INVALID_FUNCTION_CALL_1, {sym->text});
                break;
            }

            if (paramList->children.size() != argList->children.size()) {
                reportError(ErrorType::INVALID_FUNCTION_CALL_1, {sym->text});
            } else {
                for (size_t i = 0; i < paramList->children.size(); ++i) {
                    DataType paramDataType = paramList->children[i]->symbol->dataType;
                    DataType argDataType = inferDataType(argList->children[i]);

                    if (!isCompatible(paramDataType, argDataType)) {
                        reportError(
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

void checkCommand(AstNode* cmd, DataType returnDataType) {
    if (!cmd) {
        fprintf(stderr, "Error: cmd is null\n");
        return;
    }

    switch (cmd->type) {
        case AstNodeType::IF:
        case AstNodeType::WHILE_DO:
            // TODO: Verificar com o prof, isso aqui é necessário? Acredito que sim
            if (inferDataType(cmd->children[0]) != DataType::BOOL) {
                reportError(ErrorType::INVALID_CONDITIONAL_EXPR, {decompileAstNode(cmd->children[0])});
            }

            checkCommand(cmd->children[1], returnDataType);
            break;
        case AstNodeType::IF_ELSE:
            if (inferDataType(cmd->children[0]) != DataType::BOOL) {
                reportError(ErrorType::INVALID_CONDITIONAL_EXPR, {decompileAstNode(cmd->children[0])});
            }

            checkCommand(cmd->children[1], returnDataType);
            checkCommand(cmd->children[2], returnDataType);
            break;
        case AstNodeType::DO_WHILE:
            if (inferDataType(cmd->children[1]) != DataType::BOOL) {
                reportError(ErrorType::INVALID_CONDITIONAL_EXPR, {decompileAstNode(cmd->children[1])});
            }

            checkCommand(cmd->children[0], returnDataType);
            break;
        case AstNodeType::READ:
            // TODO: Checar o que é válido aqui para o identificador (só escalar, só vetor, os dois)?
            break;
        case AstNodeType::PRINT:
            // TODO: Checar aqui o que é válido para as expressões (relacionais, lógicas, aritméticas, etc)
            break;
        case AstNodeType::RETURN: {
            DataType exprDataType = inferDataType(cmd->children[0]);

            if (!isCompatible(exprDataType, returnDataType)) {
                reportError(
                    ErrorType::INVALID_RETURN_TYPE,
                    {getDataTypeLabel(exprDataType), getDataTypeLabel(returnDataType)}
                );
            }
            break;
        }
        default:
            break;
    }
}

DataType inferDataType(AstNode* node) {
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
            DataType left = inferDataType(node->children[0]);
            DataType right = inferDataType(node->children[1]);

            if (isArithmeticOp(left, right)) {
                node->dataType = left;
            } else {
                reportError(ErrorType::INVALID_ARITHMETIC_EXPR, {decompileAstNode(node)});
            }
            break;
        }

        case AstNodeType::LESS:
        case AstNodeType::GREATER:
        case AstNodeType::LE:
        case AstNodeType::GE:
        case AstNodeType::EQ:
        case AstNodeType::DIF: {
            DataType left = inferDataType(node->children[0]);
            DataType right = inferDataType(node->children[1]);

            if (isArithmeticOp(left, right)) {
                node->dataType = DataType::BOOL;
            } else {
                reportError(ErrorType::INVALID_RELATIONAL_EXPR, {decompileAstNode(node)});
            }
            break;
        }

        case AstNodeType::AND:
        case AstNodeType::OR: {
            DataType left = inferDataType(node->children[0]);
            DataType right = inferDataType(node->children[1]);

            if (left == DataType::BOOL && right == DataType::BOOL) {
                node->dataType = DataType::BOOL;
            } else {
                reportError(ErrorType::INVALID_LOGICAL_EXPR, {decompileAstNode(node)});
            }
            break;
        }

        case AstNodeType::NOT: {
            DataType child = inferDataType(node->children[0]);

            if (child == DataType::BOOL) {
                node->dataType = DataType::BOOL;
            } else {
                reportError(ErrorType::INVALID_LOGICAL_EXPR, {decompileAstNode(node)});
            }
            break;
        }

        default:
            for (auto child : node->children) inferDataType(child);
            return DataType::NONE;
    }

    return node->dataType;
}