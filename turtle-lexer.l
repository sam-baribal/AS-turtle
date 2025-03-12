%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
EXP [eE][+-]?({DIGIT}+)
DEC "."{DIGIT}*
COMM  #.*\n

%%

"print"               { return KW_PRINT; }
"up"                  { return KW_UP; }
"down"                { return KW_DOWN; }
"forward"|"fw"        { return KW_FORWARD; }
"backward"|"bw"       { return KW_BACKWARD; }
"position"|"pos"      { return KW_POSITION; }
"right"|"rt"          { return KW_RIGHT; }
"left"|"lt"           { return KW_LEFT; }
"heading"|"hd"        { return KW_HEADING; }
"color"               { return KW_COLOR; }
"home"                { return KW_HOME; }

"red"       { return COLOR_RED; }
"green"     { return COLOR_GREEN; }
"blue"      { return COLOR_BLUE; }
"cyan"      { return COLOR_CYAN; }
"magenta"   { return COLOR_MAGENTA; }
"yellow"    { return COLOR_YELLOW; }
"black"     { return COLOR_BLACK; }
"gray"      { return COLOR_GRAY; }
"white"     { return COLOR_WHITE; }

"+"           { return '+'; }
"-"           { return '-'; }
"*"           { return '*'; }
"/"           { return '/'; }
"("           { return '('; }
")"           { return ')'; }
"{"           { return '{'; }
"}"           { return '}'; }
"^"           { return '^'; }

{DIGIT}+{DEC}?{EXP}?            { yylval.value = strtod(yytext, NULL); return VALUE; }
{COMM}                          { return '\n'; }

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
