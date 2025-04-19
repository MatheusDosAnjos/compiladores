/*
15/04/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include "symbols.hpp"
#include "ast.hpp"

using namespace std;

string joinChildren(const vector<AstNode*>& children, const string& separator);
string joinBinaryOp(const vector<AstNode*>& children, const string& op);

const char* astNodeTypeLabel[] = {
    "DECL_LIST", "VAR_DECL", "ARRAY_DECL", "ARRAY_INIT", "FUNC_DECL", "PARAM_LIST",
    "VAR_DEF", "SYMBOL", "BYTE", "INT", "REAL",
    "CMD_BLOCK", "CMD_LIST","ASSIGN", "ASSIGN_ARRAY_ELEM",
    "ARRAY_ELEM", "IF", "IF_ELSE", "WHILE_DO", "DO_WHILE", "READ", "PRINT", "RETURN",
    "ADD", "SUB", "MULT", "DIV", "LESS", "GREATER", "AND", "OR", "LE", "GE", "EQ", "DIF", "NOT",
    "FUNC_CALL", "ARG_LIST"
};

void printAst(AstNode* node, int level) {
    if (!node) return;

    for (int i = 0; i < level; i++) {
        fprintf(stderr, "  ");
    }
    
    fprintf(stderr, "%s", astNodeTypeLabel[static_cast<int>(node->type)]);

    if (node->symbol)
        fprintf(stderr, ": %s", node->symbol->text.c_str());

    fprintf(stderr, "\n");

    for (AstNode* child : node->children) {
        printAst(child, level + 1);
    }
}

string decompileAstNode(AstNode* node) {
    if (!node) return "";

    ostringstream result;

    switch (node->type) {
        case AstNodeType::DECL_LIST:
            for (AstNode* child : node->children) {
                result << decompileAstNode(child) << "\n";
            }
            break;

        case AstNodeType::VAR_DECL:
            result << decompileAstNode(node->children[0]) << " = " << decompileAstNode(node->children[1]) << ";";
            break;

        case AstNodeType::ARRAY_DECL:
            result << decompileAstNode(node->children[0]) << "[" << node->symbol->text << "]";
            if (node->children.size() > 1) {
                result << " = " << decompileAstNode(node->children[1]);
            }
            result << ";";
            break;

        case AstNodeType::ARRAY_INIT:
        case AstNodeType::PARAM_LIST:
        case AstNodeType::ARG_LIST:
            result << joinChildren(node->children, ", ");
            break;

        case AstNodeType::FUNC_DECL:
            result << decompileAstNode(node->children[0]) << "(" << 
                decompileAstNode(node->children[1]) << ") " << decompileAstNode(node->children[2]);
            break;

        case AstNodeType::VAR_DEF:
            result << decompileAstNode(node->children[0]) << " " << node->symbol->text;
            break;

        case AstNodeType::SYMBOL:
            result << node->symbol->text;
            break;

        case AstNodeType::BYTE:
            result << "byte";
            break;

        case AstNodeType::INT:
            result << "int";
            break;

        case AstNodeType::REAL:
            result << "real";
            break;

        case AstNodeType::CMD_BLOCK:
            result << "{\n" << decompileAstNode(node->children[0]) << "}";
            break;

        case AstNodeType::CMD_LIST:
            for (AstNode* child : node->children) {
                result << decompileAstNode(child) << "\n";
            }
            break;

        case AstNodeType::ASSIGN:
            result << node->symbol->text << " = " << decompileAstNode(node->children[0]) << ";";
            break;

        case AstNodeType::ASSIGN_ARRAY_ELEM:
            result << decompileAstNode(node->children[0]) << " = " << decompileAstNode(node->children[1]) << ";";
            break;

        case AstNodeType::ARRAY_ELEM:
            result << node->symbol->text << "[" << decompileAstNode(node->children[0]) << "]";
            break;

        case AstNodeType::IF:
            result << "if (" << decompileAstNode(node->children[0]) << ") " << decompileAstNode(node->children[1]);
            break;

        case AstNodeType::IF_ELSE:
            result << "if (" << decompileAstNode(node->children[0]) << ") " << decompileAstNode(node->children[1]) <<
                    " else " << decompileAstNode(node->children[2]);
            break;

        case AstNodeType::WHILE_DO:
            result << "while " << decompileAstNode(node->children[0]) << " do\n" << decompileAstNode(node->children[1]);
            break;

        case AstNodeType::DO_WHILE:
            result << "do " << decompileAstNode(node->children[0]) << " while " << decompileAstNode(node->children[1]) << ";";
            break;

        case AstNodeType::READ:
            result << "read " << node->symbol->text << ";";
            break;

        case AstNodeType::PRINT:
            result << "print " << joinChildren(node->children, " ") << ";";
            break;

        case AstNodeType::RETURN:
            result << "return " << decompileAstNode(node->children[0]) << ";";
            break;

        case AstNodeType::FUNC_CALL:
            result << node->symbol->text << "(" << decompileAstNode(node->children[0]) << ")";
            break;

        case AstNodeType::ADD:      result << joinBinaryOp(node->children, "+"); break;
        case AstNodeType::SUB:      result << joinBinaryOp(node->children, "-"); break;
        case AstNodeType::MULT:     result << joinBinaryOp(node->children, "*"); break;
        case AstNodeType::DIV:      result << joinBinaryOp(node->children, "/"); break;
        case AstNodeType::LESS:     result << joinBinaryOp(node->children, "<"); break;
        case AstNodeType::GREATER:  result << joinBinaryOp(node->children, ">"); break;
        case AstNodeType::LE:       result << joinBinaryOp(node->children, "<="); break;
        case AstNodeType::GE:       result << joinBinaryOp(node->children, ">="); break;
        case AstNodeType::EQ:       result << joinBinaryOp(node->children, "=="); break;
        case AstNodeType::DIF:      result << joinBinaryOp(node->children, "!="); break;
        case AstNodeType::AND:      result << joinBinaryOp(node->children, "&"); break;
        case AstNodeType::OR:       result << joinBinaryOp(node->children, "|"); break;

        case AstNodeType::NOT:
            result << "~" << decompileAstNode(node->children[0]);
            break;

        default:
            result << "/* UNKNOWN NODE TYPE */";
            break;
    }

    return result.str();
}

string joinChildren(const vector<AstNode*>& children, const string& separator) {
    stringstream ss;

    for (size_t i = 0; i < children.size(); ++i) {
        ss << decompileAstNode(children[i]);
        if (i < children.size() - 1) ss << separator;
    }

    return ss.str();
}

string joinBinaryOp(const vector<AstNode*>& children, const string& op) {
    return "(" + decompileAstNode(children[0]) + " " + op + " " + decompileAstNode(children[1]) + ")";
}