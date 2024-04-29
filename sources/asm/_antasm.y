%{
#pragma warning(disable:4996)

#include <string>

#include "stringex.h"

#include "code.h"
#include "expression.h"
#include "function.h"
#include "pragma.h"
#include "statetment.h"

static std::string yy_errorString = "";
static WarAnts::Asm::Code* yy_result = nullptr;

/* For BISON */
extern char *yytext;

int16_t getIntNumber(const char* text);
int16_t getHexNumber(const char* text);
void yyerror(const char *msg);

int  yylex();

#pragma warning(disable:4065)
#pragma warning(disable:4244)
#pragma warning(disable:5033)

%}

%union
{
    WarAnts::Asm::PragmaType TPRAGMATYPE;
    WarAnts::Asm::Pragma* TPRAGMA;
    WarAnts::Asm::Define* TDEFINE;
    WarAnts::Asm::Function* TFUNCTION;
    WarAnts::Asm::Expression* TEXPR;
    WarAnts::Asm::Statetment* TSTATETMENT;
    WarAnts::Asm::Code* TCODE;
    std::string* TSTRING;
    int64_t TINEGER;
}

%token LROUND RROUND LSQUARE RSQUARE COMMA NEW_LINE COLON DOT
%token INT_NUMBER HEX_NUMBER ID CHARACTER_STRING
%token PRAGMA_NAME PRAGMA_VERSION PRAGMA_CLASS PRAGMA_DEFINE
%token R0 R1 R2 R3 RC RF IF IR
%token PLUS MINUS STAR
%token ADD AND DEC DIV INC MOD MUL NEG NOT OR SUB XOR MIN MAX
%token BSF BSR BT BTR BTS BTC SHL SHR ROL ROR
%token EQ NEQ GT GE LT LE TEST
%token JMP JZ JNZ JO JNO JCZ JCNZ LOOP
%token MOV CALL LEN EXIT
%token LDTR LDFD LDEN LDFR
%token CIDL CMOV CATT CTKF CGVF CEAT CPS CPW
%token NOP

%type <TPRAGMATYPE> pragma
%type <TPRAGMA> list_of_pragmas pragma_definition
%type <TDEFINE> list_of_defines define_declaration
%type <TFUNCTION> list_of_asm_functions asm_function
%type <TSTATETMENT> list_of_commands asm_command_line asm_command
%type <TSTRING> asm_function_name label quted_string
%type <TEXPR> address expression expr_0 expr_1 expr_2 expr_3
%type <TCODE> code
%type <TINEGER> number

%start code

%%

code
    : list_of_pragmas
      list_of_defines
      list_of_asm_functions                             { $$ = yy_result = new WarAnts::Asm::Code($1, $2, $3); }
    ;

list_of_pragmas
    : list_of_pragmas pragma_definition                 { $$ = $1->add($2); }
    | pragma_definition                                 { $$ = $1; }
    ;

pragma_definition
    : pragma quted_string NEW_LINE                      { $$ = new WarAnts::Asm::Pragma($1, *$2); delete $2; }
    ;

pragma
    : PRAGMA_CLASS                                      { $$ = WarAnts::Asm::PragmaType::Class; }
    | PRAGMA_NAME                                       { $$ = WarAnts::Asm::PragmaType::Name; }
    | PRAGMA_VERSION                                    { $$ = WarAnts::Asm::PragmaType::Version; }
    ;

list_of_defines
    : list_of_defines define_declaration                { $$ = $1->add($2); }
    | define_declaration                                { $$ = $1; }
    ;

define_declaration
    : PRAGMA_DEFINE label number NEW_LINE               { $$ = new WarAnts::Asm::Define(*$2, $3); delete $2; }
    |                                                   { $$ = nullptr; }
    ;

list_of_asm_functions
    : list_of_asm_functions asm_function                { $$ = $1->add($2); }
    | asm_function                                      { $$ = $1; }
    ;

asm_function
    : asm_function_name list_of_commands                { $$ = new WarAnts::Asm::Function(*$1, $2); delete $1; }
    ;

asm_function_name
    : DOT label NEW_LINE                                { $$ = $2; }
    ;

list_of_commands
    : list_of_commands asm_command_line                 { $$ = $1->add($2); }
    | asm_command_line                                  { $$ = $1; }
    ;

asm_command_line
    : asm_command NEW_LINE                              { $$ = $1; }
    ;

