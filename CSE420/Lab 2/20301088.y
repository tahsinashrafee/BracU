%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "symbol_info.h"

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern FILE *yyout;

void yyerror(const char *s);
std::ofstream outlog("20301088_log.txt");

// Declaration of lines
extern int lines;
int lines = 1;

%}

%union {
    symbol_info *symbol;
}

// Token definitions
%token <symbol> ID CONST_INT CONST_FLOAT INT FLOAT VOID DO BREAK CONTINUE CHAR DOUBLE SWITCH CASE DEFAULT
%token <symbol> ASSIGNOP ADDOP MULOP RELOP LOGICOP INCOP DECOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON IF ELSE WHILE FOR PRINTLN RETURN

%type <symbol> program unit func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term factor argument_list arguments

%left ADDOP
%left MULOP
%left RELOP
%left LOGICOP
%left ASSIGNOP
%left INCOP DECOP
%right NOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start : program
{
    outlog << "At line no: " << lines << " start : program " << std::endl;
}
;

program : program unit
{
    outlog << "At line no: " << lines << " program : program unit " << std::endl;
    $$ = new symbol_info($1->getname() + "\n" + $2->getname(), "program");
}
| unit
{
    outlog << "At line no: " << lines << " program : unit " << std::endl;
    $$ = new symbol_info($1->getname(), "program");
}
;

unit : var_declaration
{
    outlog << "At line no: " << lines << " unit : var_declaration " << std::endl;
    $$ = new symbol_info($1->getname(), "unit");
}
| func_definition
{
    outlog << "At line no: " << lines << " unit : func_definition " << std::endl;
    $$ = new symbol_info($1->getname(), "unit");
}
;

func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
{
    outlog << "At line no: " << lines << " func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement " << std::endl;
    $$ = new symbol_info($1->getname() + " " + $2->getname() + "(" + $4->getname() + ")" + $6->getname(), "func_def");
}
| type_specifier ID LPAREN RPAREN compound_statement
{
    outlog << "At line no: " << lines << " func_definition : type_specifier ID LPAREN RPAREN compound_statement " << std::endl;
    $$ = new symbol_info($1->getname() + " " + $2->getname() + "()" + $5->getname(), "func_def");
}
;

parameter_list : parameter_list COMMA type_specifier ID
{
    outlog << "At line no: " << lines << " parameter_list : parameter_list COMMA type_specifier ID " << std::endl;
    $$ = new symbol_info($1->getname() + ", " + $3->getname() + " " + $4->getname(), "param_list");
}
| parameter_list COMMA type_specifier
{
    outlog << "At line no: " << lines << " parameter_list : parameter_list COMMA type_specifier " << std::endl;
    $$ = new symbol_info($1->getname() + ", " + $3->getname(), "param_list");
}
| type_specifier ID
{
    outlog << "At line no: " << lines << " parameter_list : type_specifier ID " << std::endl;
    $$ = new symbol_info($1->getname() + " " + $2->getname(), "param_list");
}
| type_specifier
{
    outlog << "At line no: " << lines << " parameter_list : type_specifier " << std::endl;
    $$ = new symbol_info($1->getname(), "param_list");
}
;

compound_statement : LCURL statements RCURL
{
    outlog << "At line no: " << lines << " compound_statement : LCURL statements RCURL " << std::endl;
    $$ = new symbol_info("{" + $2->getname() + "}", "compound_stmt");
}
| LCURL RCURL
{
    outlog << "At line no: " << lines << " compound_statement : LCURL RCURL " << std::endl;
    $$ = new symbol_info("{}", "compound_stmt");
}
;

var_declaration : type_specifier declaration_list SEMICOLON
{
    outlog << "At line no: " << lines << " var_declaration : type_specifier declaration_list SEMICOLON " << std::endl;
    $$ = new symbol_info($1->getname() + " " + $2->getname() + ";", "var_decl");
}
;

type_specifier : INT
{
    outlog << "At line no: " << lines << " type_specifier : INT " << std::endl;
    $$ = new symbol_info("int", "type_spec");
}
| FLOAT
{
    outlog << "At line no: " << lines << " type_specifier : FLOAT " << std::endl;
    $$ = new symbol_info("float", "type_spec");
}
| VOID
{
    outlog << "At line no: " << lines << " type_specifier : VOID " << std::endl;
    $$ = new symbol_info("void", "type_spec");
}
| CHAR
{
    outlog << "At line no: " << lines << " type_specifier : CHAR " << std::endl;
    $$ = new symbol_info("char", "type_spec");
}
| DOUBLE
{
    outlog << "At line no: " << lines << " type_specifier : DOUBLE " << std::endl;
    $$ = new symbol_info("double", "type_spec");
}
;

