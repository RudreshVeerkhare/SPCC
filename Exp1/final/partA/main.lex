/* NAME : RUDRESH VEERKHARE             */
/* ROLL NO : 66                         */
/* BATCH : D                            */
/* usage : make TARGET={pascal filepath (default val is 'sample.pas')}    */

%{
#include <stdio.h>

int lineCount = 1; // for error line no. 
void yyerror(char *invalid_char, int lineNo);
%}

%%
and                  |
array                |
begin                |
case                 |
const                |
div                  |
do                   |
downto               |
else                 |
end                  |
file                 |
for                  |
function             |
goto                 |
if                   |
in                   |
label                |
mod                  |
nil                  |
not                  |
of                   |
packed               |
procedure            |
program              |
record               |
repeat               |
set                  |
then                 |
to                   |
type                 |
uses                 |  
until                |
var                  |
while                |
with                 printf("[%d] <keyword, %s >\n", lineCount, yytext); /* this are all pascal keywords */

\/\/(.*?)            |
\{(.*?)\}            |
\(\*(.*?)\*\)        printf("[%d] <comment, %s >\n", lineCount, yytext); /* ignore comments */

":="                 |
"+"                  |
"-"                  |
"*"                  |
"/"                  |
"%"                  |
"&"                  |
"|"|"!"              |
"<<"|">>"            | /* operators in pascal */
"~"                  printf("[%d] <operator, %s >\n", lineCount, yytext); 

"<="|"=<"            |
"=>"|">="            |
"<>"|"="             | /* logical operators */
"<"|">"              {printf("[%d] <logical operator, %s >\n", lineCount, yytext);} 

"{"|"}"              |
"("|")"              | /*didn't know what this are called so named it 'token'*/
";"|","|":"          printf("[%d] <token, %s >\n", lineCount, yytext); 

\'([^'\n]|\'\')+\'   printf("[%d] <literal, %s >\n", lineCount, yytext); /* string literal */
[0-9]+               printf("[%d] <number, %s >\n", lineCount, yytext); /* const numbers */
([A-Za-z]|[0-9])*    printf("[%d] <lexeme, %s >\n", lineCount, yytext); /* lexemes */


[ \t]*               /* skip blank spaces */
\n                   lineCount++; /* increment line no */
.                    {yyerror(yytext, lineCount);} /* if no pattern mathches throw error */
%%

void yyerror(char *invalid_char, int lineNo){
   fprintf(stderr,"Invalid token '%s' at line no: %d\n", yytext, lineCount);
   exit(1);
}

int yywrap(void){
	return 1;
} 

int main(int argc, char **argv){
    if(argc < 2){
        printf("NO file provided!!");
        return 1;
    }
    if(argc > 2){
        printf("Only 1 file expected!!");
        return 1;
    }
    yyin = fopen(argv[1],"r");
    yylex();
    return 0;
}