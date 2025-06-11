/*
20/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <stdio.h>

#include "asm.hpp"
#include "ast.hpp"
#include "lex.yy.h"
#include "semantic.hpp"
#include "symbols.hpp"
#include "tac.hpp"

extern int yyparse(void);
extern int isRunning(void);
extern int getLineNumber(void);

extern AstNode* astRoot;

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Error: input file missing. Run '%s <input_file>'\n", argv[0]);
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("Error: could not open input file '%s'\n", argv[1]);
        exit(2);
    }

    yyparse();
    fclose(yyin);

    runSemanticAnalysis(astRoot);

    if (hasSematicErrors()) exit(4);
    
    Tac* tacList = generateCode(astRoot);
    tacList = invertTacList(tacList);

    FILE* output = fopen("out.s", "w");
    if (output == NULL) {
        printf("Error: could not open output file.\n");
        exit(1);
    }
    
    std::string assembly = generateAsm(tacList);
    fprintf(stderr, "%s", assembly.c_str());

    fclose(output);

    exit(0);
}