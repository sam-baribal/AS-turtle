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
COMM  #.*
UPPER [A-Z]
NAME [A-Z0-9]

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
"repeat"              { return KW_REPEAT; }
"random"              { return KW_RANDOM; }
"{"                   { return KW_BLOCK_START; }
"}"                   { return KW_BLOCK_END; }
"("                   { return KW_PARAM_START; }
")"                   { return KW_PARAM_END; }
","                   { return KW_PARAM_SEP; }
"set"                 { return KW_SET; }
"proc"                { return KW_PROC; }
"call"                { return KW_CALL; }

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
"^"           { return '^'; }

{UPPER}{NAME}*                  { yylval.name = strdup(yytext); return NAME; }
{DIGIT}+{DEC}?{EXP}?            { yylval.value = strtod(yytext, NULL); return VALUE; }
{COMM}                          /* comms */ 

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
