/*
20/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <stdio.h>

#include "ast.hpp"
#include "lex.yy.h"
#include "semantic.hpp"
#include "symbols.hpp"

extern int yyparse(void);
extern int isRunning(void);
extern int getLineNumber(void);

extern AstNode* astRoot;

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Error: input/output file missing. Run '%s <input_file>'\n", argv[0]);
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("Error: could not open input file '%s'\n", argv[1]);
        exit(1);
    }

    yyparse();

    runSemanticAnalysis(astRoot);

    fclose(yyin);

    exit(0);
}