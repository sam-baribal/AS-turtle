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

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

%token <node>     FUNC        "func"

%token <node>     KW_FORWARD  "forward"
%token <node>     KW_BACKWARD "backward"
%token <node>     KW_PRINT    "print"
%token <node>     KW_UP       "up"
%token <node>     KW_DOWN     "down"
%token <node>     KW_POSITION "position"
%token <node>     KW_RIGHT    "right"
%token <node>     KW_LEFT     "left"
%token <node>     KW_HEADING  "heading"
%token <node>     KW_COLOR    "color"
%token <node>     KW_HOME     "home"

%token <node>     KW_SIN      "sin"
%token <node>     KW_COS      "cos"
%token <node>     KW_TAN      "tan"
%token <node>     KW_SQRT     "sqrt"
%token <node>     KW_RANDOM   "random"

%token <node>     COLOR_RED     "red"
%token <node>     COLOR_GREEN   "green"
%token <node>     COLOR_BLUE    "blue"
%token <node>     COLOR_CYAN    "cyan"
%token <node>     COLOR_MAGENTA "magenta"
%token <node>     COLOR_YELLOW  "yellow"
%token <node>     COLOR_BLACK   "black"
%token <node>     COLOR_GRAY    "gray"
%token <node>     COLOR_WHITE   "white"

%left '+' '-'
%left '*' '/'
 
/* TODO: add other tokens */

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
  | KW_POSITION expr expr   { $$ = make_cmd_position($2, $3); }
  | KW_RIGHT expr           { $$ = make_cmd_right($2); }
  | KW_LEFT expr            { $$ = make_cmd_left($2); }
  | KW_HEADING expr         { $$ = make_cmd_heading($2); }
  | KW_COLOR expr expr expr { $$ = make_cmd_color($2, $3, $4); }
  | KW_HOME                 { $$ = make_cmd_home(); }
  | COLOR_RED       { $$ = make_cmd_color(make_expr_value(1.0), make_expr_value(0.0), make_expr_value(0.0)); }
  | COLOR_GREEN     { $$ = make_cmd_color(make_expr_value(0.0), make_expr_value(1.0), make_expr_value(0.0)); }
  | COLOR_BLUE      { $$ = make_cmd_color(make_expr_value(0.0), make_expr_value(0.0), make_expr_value(1.0)); }
  | COLOR_CYAN      { $$ = make_cmd_color(make_expr_value(0.0), make_expr_value(1.0), make_expr_value(1.0)); }
  | COLOR_MAGENTA   { $$ = make_cmd_color(make_expr_value(1.0), make_expr_value(0.0), make_expr_value(1.0)); }
  | COLOR_YELLOW    { $$ = make_cmd_color(make_expr_value(1.0), make_expr_value(1.0), make_expr_value(0.0)); }
  | COLOR_BLACK     { $$ = make_cmd_color(make_expr_value(0.0), make_expr_value(0.0), make_expr_value(0.0)); }
  | COLOR_GRAY      { $$ = make_cmd_color(make_expr_value(0.5), make_expr_value(0.5), make_expr_value(0.5)); }
  | COLOR_WHITE     { $$ = make_cmd_color(make_expr_value(1.0), make_expr_value(1.0), make_expr_value(1.0)); }
;

expr:
    VALUE             { $$ = make_expr_value($1); }
  | NAME              { $$ = make_expr_name($1); }
  | expr '+' expr     { $$ = make_expr_value($1->u.value + $3->u.value); }
  | expr '-' expr     { $$ = make_expr_value($1->u.value - $3->u.value); }
  | expr '*' expr     { $$ = make_expr_value($1->u.value * $3->u.value); }
  | expr '/' expr     { $$ = make_expr_value($1->u.value / $3->u.value); }
  | expr '^' expr     { $$ = make_expr_value(pow($1->u.value, $3->u.value)); }
  | '-' expr          { $$ = make_expr_value(-$2->u.value); }
  | '(' expr ')'      { /*$$ = ; */}
 ;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
