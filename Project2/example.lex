%{
#include "zoomjoystrong.tab.h"
#include <stdio.h>
#include <stdlib.h>

%}


%option noyywrap

%% // rules section

"end"   {return END;}
"POINT" | "point" {return POINT;}
"LINE"  | "line" {return LINE;}
"CIRCLE" | "circle {return CIRCLE;}
"RECTANGLE" | "rectangle" {return RECTANGLE;}
"SET_COLOR" | "set_color" {return SET_COLOR;}

";"         {return END_STATEMENT;}

[0-9] +\.[0-9]+ {yylval.fval = atof(yytext); return FLOAT;}
[0-9]+ {yylval.ival = atoi(yytext); return INT;}

\$[a-zA-Z] {yyval.var = yytext[1]; return VARIABLE}


//ignore whitespace
[ \t\n]+ {/*ignore white space*/}

// arithmetic and assignment

"=" {return EQUALS;}
"+" {return PLUS;}
-
*
/

. { [printf("unknown character: %s\n",)])}

%%




