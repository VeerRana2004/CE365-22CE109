%option noyywrap
%{
#include <stdio.h>
%}

%%
[0-9]+    { printf("%s\n", yytext); }
.|\n      { ; /* Ignore other characters */ }
%%

int main() {
    printf("Please enter a character string (mix of text and numbers), and press Enter:\n");
    yylex();
    return 0;
}
