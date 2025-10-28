%{
#include <stdio.h>
#include <stdlib.h>

// declaration from flex file
int yylex(void);
void yyerror(const char *s);
%}


%union {
    int ival; //int
    float fval; //floating point
    char var; //variable names
}

%token END POINT LINE CIRCLE RECTANGLE SET_COLOR
%token END_STATEMENT
%token EQUALS PLUS MINUS MULT DIV
%token <ival> INT
%token <fval> FLOAT
%token <var> VARIABLE

%type<fval> expression

%%

statements:
/* no statement yet */
          | statements statement

;

statement:
         POINT expression expression END_STATEMENT
         {
            printf("drawing point at (%.2f, %.2f)\n", $2, $3);
         }
         |LINE
         |CIRCLE
         |rectangle
         |set_color
;

expression;
    INT {$5 = (float) $1;}
    |FLOAT {$$ = $1;}
    |VARIABLE {$$ = 0;}
    |expression PLUS expression ($$ = $1 + $3}
    |MINUS
    |MULT
    |DIV

;

%%

//error function and main function

void yyerror(const char *s)
{
    fprintf(stderr, "Error: %s\n", s);
}

int main(void)
{
    printf("Welcome")
    printf("Enter commands")
    printf("POINT 100 200 , LINE") // not proper, we have to
    yyparse();
    return 0;
}




