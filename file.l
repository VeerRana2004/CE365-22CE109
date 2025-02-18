%option noyywrap
%{
#include<stdio.h>
int v=0, c=0;
%}

%%
[aeiouAEIOU] {v++;}
[a-zA-Z] {c++;}
[ \t\n] ;
. ;
%%
int main()
{
char input[100];
printf("Enter string");
fgets(input, 100, stdin);
YY_BUFFER_STATE buffer = yy_scan_string(input);
yylex();
printf("vowels= %d",v);
printf("con= %d",c);
return 0;
}