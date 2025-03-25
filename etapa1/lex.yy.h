/*
20/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef LEX_YY_H
#define LEX_YY_H

#include <cstdio>

extern int yylex(void);
extern char* yytext;
extern FILE* yyin;

#endif