%{
#include "zoomjoystrong.tab.h" /* Contains token definitions from Bison */
#include <stdio.h>
#include <stdlib.h>
%}


%option noyywrap
%%

"end" { return END; } {/* return END token */}
";" { return END_STATEMENT; } {/* statement terminator */}
"point" { return POINT; } {/* point command */}
"line" { return LINE; } {/* line command */}
"circle" { return CIRCLE; } {/* circle command */}
"rectangle" { return RECTANGLE; } {/* rectangle command */}
"set_color" { return SET_COLOR; } {/* set_color command */}

[0-9]+ { yylval.ival = atoi(yytext); return INT; } {/* integer literal */}
[0-9]+"."[0-9]+ { yylval.fval = atof(yytext); return FLOAT; } {/* floating-point literal */}

"\$"[a-zA-Z] { yylval.var = yytext[1]; return VARIABLE; } {/* variable like $a */}

"=" { return EQUALS; } {/* equals operator */}
"+" { return PLUS; } {/* addition operator */}
"-" { return MINUS; } {/* subtraction operator */}
"*" { return MULT; } {/* multiplication operator */}
"/" { return DIV; } {/* division operator */}

[ \t\n]+ ; {/* ignore whitespace and newlines */}

. { printf("Unknown: %s\n", yytext); } {/* print unknown characters */}

%%