declaration_list : declaration_list COMMA ID
{
    outlog << "At line no: " << lines << " declaration_list : declaration_list COMMA ID " << std::endl;
    $$ = new symbol_info($1->getname() + ", " + $3->getname(), "decl_list");
}
| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
{
    outlog << "At line no: " << lines << " declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD " << std::endl;
    $$ = new symbol_info($1->getname() + ", " + $3->getname() + "[" + $5->getname() + "]", "decl_list");
}
| ID
{
    outlog << "At line no: " << lines << " declaration_list : ID " << std::endl;
    $$ = new symbol_info($1->getname(), "decl_list");
}
| ID LTHIRD CONST_INT RTHIRD
{
    outlog << "At line no: " << lines << " declaration_list : ID LTHIRD CONST_INT RTHIRD " << std::endl;
    $$ = new symbol_info($1->getname() + "[" + $3->getname() + "]", "decl_list");
}
;

statements : statement
{
    outlog << "At line no: " << lines << " statements : statement " << std::endl;
    $$ = new symbol_info($1->getname(), "stmts");
}
| statements statement
{
    outlog << "At line no: " << lines << " statements : statements statement " << std::endl;
    $$ = new symbol_info($1->getname() + "\n" + $2->getname(), "stmts");
}
;

statement : var_declaration
{
    outlog << "At line no: " << lines << " statement : var_declaration " << std::endl;
    $$ = new symbol_info($1->getname(), "stmt");
}
| expression_statement
{
    outlog << "At line no: " << lines << " statement : expression_statement " << std::endl;
    $$ = new symbol_info($1->getname(), "stmt");
}
| compound_statement
{
    outlog << "At line no: " << lines << " statement : compound_statement " << std::endl;
    $$ = new symbol_info($1->getname(), "stmt");
}
| FOR LPAREN expression_statement expression_statement expression RPAREN statement
{
    outlog << "At line no: " << lines << " statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement " << std::endl;
    $$ = new symbol_info("for(" + $3->getname() + " " + $4->getname() + " " + $5->getname() + ")" + $7->getname(), "stmt");
}
| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
{
    outlog << "At line no: " << lines << " statement : IF LPAREN expression RPAREN statement " << std::endl;
    $$ = new symbol_info("if(" + $3->getname() + ")" + $5->getname(), "stmt");
}
| IF LPAREN expression RPAREN statement ELSE statement
{
    outlog << "At line no: " << lines << " statement : IF LPAREN expression RPAREN statement ELSE statement " << std::endl;
    $$ = new symbol_info("if(" + $3->getname() + ")" + $5->getname() + " else " + $7->getname(), "stmt");
}
| WHILE LPAREN expression RPAREN statement
{
    outlog << "At line no: " << lines << " statement : WHILE LPAREN expression RPAREN statement " << std::endl;
    $$ = new symbol_info("while(" + $3->getname() + ")" + $5->getname(), "stmt");
}
| DO compound_statement WHILE LPAREN expression RPAREN SEMICOLON
{
    outlog << "At line no: " << lines << " statement : DO compound_statement WHILE LPAREN expression RPAREN SEMICOLON " << std::endl;
    $$ = new symbol_info("do " + $2->getname() + " while(" + $5->getname() + ");", "stmt");
}
| BREAK SEMICOLON
{
    outlog << "At line no: " << lines << " statement : BREAK SEMICOLON " << std::endl;
    $$ = new symbol_info("break;", "stmt");
}
| CONTINUE SEMICOLON
{
    outlog << "At line no: " << lines << " statement : CONTINUE SEMICOLON " << std::endl;
    $$ = new symbol_info("continue;", "stmt");
}
| SWITCH LPAREN expression RPAREN compound_statement
{
    outlog << "At line no: " << lines << " statement : SWITCH LPAREN expression RPAREN compound_statement " << std::endl;
    $$ = new symbol_info("switch(" + $3->getname() + ")" + $5->getname(), "stmt");
}
| PRINTLN LPAREN ID RPAREN SEMICOLON
{
    outlog << "At line no: " << lines << " statement : PRINTLN LPAREN ID RPAREN SEMICOLON " << std::endl;
    $$ = new symbol_info("println(" + $3->getname() + ");", "stmt");
}
| RETURN expression SEMICOLON
{
    outlog << "At line no: " << lines << " statement : RETURN expression SEMICOLON " << std::endl;
    $$ = new symbol_info("return " + $2->getname() + ";", "stmt");
}
;

expression_statement : SEMICOLON
{
    outlog << "At line no: " << lines << " expression_statement : SEMICOLON " << std::endl;
    $$ = new symbol_info(";", "expr_stmt");
}
| expression SEMICOLON
{
    outlog << "At line no: " << lines << " expression_statement : expression SEMICOLON " << std::endl;
    $$ = new symbol_info($1->getname() + ";", "expr_stmt");
}
;

