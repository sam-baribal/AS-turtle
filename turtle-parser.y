%{
#include <stdio.h>
#include <math.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  char *name;
  struct ast_node *node;
}

%token <value>    VALUE         "value"
%token <name>     NAME          "name"

%token            COLOR_RED     "red"
%token            COLOR_GREEN   "green"
%token            COLOR_BLUE    "blue"
%token            COLOR_CYAN    "cyan"
%token            COLOR_MAGENTA "magenta"
%token            COLOR_YELLOW  "yellow"
%token            COLOR_BLACK   "black"
%token            COLOR_GRAY    "gray"
%token            COLOR_WHITE   "white"

%token            KW_FORWARD    "forward" // "fw"
%token            KW_BACKWARD   "backward" // "bw"
%token            KW_PRINT      "print"
%token            KW_UP         "up"
%token            KW_DOWN       "down"
%token            KW_POSITION   "position" // "pos"
%token            KW_RIGHT      "right" // "rt"
%token            KW_LEFT       "left"  // "lt"
%token            KW_HEADING    "heading" // "hd"
%token            KW_COLOR      "color"
%token            KW_HOME       "home"

%token            KW_REPEAT     "repeat"
%token            KW_SET        "set"
%token            KW_PROC       "proc"
%token            KW_CALL       "call"

%token            KW_COS        "cos"
%token            KW_RANDOM     "random"
%token            KW_SIN        "sin"
%token            KW_SQRT       "sqrt"
%token            KW_TAN        "tan"

%token            KW_BLOCK_START  "{"
%token            KW_BLOCK_END    "}"
%token            KW_PARAM_START  "("
%token            KW_PARAM_END    ")"
%token            KW_PARAM_SEP    ","

%left '+' '-'
%left '*' '/'

%type <node> unit cmds cmd expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_PRINT expr           { $$ = make_cmd_print($2); }
  | KW_UP                   { $$ = make_cmd_up(); }
  | KW_DOWN                 { $$ = make_cmd_down(); }
  | KW_FORWARD expr         { $$ = make_cmd_forward($2); }
  | KW_BACKWARD expr        { $$ = make_cmd_backward($2); }
  | KW_POSITION expr KW_PARAM_SEP expr   { $$ = make_cmd_position($2, $4); }
  | KW_RIGHT expr           { $$ = make_cmd_right($2); }
  | KW_LEFT expr            { $$ = make_cmd_left($2); }
  | KW_HEADING expr         { $$ = make_cmd_heading($2); }
  | KW_COLOR expr KW_PARAM_SEP expr KW_PARAM_SEP expr { $$ = make_cmd_color_RGB($2, $4, $6); }
  | KW_COLOR COLOR_RED      { $$ = make_cmd_color_name("red"); }
  | KW_COLOR COLOR_GREEN    { $$ = make_cmd_color_name("green"); }
  | KW_COLOR COLOR_BLUE     { $$ = make_cmd_color_name("blue"); }
  | KW_COLOR COLOR_CYAN     { $$ = make_cmd_color_name("cyan"); }
  | KW_COLOR COLOR_MAGENTA  { $$ = make_cmd_color_name("magenta"); }
  | KW_COLOR COLOR_YELLOW   { $$ = make_cmd_color_name("yellow"); }
  | KW_COLOR COLOR_BLACK    { $$ = make_cmd_color_name("black"); }
  | KW_COLOR COLOR_GRAY     { $$ = make_cmd_color_name("gray"); }
  | KW_COLOR COLOR_WHITE    { $$ = make_cmd_color_name("white"); }
  | KW_HOME                 { $$ = make_cmd_home(); }
  | KW_REPEAT expr KW_BLOCK_START cmds KW_BLOCK_END    { $$ = make_cmd_repeat($2, $4); }
  | KW_PROC expr KW_BLOCK_START cmds KW_BLOCK_END      { $$ = make_cmd_proc($2, $4); }
  | KW_CALL expr            { $$ = make_cmd_call($2); }
  | KW_SET expr expr        { $$ = make_cmd_set($2, $3); }
;

expr:
    VALUE             { $$ = make_expr_value($1); }
  | NAME              { $$ = make_expr_name($1); }
  | KW_BLOCK_START cmds KW_BLOCK_END { $$ = make_expr_block($2); }
  | '-' expr          { $$ = make_expr_unary_operator('-', $2); }
  | KW_RANDOM KW_PARAM_START expr KW_PARAM_SEP expr KW_PARAM_END  { $$ = make_expr_func_rand($3, $5); }
  | KW_COS KW_PARAM_START expr KW_PARAM_END              { $$ = make_expr_func_cos($3); }
  | KW_SIN KW_PARAM_START expr KW_PARAM_END              { $$ = make_expr_func_sin($3); }
  | KW_TAN KW_PARAM_START expr KW_PARAM_END              { $$ = make_expr_func_tan($3); }
  | KW_SQRT KW_PARAM_START expr KW_PARAM_END             { $$ = make_expr_func_sqrt($3); }
  | expr '+' expr     { $$ = make_expr_binary_operator('+', $1, $3); }
  | expr '-' expr     { $$ = make_expr_binary_operator('-', $1, $3); }
  | expr '*' expr     { $$ = make_expr_binary_operator('*', $1, $3); }
  | expr '/' expr     { $$ = make_expr_binary_operator('/', $1, $3); }
  | expr '^' expr     { $$ = make_expr_binary_operator('^', $1, $3); }
 ;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
