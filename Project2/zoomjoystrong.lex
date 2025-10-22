%{
#include "calc.tab.h"   /* Contains token definitions from Bison */
#include <stdio.h>
#include <stdlib.h>
%}

/* Regular expressions */
DIGIT   [0-9]
LETTER  [a-zA-Z]

%%

/* commands */
"end" {return END;}
";"   {return END_STATEMENT;}
"point" {return POINT;}
"line"  {return LINE;}
"circle" { return CIRCLE;}
"rectangle" { return RECTANGLE;}
"set_color" {return SET_COLOR;}

/* numbers */
{DIGIT}+ { yylval.ival = atoi(yytext); return INT; }
{DIGIT}+"."{DIGIT}+ { yylval.fval = atof(yytext); return FLOAT; }

/* Variables */
"\$"{LETTER} { yylval.var = yytext[1]; return VARIABLE;}

/* operators */
"=" {return EQUALS;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULT;}
"/" {return DIV;}

/* ignore white space */
[ \t\n]+ ;

/* unknown characters */
. {printf("Unknown: %s\n",yytext);}

%%

int yywrap() { return 1; }
