#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846
#define SQRT2 1.41421356237309504880
#define SQRT3 1.7320508075688772935

#define DEG2RAD 57.295780

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  node->children_count = 0;
  return node;
}

struct ast_node *make_expr_name(const char* name) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_EXPR_NAME;
  node->u.name = strdup(name);
  node->children_count = 0;
  return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_FORWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_BACKWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_POSITION;
  node->children_count = 2;
  node->children[0] = expr1;
  node->children[1] = expr2;
  return node;
}

struct ast_node *make_cmd_print(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_PRINT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_up() {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_UP;
  node->children_count = 0;
  return node;
}
struct ast_node *make_cmd_down() {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_DOWN;
  node->children_count = 0;
  return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_RIGHT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}


struct ast_node *make_cmd_left(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_LEFT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}


struct ast_node *make_cmd_heading(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HEADING;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}


struct ast_node *make_cmd_color_RGB(struct ast_node *valueR, struct ast_node *valueG, struct ast_node *valueB) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 3;
  node->children[0] = valueR;
  node->children[1] = valueG;
  node->children[2] = valueB;
  return node;
}

struct ast_node *make_cmd_color_name(const char *name){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 3;
  double r, g, b;
  if (strcmp(name, "red") == 0){
    r = 1.0;
    g = 0.0;
    b = 0.0;
  }
  else if (strcmp(name, "green") == 0){
    r = 0.0;
    g = 1.0;
    b = 0.0;
  }
  else if (strcmp(name, "blue") == 0){
    r = 0.0;
    g = 0.0;
    b = 1.0;
  }
  else if (strcmp(name, "cyan") == 0){
    r = 0.0;
    g = 1.0;
    b = 1.0;
  }
  else if (strcmp(name, "magenta") == 0){
    r = 1.0;
    g = 0.0;
    b = 1.0;
  }
  else if (strcmp(name, "yellow") == 0){
    r = 1.0;
    g = 1.0;
    b = 0.0;
  }
  else if (strcmp(name, "black") == 0){
    r = 0.0;
    g = 0.0;
    b = 0.0;
  }
  else if (strcmp(name, "gray") == 0){
    r = 0.5;
    g = 0.5;
    b = 0.5;
  }
  else{
    r = 1.0;
    g = 1.0;
    b = 1.0;
  }
  node->children[0] = make_expr_value(r);
  node->children[1] = make_expr_value(g);
  node->children[2] = make_expr_value(b);
  return node;
}


struct ast_node *make_cmd_home() {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HOME;
  node->children_count = 0;
  return node;
}

struct ast_node *make_expr_func_cos(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_EXPR_FUNC;
  node->u.func = FUNC_COS;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}


struct ast_node *make_expr_func_rand(struct ast_node *down_limit, struct ast_node *up_limit) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_EXPR_FUNC;
  node->u.func = FUNC_RANDOM;
  node->children_count = 2;
  node->children[0] = down_limit;
  node->children[1] = up_limit;
  return node;
}

