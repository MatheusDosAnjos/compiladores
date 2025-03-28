/*
20/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <stdio.h>

#include "lex.yy.h"
#include "tokens.h"
#include "symbols.hpp"

extern int isRunning(void);
extern int getLineNumber(void);

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Error: input file missing. Run '%s <input_file>'\n", argv[0]);
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("Error: could not open file '%s'\n", argv[1]);
        exit(1);
    }

    while (isRunning()) {
        switch (yylex()) {
            case KW_BYTE:
                fprintf(stderr, "KW_BYTE ");
                break;
            case KW_INT:
                fprintf(stderr, "KW_INT ");
                break;
            case KW_REAL:
                fprintf(stderr, "KW_REAL ");
                break;
            case KW_IF:
                fprintf(stderr, "KW_IF ");
                break;
            case KW_ELSE:
                fprintf(stderr, "KW_ELSE ");
                break;
            case KW_DO:
                fprintf(stderr, "KW_DO ");
                break;
            case KW_WHILE:  
                fprintf(stderr, "KW_WHILE ");
                break;
            case KW_READ:
                fprintf(stderr, "KW_READ ");
                break;
            case KW_PRINT:
                fprintf(stderr, "KW_PRINT ");
                break;
            case KW_RETURN:
                fprintf(stderr, "KW_RETURN ");
                break;
            case OPERATOR_LE:
                fprintf(stderr, "OPERATOR_LE ");
                break;
            case OPERATOR_GE:
                fprintf(stderr, "OPERATOR_GE ");
                break;
            case OPERATOR_EQ:
                fprintf(stderr, "OPERATOR_EQ ");
                break;
            case OPERATOR_DIF:
                fprintf(stderr, "OPERATOR_DIF ");
                break;
            case TK_IDENTIFIER:
                fprintf(stderr, "TK_IDENTIFIER ");
                break;
            case LIT_INT:
                fprintf(stderr, "LIT_INT ");
                break;
            case LIT_CHAR:
                fprintf(stderr, "LIT_CHAR ");
                break;
            case LIT_REAL:
                fprintf(stderr, "LIT_REAL ");
                break;
            case LIT_STRING:
                fprintf(stderr, "LIT_STRING ");
                break;
            case TOKEN_ERROR:
                fprintf(stderr, "TOKEN_ERROR[%s] ", yytext);
                break;
            default:
                fprintf(stderr, "DEFAULT[%s]", yytext);
                break;
        }
    }

    fprintf(stderr, "Line number: %d lines\n", getLineNumber());
    printSymbolTable();
}