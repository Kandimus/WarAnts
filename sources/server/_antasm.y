%{
#pragma warning(disable:4996)

#include <string>
-#include "bcode.h"

/* For BISON */
-extern char *yytext;

-extern void yyerror(const char *msg);
-extern int  yylex();

%}

%union
{
    Pragma* TPRAGMA;
    Function* TFUNCTION;
    std::string TSTRING;
    RegisterType TREGISTER;
    Expr TEXPR;
}

%token LROUND RROUND LSQUARE RSQUARE COMMA NEW_LINE COLON
%token NUMBER ID CHARACTER_STRING
%token PRAGMA_NAME PRAGMA_VERSION PRAGMA_CLASS
%token AX BX CX DX EX FX R0 R1 S0 S1
%token PLUS MINUS STAR DOT
%token ADD AND BSF BSR MOV

%type <TPRAGMA> list_of_pragma pragma_definition pragma
%type <TFUNCTION> list_of_asm_function asm_function
%type <TSTRING> asm_function_name label
%type <TREGISTER> c_register r_register s_register
%type <TEXPR> address expression expr_0 expr_1 expr_2 expr_3

%start code

%%

code
    : list_of_pragma                                    { asm.addPragma($1); }
      list_of_asm_function                              { asm.addFunctions($2); }
    ;

list_of_pragma
    : list_of_pragma pragma_definition                  { $$ = $1->add($2); }
    | pragma_definition                                 { $$ = $1; }
    ;

pragma_definition
    : pragma CHARACTER_STRING NEW_LINE                  { $$ = $1->setValue($2); }
    ;

pragma
    : PRAGMA_CLASS                                      { $$ = new PragmaClass(); }
    | PRAGMA_NAME                                       { $$ = new PragmaName(); }
    | PRAGMA_VERSION                                    { $$ = new PragmaVersion(); }
    ;

list_of_asm_function
    : list_of_asm_function asm_function                 { $$ = $1->add($2); }
    | asm_function                                      { $$ = $1; }
    ;

asm_function
    : asm_function_name list_of_command                 { $$ = new Function($1, $2); }
    ;

asm_function_name
    : DOT label NEW_LINE                                { $$ = $2; }
    ;

list_of_command
    : list_of_command asm_command_line
    | asm_command_line
    ;

asm_command_line
    : asm_command NEW_LINE
    ;

asm_command
    : label COLON
    | cmd_add
    | cmd_and
    
    | cmd_move
    ;

//--------------------------------------------

cmd_add
    : ADD address COMMA address
    ;

cmd_and
    : AND address COMMA address
    ;

cmd_bsf
    : BSF address COMMA address

cmd_bsr
    : BSR address COMMA address

cmd_move
    : MOV address COMMA address
    ;

//--------------------------------------------

label
    : ID                                                { $$ = std::string(yytext); }
    ;

address
    : expression                                        { $$ = new Expr($1, false); }
    | LSQUARE expression RSQUARE                        { $$ = new Expr($2, true); }
    ;

c_register
    : AX                                                { $$ = RegisterType::AX; }
    | BX                                                { $$ = RegisterType::BX; }
    | CX                                                { $$ = RegisterType::CX; }
    | DX                                                { $$ = RegisterType::DX; }
    | EX                                                { $$ = RegisterType::EX; }
    | FX                                                { $$ = RegisterType::FX; }
    ;

r_register
    : R0                                                { $$ = RegisterType::R0; }
    | R1                                                { $$ = RegisterType::R1; }
    ;

s_register
    : S0                                                { $$ = RegisterType::S0; }
    | S1                                                { $$ = RegisterType::S1; }
    ;

expression
    : expr_0                                            { $$ = $1; }
    ;

/*
    EXPRESSION

    0  +    Plus
       -    Minus

    1  *    Mulligan

    2  ()   Round brackets

    3  val  regs or number
*/
expr_0
    : expr_1                                            { $$ = $1; }
    | expr_0 PLUS  expr_1                               { $$ = new ExprPlus($1, $3); }
    | expr_0 MINUS expr_1                               { $$ = new ExprMinus($1, $3); }
    ;

expr_1
    : expr_2                                            { $$ = $1; }
    | expr_1 STAR expr_2                                { $$ = new ExprMul($1, $3); }
    ;

expr_2
    : expr_3                                            { $$ = $1; }
    | LROUND expr_0 RROUND                              { $$ = $2; }
    ;

expr_3
    : c_register                                        { $$ = new ExprRegister($1); }
    | r_register                                        { $$ = new ExprRegister($1); }
    | s_register                                        { $$ = new ExprRegister($1); }
    | NUMBER                                            { $$ = new ExprNumber(atol(yytext)); }
    ;

%%

#include "_moe.l.h"

void yyerror(const char *msg)
{
    char Str[1024] = {0};

    sprintf(Str,"%i: %s at or before '%s'.", yylineno, msg, yytext);
    CodeErrStr = Str;
}

int CompileFunction(const char *Func, char *Code)
{
    BCode      = Code;
    BCodePos   = 0;
    CodeErrStr = "";

    memset(BCode, 0, BCodeMaxLen);
    
    YY_BUFFER_STATE b = yy_scan_string(Func);
    yyparse();
    yy_delete_buffer(b);

    return CodeErrStr.empty();
}
