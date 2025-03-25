%{
    #include "tokens.h"

    int lineNumber = 1;
    int running = 1;
%}

%x STRING
%x COMMENT
%x MULTI_LINE_COMMENT

DIGIT  [0-9]+

%%

"byte"                      { return KW_BYTE;       }
"int"                       { return KW_INT;        }
"real"                      { return KW_REAL;       }

"if"                        { return KW_IF;         }
"else"                      { return KW_ELSE; }
"do"                        { return KW_DO; }
"while"                     { return KW_WHILE; }
"read"                      { return KW_READ; }
"print"                     { return KW_PRINT; }
"return"                    { return KW_RETURN; }

[-,;:()[\]{}=+*/%<>&|~]     { return yytext[0]; }
"<="                        { return OPERATOR_LE; }
">="                        { return OPERATOR_GE; }
"=="                        { return OPERATOR_EQ; }
"!="                        { return OPERATOR_DIF; }

[a-zA-Z_][a-zA-Z0-9_]*      { return TK_IDENTIFIER; }

{DIGIT}+\/{DIGIT}+          { return LIT_REAL; }
{DIGIT}+                    { return LIT_INT; }
'[^'\n\t]'                  { return LIT_CHAR; }
\"(\\.|[^\\"])*\"           { return LIT_STRING; }

[ \t\r]+
\n                          { lineNumber++; }


"//".*

"/--"                       { BEGIN(MULTI_LINE_COMMENT); }
<MULTI_LINE_COMMENT>\n      { lineNumber++; }
<MULTI_LINE_COMMENT>.
<MULTI_LINE_COMMENT>"--/"   { BEGIN(INITIAL); }

.                           { return TOKEN_ERROR; }

%%

void initMe(void) {}

int yywrap(void) {
    running = 0;
    return 1;
}

int isRunning(void) {
    return running;
}

int getLineNumber(void) {
    return lineNumber;
}