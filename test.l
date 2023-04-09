%{
    #include "test_translator.h"
    #include "y.tab.h"
%}

%%

"SELECT"                      { return SELECT;                             }
[a-zA-Z0-9][a-zA-Z0-9\.]*     { yylval.str=strdup(yytext); return WORD;    }
"&"                           { return AND;                                }
"|"                           { return OR;                                 }
"["                           { return LSQ;                                }
"]"                           { return RSQ;                                }
"("                           { return LPAR;                               }
")"                           { return RPAR;                               }
[ \n\t]                       {                                            }

%%

int yywrap()
{
    return 1;
}