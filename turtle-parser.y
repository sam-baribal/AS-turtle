%{
#include <stdio.h>

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

%token            KW_FORWARD    "forward"
%token            KW_BACKWARD   "backward"
%token            KW_PRINT      "print"
%token            KW_UP         "up"
%token            KW_DOWN       "down"
%token            KW_POSITION   "position"
%token            KW_RIGHT      "right"
%token            KW_LEFT       "left"
%token            KW_RIGHT      "rt"
%token            KW_LEFT       "lt"
%token            KW_HEADING    "heading"
%token            KW_COLOR      "color"
%token            KW_HOME       "home"

%token            KIND_CMD_REPEAT "repeat"
%token            KIND_CMD_SET    "set"
%token            KIND_CMD_PROC   "proc"
%token            KIND_CMD_CALL   "call"

%token            FUNC_COS        "cos"
%token            FUNC_RANDOM     "random"
%token            FUNC_SIN        "sin"
%token            FUNC_SQRT       "sqrt"
%token            FUNC_TAN        "tan"

%token            COLOR_RED     "red"
%token            COLOR_GREEN   "green"
%token            COLOR_BLUE    "blue"
%token            COLOR_CYAN    "cyan"
%token            COLOR_MAGENTA "magenta"
%token            COLOR_YELLOW  "yellow"
%token            COLOR_BLACK   "black"
%token            COLOR_GRAY    "gray"
%token            COLOR_WHITE   "white"

/* TODO: add other tokens */

%type <node> unit cmds cmd expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

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
  | FUNC_COS                { $$ = make_cmd_home(); }
  | COLOR_RED               { $$ = make_cmd_color(make_expr_value(1.0), make_expr_value(0.0), make_expr_value(0.0)); }
  | COLOR_GREEN             { $$ = make_cmd_color(make_expr_value(0.0), make_expr_value(1.0), make_expr_value(0.0)); }
  | COLOR_BLUE              { $$ = make_cmd_color(make_expr_value(0.0), make_expr_value(0.0), make_expr_value(1.0)); }
  | COLOR_CYAN              { $$ = make_cmd_color(make_expr_value(0.0), make_expr_value(1.0), make_expr_value(1.0)); }
  | COLOR_MAGENTA           { $$ = make_cmd_color(make_expr_value(1.0), make_expr_value(0.0), make_expr_value(1.0)); }
  | COLOR_YELLOW            { $$ = make_cmd_color(make_expr_value(1.0), make_expr_value(1.0), make_expr_value(0.0)); }
  | COLOR_BLACK             { $$ = make_cmd_color(make_expr_value(0.0), make_expr_value(0.0), make_expr_value(0.0)); }
  | COLOR_GRAY              { $$ = make_cmd_color(make_expr_value(0.5), make_expr_value(0.5), make_expr_value(0.5)); }
  | COLOR_WHITE             { $$ = make_cmd_color(make_expr_value(1.0), make_expr_value(1.0), make_expr_value(1.0)); }
;

expr:
    VALUE           { $$ = make_expr_value($1); }
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
