/*
20/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <stdio.h>

#include "ast.hpp"
#include "lex.yy.h"
#include "symbols.hpp"

extern int yyparse(void);
extern int isRunning(void);
extern int getLineNumber(void);

extern AstNode* astRoot;

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Error: input/output file missing. Run '%s <input_file> <output_file>'\n", argv[0]);
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("Error: could not open input file '%s'\n", argv[1]);
        exit(1);
    }

    FILE* output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Error: could not open output file '%s'\n", argv[2]);
        fclose(yyin);
        exit(1);
    }

    yyparse();

    // printAst(astRoot);
    std::string ast = decompileAstNode(astRoot);
    fprintf(output, "%s", ast.c_str());

    fclose(yyin);
    fclose(output);

    exit(0);
}