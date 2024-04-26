%{
#pragma warning(disable:4996)

#include <string>

#include "stringex.h"

#include "code.h"
#include "expression.h"
#include "function.h"
#include "pragma.h"
#include "statetment.h"

namespace WarAnts
{
namespace Asm
{

std::string yy_errorString = "";

/* For BISON */
extern char *yytext;

int16_t getIntNumber(const char* text);
int16_t getHexNumber(const char* text);
void yy_error(const char *msg);
int  yylex();

};
};

%}

%union
{
    WarAnts::Asm::PragmaType TPRAGMATYPE;
    WarAnts::Asm::Pragma* TPRAGMA;
    WarAnts::Asm::Function* TFUNCTION;
    std::string TSTRING;
    WarAnts::Asm::Expression* TEXPR;
    WarAnts::Asm::Statetment* TSTATETMENT;
    WarAnts::Asm::Code* TCODE;
    int64_t TINEGER;
}

%token LROUND RROUND LSQUARE RSQUARE COMMA NEW_LINE COLON DOT
%token INT_NUMBER HEX_NUMBER ID CHARACTER_STRING
%token PRAGMA_NAME PRAGMA_VERSION PRAGMA_CLASS
%token R0 R1 R2 R3 RC RF IF IR
%token PLUS MINUS STAR
%token ADD AND BSF BSR MOV

%type <TPRAGMATYPE> pragma
%type <TPRAGMA> list_of_pragma pragma_definition
%type <TFUNCTION> list_of_asm_function asm_function
%type <TSTATETMENT> list_of_command asm_command_line asm_command
%type <TSTRING> asm_function_name label quted_string
%type <TEXPR> address expression expr_0 expr_1 expr_2 expr_3
%type <TCODE> code
%type <TINEGER> number

%start code

%%

code
    : list_of_pragma list_of_asm_function               { $$ = new Code($1, $2); }
    ;

list_of_pragma
    : list_of_pragma pragma_definition                  { $$ = $1->add($2); }
    | pragma_definition                                 { $$ = $1; }
    ;

pragma_definition
    : pragma quted_string NEW_LINE                      { $$ = new Pragma($1, $2); }
    ;

pragma
    : PRAGMA_CLASS                                      { $$ = PragmaType::Class; }
    | PRAGMA_NAME                                       { $$ = PragmaType::Name; }
    | PRAGMA_VERSION                                    { $$ = PragmaType::Version; }
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
    : list_of_command asm_command_line                  { $$ = $1->add($2); }
    | asm_command_line                                  { $$ = $1; }
    ;

asm_command_line
    : asm_command NEW_LINE                              { $$ = $1; }
    ;

asm_command
    : label COLON                                       { $$ = new Statetment($1); }

    // Arithmetic
    | ADD address COMMA address                         { $$ = new Statetment(WarAnts::Asm::AsmCommand::ADD, $2, $4); }
    | AND address COMMA address                         { $$ = new Statetment(WarAnts::Asm::AsmCommand::AND, $2, $4); }

    // Bit manipulation
    | BSF address COMMA address                         { $$ = new Statetment(WarAnts::Asm::AsmCommand::BSF, $2, $4); }
    | BSR address COMMA address                         { $$ = new Statetment(WarAnts::Asm::AsmCommand::BSR, $2, $4); }

    | MOV address COMMA address                         { $$ = new Statetment(WarAnts::Asm::AsmCommand::MOV, $2, $4); }
    ;

//--------------------------------------------

quted_string
    : CHARACTER_STRING                                  { $$ = std::string(yytext); }
    ;

label
    : ID                                                { $$ = std::string(yytext); }
    ;

address
    : expression                                        { $$ = $1; }
    | LSQUARE expression RSQUARE                        { $$ = new Expression($2); }
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
    | expr_0 PLUS  expr_1                               { $$ = new Expression(OperandType::Plus, $1, $3); }
    | expr_0 MINUS expr_1                               { $$ = new Expression(OperandType::Minus, $1, $3); }
    ;

expr_1
    : expr_2                                            { $$ = $1; }
    | expr_1 STAR expr_2                                { $$ = new Expression(OperandType::Star, $1, $3); }
    ;

expr_2
    : expr_3                                            { $$ = $1; }
    | LROUND expr_0 RROUND                              { $$ = $2; }
    ;

expr_3
    : R0                                                { $$ = new Expression(RegisterType::R0); }
    | R1                                                { $$ = new Expression(RegisterType::R1); }
    | R2                                                { $$ = new Expression(RegisterType::R2); }
    | R3                                                { $$ = new Expression(RegisterType::R3); }
    | RC                                                { $$ = new Expression(RegisterType::RC); }
    | RF                                                { $$ = new Expression(RegisterType::RF); }
    | IF                                                { $$ = new Expression(RegisterType::IF); }
    | IR                                                { $$ = new Expression(RegisterType::IR); }
    | number                                            { $$ = new Expression($1); }
    ;

number
    : INT_NUMBER                                        { $$ = getIntNumber(yytext); }
    | HEX_NUMBER                                        { $$ = getHexNumber(yytext); }
    ;

%%

namespace WarAnts
{
namespace Asm
{
#include "_antasm.l.h"

int16_t getHexNumber(const char* text)
{
    unsigned int val = 0;

    if (!su::String_isValidHex(text, val))
    {
        yy_errorString += su::String_format2("%i: number '%s' is not hex val.", yylineno, yytext);
        return 0;
    }

    if (val > 0xffff)
    {
        yy_errorString += su::String_format2("%i: number '%s' is not int16.", yylineno, yytext);
        return 0;
    }

    uint16_t val16 = static_cast<uint16_t>(val);
    return *(int16_t*)&val16;
}

int16_t getIntNumber(const char* text)
{
    int64_t val = atol(text);

    if (val < -32668 || val > 32767)
    {
        yy_errorString += su::String_format2("%i: number '%s' is not int16.", yylineno, yytext);
        return 0;
    }
    return static_cast<uint16_t>(val);
}

void yy_error(const char *msg)
{
    yy_errorString += su::String_format2("%i: %s at or before '%s'.", yylineno, msg, yytext);
}

Code* yy_compile(const char *Func)
{
    CodeErrStr = "";

    memset(BCode, 0, BCodeMaxLen);
    
    YY_BUFFER_STATE b = yy_scan_string(Func);
    yyparse();
    yy_delete_buffer(b);

    return CodeErrStr.empty();
}

}; // namespace Asm
}; // namespace WarAnts
