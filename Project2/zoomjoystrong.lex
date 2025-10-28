%{
#include "zoomjoystrong.tab.h"   /* Contains token definitions from Bison */
#include <stdio.h>
#include <stdlib.h>
%}

/* Regular expressions */
DIGIT   [0-9]
LETTER  [a-zA-Z]

%%

"end" {return END;}
";"   {return END_STATEMENT;}
"point" {return POINT;}
"line"  {return LINE;}
"circle" { return CIRCLE;}
"rectangle" { return RECTANGLE;}
"set_color" {return SET_COLOR;}

{DIGIT}+ { yylval.ival = atoi(yytext); return INT; }
{DIGIT}+"."{DIGIT}+ { yylval.fval = atof(yytext); return FLOAT; }

"\$"{LETTER} { yylval.var = yytext[1]; return VARIABLE;}

"=" {return EQUALS;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULT;}
"/" {return DIV;}

[ \t\n]+ ;

. {printf("Unknown: %s\n",yytext);}

%%

int yywrap() { return 1; }