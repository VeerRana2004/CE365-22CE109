%option noyywrap
%{
#include <stdio.h>
%}

%%
charusat       { printf("university"); }
CHARUSAT       { printf("UNIVERSITY"); }
[Cc]harusat    { printf("University"); }
.|\n           { printf("%s", yytext); }
%%

int main() {
    printf("Please enter a character string, and press Enter:\n");
    yylex();
    return 0;
}