asm_command
    : label COLON                                       { $$ = new WarAnts::Asm::Statetment(*$1); delete $1;}

    // Arithmetic
    | ADD  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ADD , $2, $4); }
    | AND  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::AND , $2, $4); }
    | DEC  address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::DEC , $2, nullptr); }
    | DIV  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::DIV , $2, $4); }
    | INC  address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::INC , $2, nullptr); }
    | MOD  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MOD , $2, $4); }
    | MUL  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MUL , $2, $4); }
    | NEG  address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NEG , $2, nullptr); }
    | NOT  address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NOT , $2, nullptr); }
    | OR   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::OR  , $2, $4); }
    | SUB  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SUB , $2, $4); }
    | XOR  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::XOR , $2, $4); }
    | MIN  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MIN , $2, $4); }
    | MAX  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MAX , $2, $4); }

    // Bit manipulation
    | BSF  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BSF , $2, $4); }
    | BSR  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BSR , $2, $4); }
    | BT   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BT  , $2, $4); }
    | BTR  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTR , $2, $4); }
    | BTS  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTS , $2, $4); }
    | BTC  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTC , $2, $4); }
    | SHL  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SHL , $2, $4); }
    | SHR  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SHR , $2, $4); }
    | ROL  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ROL , $2, $4); }
    | ROR  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ROR , $2, $4); }

    // Compare
    | EQ   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::EQ  , $2, $4); }
    | NEQ  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NEQ , $2, $4); }
    | GT   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::GT  , $2, $4); }
    | GE   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::GE  , $2, $4); }
    | LT   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LT  , $2, $4); }
    | LE   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LE  , $2, $4); }
    | TEST address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::TEST, $2, $4); }

    // Jump
    | JMP  label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JMP , $2); }
    | JZ   label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JZ  , $2); }
    | JNZ  label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JNZ , $2); }
    | JO   label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JO  , $2); }
    | JNO  label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JNO , $2); }
    | JCZ  label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JCZ , $2); }
    | JCNZ label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JCNZ, $2); }
    | LOOP label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LOOP, $2); }

    // Other
    | MOV  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MOV , $2, $4); }
    | CALL label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CALL, $2); }
    | LEN  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LEN , $2, $4); }
    | EXIT                                              { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::EXIT, nullptr, nullptr); }

    // Load data to memory
    | LDTR address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDTR, $2, nullptr); }
    | LDFD address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDFD, $2, nullptr); }
    | LDEN address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDEN, $2, nullptr); }
    | LDFR address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDFR, $2, nullptr); }

    // Commands
    | CIDL address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CIDL , $2, nullptr); }
    | CMOV address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CMOV , $2, $4); }
    | CATT address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CATT , $2, $4); }
    | CTKF  address COMMA address                       { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CTKF , $2, $4); }
    | CGVF  address COMMA address                       { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CGVF , $2, $4); }
    | CEAT address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CEAT , $2, nullptr); }
    | CPS                                               { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CPS  , nullptr, nullptr); }
    | CPW                                               { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CPW  , nullptr, nullptr); }

    | NOP                                               { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NOP  , nullptr, nullptr); }
    ;

//------------------------------------------------------

quted_string
    : CHARACTER_STRING                                  { $$ = new std::string(yytext); }
    ;

label
    : ID                                                { $$ = new std::string(yytext); }
    ;

address
    : expression                                        { $$ = $1; }
    | LSQUARE expression RSQUARE                        { $$ = new WarAnts::Asm::Expression($2); }
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
    | expr_0 PLUS  expr_1                               { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Plus, $1, $3); }
    | expr_0 MINUS expr_1                               { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Minus, $1, $3); }
    ;

expr_1
    : expr_2                                            { $$ = $1; }
    | expr_1 STAR expr_2                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Star, $1, $3); }
    ;

expr_2
    : expr_3                                            { $$ = $1; }
    | LROUND expr_0 RROUND                              { $$ = $2; }
    ;

expr_3
    : R0                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R0); }
    | R1                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R1); }
    | R2                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R2); }
    | R3                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R3); }
    | RC                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::RC); }
    | RF                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::RF); }
    | IF                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::IF); }
    | IR                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::IR); }
    | number                                            { $$ = new WarAnts::Asm::Expression($1); }
    | label                                             { $$ = new WarAnts::Asm::Expression($1); }
    ;

number
    : INT_NUMBER                                        { $$ = getIntNumber(yytext); }
    | HEX_NUMBER                                        { $$ = getHexNumber(yytext); }
    ;

%%

#include "_antasm.l.h"

static int16_t getHexNumber(const char* text)
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

static int16_t getIntNumber(const char* text)
{
    int64_t val = atol(text);

    if (val < -32668 || val > 32767)
    {
        yy_errorString += su::String_format2("%i: number '%s' is not int16.", yylineno, yytext);
        return 0;
    }
    return static_cast<uint16_t>(val);
}

static void yyerror(const char *msg)
{
    yy_errorString += su::String_format2("%i: %s at or before '%s'.", yylineno, msg, yytext);
}


namespace WarAnts
{
namespace Asm
{

Code* yy_compile(const char *Func, std::string& outError)
{
    yy_errorString = "";

    YY_BUFFER_STATE b = yy_scan_string(Func);
    yyparse();
    yy_delete_buffer(b);

    outError = yy_errorString;

    return yy_result;
}

}; // namespace Asm
}; // namespace WarAnts
