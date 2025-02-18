%option noyywrap
%{
#include <stdio.h>
#include <ctype.h>

int char_count = 0;
int word_count = 0;
int line_count = 0;
%}

%%
\n          { line_count++; char_count++; }
[ \t\n]+    { char_count += yyleng; }
[^ \t\n]+   { char_count += yyleng; word_count++; }
%%

int main(int argc, char **argv) {
    FILE *file;
    if (argc > 1) {
        file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
    }

    yylex();

    if (argc > 1) {
        fclose(file);
    }

    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);

    return 0;
}