variable : ID
{
    outlog << "At line no: " << lines << " variable : ID " << std::endl;
    $$ = new symbol_info($1->getname(), "var");
}
| ID LTHIRD expression RTHIRD
{
    outlog << "At line no: " << lines << " variable : ID LTHIRD expression RTHIRD " << std::endl;
    $$ = new symbol_info($1->getname() + "[" + $3->getname() + "]", "var");
}
;

expression : logic_expression
{
    outlog << "At line no: " << lines << " expression : logic_expression " << std::endl;
    $$ = new symbol_info($1->getname(), "expr");
}
| variable ASSIGNOP logic_expression
{
    outlog << "At line no: " << lines << " expression : variable ASSIGNOP logic_expression " << std::endl;
    $$ = new symbol_info($1->getname() + "=" + $3->getname(), "expr");
}
;

logic_expression : rel_expression
{
    outlog << "At line no: " << lines << " logic_expression : rel_expression " << std::endl;
    $$ = new symbol_info($1->getname(), "logic_expr");
}
| rel_expression LOGICOP rel_expression
{
    outlog << "At line no: " << lines << " logic_expression : rel_expression LOGICOP rel_expression " << std::endl;
    $$ = new symbol_info($1->getname() + " " + $2->getname() + " " + $3->getname(), "logic_expr");
}
;

rel_expression : simple_expression
{
    outlog << "At line no: " << lines << " rel_expression : simple_expression " << std::endl;
    $$ = new symbol_info($1->getname(), "rel_expr");
}
| simple_expression RELOP simple_expression
{
    outlog << "At line no: " << lines << " rel_expression : simple_expression RELOP simple_expression " << std::endl;
    $$ = new symbol_info($1->getname() + " " + $2->getname() + " " + $3->getname(), "rel_expr");
}
;

simple_expression : term
{
    outlog << "At line no: " << lines << " simple_expression : term " << std::endl;
    $$ = new symbol_info($1->getname(), "simple_expr");
}
| simple_expression ADDOP term
{
    outlog << "At line no: " << lines << " simple_expression : simple_expression ADDOP term " << std::endl;
    $$ = new symbol_info($1->getname() + " " + $2->getname() + " " + $3->getname(), "simple_expr");
}
;

term : factor
{
    outlog << "At line no: " << lines << " term : factor " << std::endl;
    $$ = new symbol_info($1->getname(), "term");
}
| term MULOP factor
{
    outlog << "At line no: " << lines << " term : term MULOP factor " << std::endl;
    $$ = new symbol_info($1->getname() + " " + $2->getname() + " " + $3->getname(), "term");
}
;

factor : variable
{
    outlog << "At line no: " << lines << " factor : variable " << std::endl;
    $$ = new symbol_info($1->getname(), "factor");
}
| ID LPAREN argument_list RPAREN
{
    outlog << "At line no: " << lines << " factor : ID LPAREN argument_list RPAREN " << std::endl;
    $$ = new symbol_info($1->getname() + "(" + $3->getname() + ")", "factor");
}
| LPAREN expression RPAREN
{
    outlog << "At line no: " << lines << " factor : LPAREN expression RPAREN " << std::endl;
    $$ = new symbol_info("(" + $2->getname() + ")", "factor");
}
| CONST_INT
{
    outlog << "At line no: " << lines << " factor : CONST_INT " << std::endl;
    $$ = new symbol_info($1->getname(), "factor");
}
| CONST_FLOAT
{
    outlog << "At line no: " << lines << " factor : CONST_FLOAT " << std::endl;
    $$ = new symbol_info($1->getname(), "factor");
}
| variable INCOP
{
    outlog << "At line no: " << lines << " factor : variable INCOP " << std::endl;
    $$ = new symbol_info($1->getname() + "++", "factor");
}
| variable DECOP
{
    outlog << "At line no: " << lines << " factor : variable DECOP " << std::endl;
    $$ = new symbol_info($1->getname() + "--", "factor");
}
;

argument_list : arguments
{
    outlog << "At line no: " << lines << " argument_list : arguments " << std::endl;
    $$ = new symbol_info($1->getname(), "arg_list");
}
|
{
    outlog << "At line no: " << lines << " argument_list : /* empty */ " << std::endl;
    $$ = new symbol_info("", "arg_list");
}
;

arguments : arguments COMMA logic_expression
{
    outlog << "At line no: " << lines << " arguments : arguments COMMA logic_expression " << std::endl;
    $$ = new symbol_info($1->getname() + ", " + $3->getname(), "args");
}
| logic_expression
{
    outlog << "At line no: " << lines << " arguments : logic_expression " << std::endl;
    $$ = new symbol_info($1->getname(), "args");
}
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("fopen");
        return 1;
    }

    yyin = inputFile;
    yyout = fopen("20301088.txt", "w");

    do {
        yyparse();
    } while (!feof(yyin));

    fclose(yyin);
    fclose(yyout);

    return 0;
}
