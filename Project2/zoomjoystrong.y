%{
#include <stdio.h>
#include "zoomjoystrong.h"
#include <stdlib.h>

void yyerror(const char *s); // prints syntax errors
int yylex(void);             // lexer function from Flex
%}

// Define the union before any %token
%union {
    int ival;
    float fval;
    char var;
}

// Tokens
%token END END_STATEMENT
%token POINT LINE CIRCLE RECTANGLE SET_COLOR
%token <ival> INT // Integer literal token
%token <fval> FLOAT // Floating point literal token
%token <var> VARIABLE // Variable token (e.g., $a)
%token EQUALS PLUS MINUS MULT DIV

// Types
%type <ival> value  // The non-terminal 'value' must always result in an integer (ival)

%start program

%%

program:
    statement_list END
  | statement_list END END_STATEMENT
  | statement_list
;

statement_list:
    statement_list statement
  | statement
;

statement:
      POINT value value END_STATEMENT               { point($2, $3); }
    | LINE value value value value END_STATEMENT    { line($2, $3, $4, $5); }
    | CIRCLE value value value END_STATEMENT        { circle($2, $3, $4); }
    | RECTANGLE value value value value END_STATEMENT { rectangle($2, $3, $4, $5); }
    | SET_COLOR value value value END_STATEMENT     { set_color($2, $3, $4); }
;

value:
      INT   { $$ = $1; }
    | FLOAT { $$ = (int)$1; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    setup();
    yyparse();

    // loop for SDL
    SDL_Event event;
    int running = 1;
    while (running) {
        // Handle all pending events
        while (SDL_PollEvent(&event)) {
            // Check for window close event
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }

    finish();
    return 0;
}
