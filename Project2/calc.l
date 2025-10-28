/* calc.l — Lexical analyzer for calculator */

%{
#include "calc.tab.h"   /* Contains token definitions from Bison */
#include <stdio.h>
#include <stdlib.h>
%}

/* Regular expressions */
DIGIT   [0-9]
NUMBER  {DIGIT}+(\.{DIGIT}+)?

%%

{NUMBER}    { yylval.fval = atof(yytext); return NUMBER; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULT; }
"/"         { return DIV; }
"("         { return LPAREN; }
")"         { return RPAREN; }
\n          { return EOL; }
[ \t]+      ;   /* Ignore whitespace */
.           { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() { return 1; }
