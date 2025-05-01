/*
01/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <map>
#include "ast.hpp"
#include "semantic.hpp"
#include "symbols.hpp"

using namespace std;

static const map<AstNodeType, SymbolType> declarationTypeMap = {
    {AstNodeType::VAR_DECL, SymbolType::VARIABLE},
    {AstNodeType::ARRAY_DECL, SymbolType::ARRAY},
    {AstNodeType::FUNC_DECL, SymbolType::FUNCTION},
};

static const map<AstNodeType, SymbolDataType> dataTypeMap = {
    {AstNodeType::INT, SymbolDataType::INT},
    {AstNodeType::BYTE, SymbolDataType::INT},  // TODO: change to BYTE if needed
    {AstNodeType::REAL, SymbolDataType::REAL},
};

void runSemanticAnalysis(AstNode* node) {
    checkDeclarations(node);
}

void checkDeclarations(AstNode* declList) {
    for (AstNode* decl : declList->children) {
        AstNode* identifierNode = decl->children[0];
        Symbol* symbol = identifierNode->symbol;

        if (symbol->type != SymbolType::IDENTIFIER) {
            fprintf(stderr, "Semantic error: variable %s redeclared\n", symbol->text.c_str());
            continue;
        }

        symbol->type = declarationTypeMap.at(decl->type);
        symbol->dataType = dataTypeMap.at(identifierNode->children[0]->type);

        if (decl->type == AstNodeType::ARRAY_DECL) {
            int arraySize = stoi(decl->symbol->text);
            if (arraySize <= 0) {
                fprintf(stderr, "Semantic error: array size must be greater than 0\n");
            }

            AstNode* arrayInitNode = decl->children.size() > 1 ? decl->children[1] : nullptr;
            if (!arrayInitNode) continue;

            // TODO: Check if array values are compatible with the array type
            for (auto* child : arrayInitNode->children) {
                fprintf(stderr, "Child: %s\n", child->symbol->text.c_str());
            }
        }
    }
}

void checkUndeclared(AstNode* node) {
}