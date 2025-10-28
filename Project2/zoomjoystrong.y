%{
#include <stdio.h>  /* standard I/O functions */
#include "zoomjoystrong.h" /* drawing functions header */
#include <stdlib.h> /* general utilities */

void yyerror(const char *s); /* prints syntax errors */
int yylex(void); /* lexer function from Flex */

// Constants for color range validation
#define MAX_COLOR 255
#define MIN_COLOR 0
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
%}

/* define the union before tokens */
%union {
    int ival; /* integer values */
    float fval; /* float values */
    char var; /* variable name (e.g. $a) */
}

/* token definitions */
%token END END_STATEMENT /* end and semicolon tokens */
%token POINT LINE CIRCLE RECTANGLE SET_COLOR /* drawing commands */
%token <ival> INT /* integer literal token */
%token <fval> FLOAT /* floating-point literal token */
%token <var> VARIABLE /* variable token (e.g., $a) */
%token EQUALS PLUS MINUS MULT DIV /* arithmetic/assignment operators */

/* non-terminal type definitions */
%type <fval> value/* 'value' results in an float (fval) */

/* program entry point */
%start program

%%

program:
      statement_list END { /* program ending with END */ }
    | statement_list END END_STATEMENT { /* program ending with END; */ }
    | statement_list { /* program ending at EOF */ }
;

statement_list:
      statement_list statement { /* multiple statements */ }
    | statement { /* single statement */ }
;

statement:
     POINT value value END_STATEMENT { 
        int x = (int)$2;
        int y = (int)$3;
        if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT) {
            fprintf(stderr, "Error: Point (%d, %d) is outside screen boundaries (0-%d, 0-%d).\n", 
                x, y, SCREEN_WIDTH, SCREEN_HEIGHT);
                YYERROR; 
            } else {
            point(x, y);
        }
    }
    | LINE value value value value END_STATEMENT { line($2, $3, $4, $5); } {/* draw a line */}
    | CIRCLE value value value END_STATEMENT { circle($2, $3, $4); } {/* draw a circle */}
    | RECTANGLE value value value value END_STATEMENT { rectangle($2, $3, $4, $5); } {/* draw a rectangle */}
    | SET_COLOR value value value END_STATEMENT {
        int r = (int)$2;
        int g = (int)$3;
        int b = (int)$4;
        if (r < MIN_COLOR || r > MAX_COLOR || g < MIN_COLOR || g > MAX_COLOR || b < MIN_COLOR || b > MAX_COLOR) {
            fprintf(stderr, "Error: Color values (%d, %d, %d) must be in the range 0-255.\n", r, g, b);
            YYERROR; /* Triggers graceful error recovery */
            } else {
                set_color(r, g, b); 
        }
    }
;

value:
    INT { $$ = (float)$1;  /* Convert INT (ival) to float (fval) for $$ */ }
    | FLOAT { $$ = $1; /* FLOAT (fval) directly assigned to $$ (fval) */ }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s); {/* print syntax error */}
}

int main(void) {
    printf("Starting\n"); {/* start message */}
    setup();
    yyparse(); {/* parse input and draw */}
    finish();
    printf("Finished\n");   {/* end message */}

    return 0; {/* normal program exit */}
}