struct ast_node *make_expr_func_sin(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_EXPR_FUNC;
  node->u.func = FUNC_SIN;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_expr_func_sqrt(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_EXPR_FUNC;
  node->u.func = FUNC_SQRT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_expr_func_tan(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_EXPR_FUNC;
  node->u.func = FUNC_TAN;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_expr_unary_operator(const char operator, struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_EXPR_UNOP;
  node->u.op = operator;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_expr_binary_operator(const char operator, struct ast_node *expr1, struct ast_node *expr2) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_EXPR_BINOP;
  node->u.op = operator;
  node->children_count = 2;
  node->children[0] = expr1;
  node->children[1] = expr2;
  return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *block){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_REPEAT;
  node->children_count = 2;
  node->children[0] = expr;
  node->children[1] = block;
  return node;
}

struct ast_node *make_cmd_proc(struct ast_node *name, struct ast_node *body){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_PROC;
  node->children_count = 2;
  node->children[0] = name;
  node->children[1] = body;
  return node;
}

struct ast_node *make_cmd_call(struct ast_node *name){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_CALL;
  node->children_count = 1;
  node->children[0] = name;
  return node;
}

struct ast_node *make_cmd_block(struct ast_node *first_command){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_BLOCK;
  node->children_count = 1;
  node->children[0] = first_command;
  return node;
}

struct ast_node *make_expr_block(struct ast_node *first_command){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_EXPR_BLOCK;
  node->children_count = 1;
  node->children[0] = first_command;
  return node;
}

struct ast_node *make_cmd_set(struct ast_node *name, struct ast_node *value){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->next = NULL;
  node->kind = KIND_CMD_SET;
  node->children_count = 2;
  node->children[0] = name;
  node->children[1] = value;
  return node;
}

/*
 * destroy
 */

void ast_destroy_node(struct ast_node *self){
  for(int i = 0; i < self->children_count; i++){
    ast_destroy_node(self->children[i]);
  }
  if (self->next != NULL){
    ast_destroy_node(self->next);
  }
  if(self->kind == KIND_EXPR_NAME){
    free(self->u.name);
  }
  free(self);
}

void ast_destroy(struct ast *self) {
  fprintf(stderr, "\n==[ ast_destroy ]==\n");
  ast_destroy_node(self->unit);
}

/*
 * context
 */

void context_create(struct context *self) {
  fprintf(stderr, "\n==[ context_create ]==\n");
  self->x = 0;
  self->y = 0;
  self->angle = 0;
  self->up = false;
  self->proc_count = 0;
  self->var_count = 0;
}

void context_compute_new_position(struct context *self, double n){
  self->x += n*sin(self->angle/DEG2RAD);
  self->y -= n*cos(self->angle/DEG2RAD);
}

void context_add_proc(struct context *self, const char *name, struct ast_node *body){
  int count = self->proc_count;
  for (int i = 0; i < count; i++){
    if(strcmp(self->procedures[i].name, name) == 0){
      fprintf(stderr, "\nError : proc name %s already used\n", name);
      exit(1);
    }
  }
  if (self->proc_count < PROC_MAX){
    self->procedures[self->proc_count].name = strdup(name);
    self->procedures[self->proc_count].body = body;
    self->proc_count ++;
  }
  else{
    fprintf(stderr, "\nError : proc limit PROC_MAX reached (%d)\n", PROC_MAX);
    exit(1);
  }
}

struct ast_node *context_get_proc(struct context *self, const char *name){
  int count = self->proc_count;
  for (int i = 0; i < count; i++){
    if (strcmp(self->procedures[i].name, name) == 0){
      return self->procedures[i].body;
    }
  }
  fprintf(stderr, "\nError : proc %s was not set\n", name);
  exit(1);
}

void context_add_var(struct context *self, const char *name, double value){
  int count = self->var_count;
  for (int i = 0; i < count; i++){
    if(strcmp(self->variables[i].name, name) == 0){
      fprintf(stderr, "\nError : var name %s already used\n", name);
      exit(1);
    }
  }
  if (self->var_count < VAR_MAX){
    self->variables[self->var_count].name = strdup(name);
    self->variables[self->var_count].value = value;
    self->var_count ++;
  }
  else{
    fprintf(stderr, "\nError : var limit VAR_MAX reached (%d)\n", VAR_MAX);
    exit(1);
  }
}

double context_get_var(struct context *self, const char *name){
  if (strcmp(name, "PI") == 0){
    return PI;
  }
  else if (strcmp(name, "SQRT2") == 0){
    return SQRT2;
  }
  else if (strcmp(name, "SQRT3") == 0){
    return SQRT3;
  }
  int count = self->var_count;
  for (int i = 0; i < count; i++){
    if (strcmp(self->variables[i].name, name) == 0){
      return self->variables[i].value;
    }
  }
  fprintf(stderr, "\nError : var %s was not set\n", name);
  exit(1);
}

/*
 * eval
 */

double ast_get_value(const struct ast_node *self, struct context *ctx){
  switch (self->kind){
    case KIND_CMD_REPEAT :
    case KIND_CMD_BLOCK :
    case KIND_CMD_CALL :
      break;
    case KIND_EXPR_FUNC :
      switch (self->u.func){
        case FUNC_COS :
            return cos(ast_get_value(self->children[0], ctx));
          break;
        case FUNC_RANDOM :
            double min = ast_get_value(self->children[0], ctx);
            double max = ast_get_value(self->children[1], ctx);
            if (min > max){
              fprintf(stderr, "\nError : invalid random(min, max) parameters, max should be stricly greater than min\n");
              exit(1);
            }
            return min + (max - min) * (rand() / (double)RAND_MAX);
          break;
        case FUNC_SIN :
            return sin(ast_get_value(self->children[0], ctx));
          break;
        case FUNC_SQRT :
            return sqrt(ast_get_value(self->children[0], ctx));
          break;
        case FUNC_TAN :
            return tan(ast_get_value(self->children[0], ctx));
          break;
        default:
          fprintf(stderr, "\nError : unknown function\n");
          exit(1);
          break;
      }
    case KIND_EXPR_VALUE :
      return self->u.value;
    case KIND_EXPR_UNOP :
      if (self->u.op == '-') {
        return -(ast_get_value(self->children[0], ctx));
      }
      else{
        fprintf(stderr, "\nError : unknown unary operator\n");
        exit(1);
      }
      break;
    case KIND_EXPR_BINOP :
      switch (self->u.op) {
        case '+' :
          return ast_get_value(self->children[0], ctx) + ast_get_value(self->children[1], ctx);
        case '-' :
          return ast_get_value(self->children[0], ctx) - ast_get_value(self->children[1], ctx);
        case '*' :
          return ast_get_value(self->children[0], ctx) * ast_get_value(self->children[1], ctx);
        case '/' :
          if (ast_get_value(self->children[1], ctx) == 0.0){
            fprintf(stderr, "\nError : division by 0\n");
            exit(1);
          }
          return ast_get_value(self->children[0], ctx) / ast_get_value(self->children[1], ctx);
        case '^' :
          return pow(ast_get_value(self->children[0], ctx), ast_get_value(self->children[1], ctx));
        default :
          fprintf(stderr, "\nError : unknown binary operator\n");
          exit(1);
      }
    case KIND_EXPR_BLOCK :
      break;
    case KIND_EXPR_NAME :
      return context_get_var(ctx, self->u.name);
      break;
    default:
      fprintf(stderr, "\nError : unsupported node kind in ast_get_value call\n");
      exit(1);
  }
  exit(1);
}

void ast_eval_node(const struct ast_node *self, struct context *ctx, FILE * stream) {
  // process current node
  switch (self->kind){
    // CMD
    case KIND_CMD_SIMPLE :
      switch (self->u.cmd){
        case CMD_UP :
          ctx->up = true;
          break;
        case CMD_DOWN :
          ctx->up = false;
          break;
        case CMD_RIGHT :
          ctx->angle += ast_get_value(self->children[0], ctx);
          break;
        case CMD_LEFT :
          ctx->angle -= ast_get_value(self->children[0], ctx);
          break;
        case CMD_HEADING :
          ctx->angle = ast_get_value(self->children[0], ctx);
          break;
        case CMD_FORWARD :
          context_compute_new_position(ctx, ast_get_value(self->children[0], ctx));
          if (ctx->up == true){
            fprintf(stream, "MoveTo ");
          }
          else {
            fprintf(stream, "LineTo ");
          }
          fprintf(stream, "%f %f\n", ctx->x, ctx->y);
          break;
        case CMD_BACKWARD :
          context_compute_new_position(ctx, -ast_get_value(self->children[0], ctx));
          if (ctx->up == true){
            fprintf(stream, "MoveTo ");
          }
          else {
            fprintf(stream, "LineTo ");
          }
          fprintf(stream, "%f %f\n", ctx->x, ctx->y);
          break;
        case CMD_POSITION :
          ctx->x = ast_get_value(self->children[0], ctx);
          ctx->y = ast_get_value(self->children[1], ctx);
          fprintf(stream, "MoveTo %f %f\n", ctx->x, ctx->y);
          break;
        case CMD_HOME :
          context_create(ctx);
          break;
        case CMD_COLOR :
          fprintf(stream, "Color ");
          ast_eval_node(self->children[0], ctx, stream);
          ast_eval_node(self->children[1], ctx, stream);
          ast_eval_node(self->children[2], ctx, stream);
          fprintf(stream, "\n");
          break;
        case CMD_PRINT :
          ast_eval_node(self->children[0], ctx, stderr);
          break;
        default:
          fprintf(stderr, "\nError : unknown command\n");
          exit(1);
      }
      break;
    case KIND_CMD_REPEAT :
      int repeats = (int)floor(ast_get_value(self->children[0], ctx));
      for (int i = 0; i < repeats; i++){
        ast_eval_node(self->children[1], ctx, stream);
      }
      break;
    case KIND_CMD_BLOCK :
      ast_eval_node(self->children[0], ctx, stream);
      break;
    case KIND_CMD_PROC :
      context_add_proc(ctx, self->children[0]->u.name, self->children[1]);
      break;
    case KIND_CMD_CALL :
      struct ast_node *proc_body = context_get_proc(ctx, self->children[0]->u.name);
      if (proc_body != NULL){
        ast_eval_node(proc_body, ctx, stream);
      }
      else {
        fprintf(stderr, "\nError : unknown procedure name %s\n", self->u.name);
        exit(1);
      }
      break;
    case KIND_CMD_SET :
      context_add_var(ctx, self->children[0]->u.name, ast_get_value(self->children[1], ctx));
      break;

    // EXPR
    case KIND_EXPR_FUNC :
      break;
    case KIND_EXPR_VALUE :
      fprintf(stream, "%f ", self->u.value);
      break;
    case KIND_EXPR_UNOP :
    case KIND_EXPR_BINOP :
    case KIND_EXPR_BLOCK :
      ast_eval_node(self->children[0], ctx, stream);
      break;
    case KIND_EXPR_NAME :
      fprintf(stream, "%f ", context_get_var(ctx, self->u.name));
      break;
    default:
      fprintf(stderr, "\nError : unknown node kind\n");
      exit(1);
  }

  // go on to the next node (if it exists)
  if (self->next != NULL && stream == stdout){
    ast_eval_node(self->next, ctx, stdout);
  }
}

void ast_eval(const struct ast *self, struct context *ctx) {
  fprintf(stderr, "\n==[ ast_eval ]==\n");
  ast_eval_node(self->unit, ctx, stdout);
}

/*
 * print
 */

void ast_print_node(const struct ast_node *self, FILE * stream){
  // print current node
  switch (self->kind){
    // CMD
    case KIND_CMD_SIMPLE :
      switch (self->u.cmd){
        case CMD_UP :
          fprintf(stream, "up ");
          break;
        case CMD_DOWN :
          fprintf(stream, "down ");
          break;
        case CMD_RIGHT :
          fprintf(stream, "right ");
          ast_print_node(self->children[0], stream);
          break;
        case CMD_LEFT :
          fprintf(stream, "left ");
          ast_print_node(self->children[0], stream);
          break;
        case CMD_HEADING :
          fprintf(stream, "heading ");
          ast_print_node(self->children[0], stream);
          break;
        case CMD_FORWARD :
          fprintf(stream, "forward ");
          ast_print_node(self->children[0], stream);
          break;
        case CMD_BACKWARD :
          fprintf(stream, "backward ");
          ast_print_node(self->children[0], stream);
          break;
        case CMD_POSITION :
          fprintf(stream, "position ");
          ast_print_node(self->children[0], stream);
          ast_print_node(self->children[1], stream);
          break;
        case CMD_HOME :
          fprintf(stream, "position");
          break;
        case CMD_COLOR :
          fprintf(stream, "color ");
          ast_print_node(self->children[0], stream);
          ast_print_node(self->children[1], stream);
          ast_print_node(self->children[2], stream);
          break;
        case CMD_PRINT :
          fprintf(stream, "print ");
          ast_print_node(self->children[0], stream);
          break;
        default:
          fprintf(stderr, "\nError : unknown command\n");
          exit(1);
      }
      break;
    case KIND_CMD_REPEAT :
      fprintf(stream, "repeat ");
      ast_print_node(self->children[0], stream);
      fprintf(stream, "{\n");
      ast_print_node(self->children[1], stream);
      fprintf(stream, "}\n");
      break;
    case KIND_CMD_BLOCK :
      fprintf(stream, "{\n");
      ast_print_node(self->children[0], stream);
      fprintf(stream, "}\n");
      break;
    case KIND_CMD_PROC :
      fprintf(stream, "proc ");
      ast_print_node(self->children[0], stream);
      fprintf(stream, "{\n");
      ast_print_node(self->children[1], stream);
      fprintf(stream, "}\n");
      break;
    case KIND_CMD_CALL :
      fprintf(stream, "call ");
      ast_print_node(self->children[0], stream);
      break;
    case KIND_CMD_SET :
      fprintf(stream, "set ");
      ast_print_node(self->children[0], stream);
      ast_print_node(self->children[1], stream);
      break;
      
    // EXPR
    case KIND_EXPR_FUNC :
      switch (self->u.func){
        case FUNC_COS :
          fprintf(stream, "cos (");
          ast_print_node(self->children[0], stream);
          fprintf(stream, ")");
          break;
        case FUNC_RANDOM :
          fprintf(stream, "sin (");
          ast_print_node(self->children[0], stream);
          fprintf(stream, ", ");
          ast_print_node(self->children[1], stream);
          fprintf(stream, ")");
          break;
        case FUNC_SIN :
          fprintf(stream, "sin (");
          ast_print_node(self->children[0], stream);
          fprintf(stream, ")");
          break;
        case FUNC_SQRT :
        fprintf(stream, "sqrt (");
          ast_print_node(self->children[0], stream);
          fprintf(stream, ")");
          break;
        case FUNC_TAN :
          fprintf(stream, "tan (");
          ast_print_node(self->children[0], stream);
          fprintf(stream, ")");
          break;
        default:
          fprintf(stderr, "\nError : unknown function\n");
          exit(1);
      }
    case KIND_EXPR_VALUE :
      fprintf(stream, "%f ", self->u.value);
      break;
    case KIND_EXPR_UNOP :
      fprintf(stream, "%c", self->u.op);
      ast_print_node(self->children[0], stream);
      break;
    case KIND_EXPR_BINOP :
      ast_print_node(self->children[0], stream);
      fprintf(stream, "%c", self->u.op);
      ast_print_node(self->children[1], stream);
      break;
    case KIND_EXPR_BLOCK :
      fprintf(stream, "{\n");
      ast_print_node(self->children[0], stream);
      fprintf(stream, "}\n");
      break;
    case KIND_EXPR_NAME :
      fprintf(stream, "%s", self->u.name);
      break;
    default:
      fprintf(stderr, "\nError : unknown node kind\n");
      exit(1);
  }
  if (self->next != NULL){
    fprintf(stream, "\n");
    ast_print_node(self->next, stream);
  }
}

void ast_print(const struct ast *self) {
  fprintf(stderr, "\n==[ ast_print ]==\n");
  ast_print_node(self->unit, stdin);
}