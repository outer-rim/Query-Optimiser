%{
    #include "test_translator.h"
    extern int yylex();
    void yyerror(char* s);
%}

%union 
{
    char* str;
    Node* node;
}

%token AND OR SELECT LSQ RSQ LPAR RPAR
%token <str> WORD

%start result

%type<node>
    expression
    table
    term

%%

result :
        | result table
        {
            printTable($2);
            parse($2);
        }
;

table : term
        { $$ = makeTree($1, NULL); }
        | SELECT LSQ expression RSQ LPAR table RPAR
        { $$ = makeTree($3, $6); }
;

expression: term
            { $$ = $1; }
            | expression AND term
            { $$ = makeAndNode($1, $3); }
;

term:   WORD
        { $$ = makeTermNode($1); }
;

%%

void yyerror(char* s)
{
    printf("Error Detected : %s\n", s);
}