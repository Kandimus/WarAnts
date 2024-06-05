%{
#pragma warning(disable:4996)

#include <memory>
#include <string>

#include "stringex.h"

#include "code.h"
#include "expression.h"
#include "function.h"
#include "pragma.h"
#include "statement.h"
#include "stringNode.h"

#define UPD_LINENO {yyRealLineNo = yylineno;}

static std::shared_ptr<WarAnts::Asm::Code> yy_code;

/* For BISON */
extern int yylineno;
extern char *yytext;

int yyRealLineNo;

int16_t getIntNumber(const char* text);
int16_t getHexNumber(const char* text);
int16_t getDefine(const std::string& text);
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
    WarAnts::Asm::Function* TFUNCTION;
    WarAnts::Asm::Expression* TEXPR;
    WarAnts::Asm::Statement* TSTATETMENT;
    WarAnts::Asm::StringNode* TSTRING;
    int64_t TINEGER;
}

%token LROUND RROUND LSQUARE RSQUARE COMMA COLON DOT SIGN PERSENT LESS GREATER
%token INT_NUMBER HEX_NUMBER ID CHARACTER_STRING
%token NAME VERSION CLASS DEFINE CORE
%token R0 R1 R2 RC RF P0 P1 P2 COORD_X COORD_Y
%token PLUS MINUS STAR
%token ADD AND DEC DIV INC MOD MUL NEG NOT OR SUB XOR MIN MAX
%token BSF BSR BT BTR BTS BTC SHL SHR ROL ROR
%token EQ NEQ GT GE LT LE TEST
%token JMP JZ JNZ JT JF JO JNO JS JNS JCZ JCNZ LOOP CALL
%token MOV LEN DIST RET DBG MPSZ
%token LDRC LDFD LDEN LDAL
%token CIDL CMOV CATT CFD CTKF CEAT CCSL CCWR

%type <TPRAGMATYPE> pragma
%type <TPRAGMA> list_of_pragmas pragma_definition
%type <TFUNCTION> list_of_asm_functions asm_function asm_function_declaration
%type <TSTATETMENT> list_of_commands asm_command
%type <TSTRING> asm_function_name label quted_string
%type <TEXPR> address expr_0 expr_1 expr_2 expr_3
%type <TINEGER> number

%start asm_file

%%

asm_file
    : asm_code
    ;

asm_code
    : list_of_pragmas                                   { yy_code->m_pragma   = $1; }
      list_of_asm_functions                             { yy_code->m_function = $3; }
    ;

// pragmas
list_of_pragmas
    : list_of_pragmas pragma_definition                 { $$ = $1->add($2); }
    | pragma_definition                                 { $$ = $1; }
    ;

pragma_definition
    : persent { UPD_LINENO } pragma quted_string        { $$ = new WarAnts::Asm::Pragma($3, $4->get(), yy_code.get()); }
    ;

pragma
    : CLASS                                             { $$ = WarAnts::Asm::PragmaType::Class; }
    | NAME                                              { $$ = WarAnts::Asm::PragmaType::Name; }
    | VERSION                                           { $$ = WarAnts::Asm::PragmaType::Version; }
    | CORE                                              { $$ = WarAnts::Asm::PragmaType::Core; }
    ;

// defines
define_declaration
    : list_of_defines
    ;

list_of_defines
    : list_of_defines define_definition
    | define_definition
    ;

define_definition
    : sign DEFINE label number                          { yy_code->m_defines[$3->get()] = $4; }
    ;

// functions
list_of_asm_functions
    : list_of_asm_functions asm_function                { $$ = $1->add($2); }
    | asm_function                                      { $$ = $1; }
    ;

asm_function
    : define_declaration asm_function_declaration       { $$ = $2; }
    | asm_function_declaration                          { $$ = $1; }
    ;

asm_function_declaration
    : asm_function_name list_of_commands                { $$ = new WarAnts::Asm::Function($1, $2, yy_code.get()); }
    ;

asm_function_name
    : DOT { UPD_LINENO } label                          { $$ = $3; }
    ;

list_of_commands
    : list_of_commands asm_command                      { $$ = $1->add($2); }
    | asm_command                                       { $$ = $1; }
    ;

asm_command
    : label { UPD_LINENO } COLON                        { $$ = new WarAnts::Asm::Statement($1->get(), yy_code.get()); }

    // Arithmetic
    | ADD  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::ADD , $3,      $5, yy_code.get()); }
    | AND  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::AND , $3,      $5, yy_code.get()); }
    | DEC  { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::DEC , $3, nullptr, yy_code.get()); }
    | DIV  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::DIV , $3,      $5, yy_code.get()); }
    | INC  { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::INC , $3, nullptr, yy_code.get()); }
    | MOD  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MOD , $3,      $5, yy_code.get()); }
    | MUL  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MUL , $3,      $5, yy_code.get()); }
    | NEG  { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::NEG , $3, nullptr, yy_code.get()); }
    | NOT  { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::NOT , $3, nullptr, yy_code.get()); }
    | OR   { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::OR  , $3,      $5, yy_code.get()); }
    | SUB  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::SUB , $3,      $5, yy_code.get()); }
    | XOR  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::XOR , $3,      $5, yy_code.get()); }
    | MIN  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MIN , $3,      $5, yy_code.get()); }
    | MAX  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MAX , $3,      $5, yy_code.get()); }

    // Bit manipulation
    | BSF  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BSF , $3, $5, yy_code.get()); }
    | BSR  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BSR , $3, $5, yy_code.get()); }
    | BT   { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BT  , $3, $5, yy_code.get()); }
    | BTR  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BTR , $3, $5, yy_code.get()); }
    | BTS  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BTS , $3, $5, yy_code.get()); }
    | BTC  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BTC , $3, $5, yy_code.get()); }
    | SHL  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::SHL , $3, $5, yy_code.get()); }
    | SHR  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::SHR , $3, $5, yy_code.get()); }
    | ROL  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::ROL , $3, $5, yy_code.get()); }
    | ROR  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::ROR , $3, $5, yy_code.get()); }

    // Compare
    | EQ   { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::EQ  , $3, $5, yy_code.get()); }
    | NEQ  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::NEQ , $3, $5, yy_code.get()); }
    | GT   { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::GT  , $3, $5, yy_code.get()); }
    | GE   { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::GE  , $3, $5, yy_code.get()); }
    | LT   { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LT  , $3, $5, yy_code.get()); }
    | LE   { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LE  , $3, $5, yy_code.get()); }
    | TEST { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::TEST, $3, $5, yy_code.get()); }

    // Jump
    | JMP  { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JMP , $3->get(), yy_code.get()); }
    | JZ   { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JZ  , $3->get(), yy_code.get()); }
    | JNZ  { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JNZ , $3->get(), yy_code.get()); }
    | JT   { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JNZ , $3->get(), yy_code.get()); }
    | JF   { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JZ  , $3->get(), yy_code.get()); }
    | JO   { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JO  , $3->get(), yy_code.get()); }
    | JNO  { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JNO , $3->get(), yy_code.get()); }
    | JS   { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JS  , $3->get(), yy_code.get()); }
    | JNS  { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JNS , $3->get(), yy_code.get()); }
    | JCZ  { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JCZ , $3->get(), yy_code.get()); }
    | JCNZ { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JCNZ, $3->get(), yy_code.get()); }
    | LOOP { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LOOP, $3->get(), yy_code.get()); }
    | CALL { UPD_LINENO } label                         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CALL, $3->get(), yy_code.get()); }

    // Other
    | MOV  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MOV , $3, $5, yy_code.get()); }
    | LEN  { UPD_LINENO } address COMMA address         { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LEN , $3, $5, yy_code.get()); }
    | DIST { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::DIST, $3, nullptr, yy_code.get()); }
    | RET  { UPD_LINENO }                               { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::RET ,              yy_code.get()); }
    | DBG  { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::DBG , nullptr, $3, yy_code.get()); }
    | MPSZ { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MPSZ, $3, nullptr, yy_code.get()); }

    // Load data to memory
    | LDRC { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LDRC, nullptr, $3, yy_code.get()); }
    | LDFD { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LDFD, nullptr, $3, yy_code.get()); }
    | LDEN { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LDEN, nullptr, $3, yy_code.get()); }
    | LDAL { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LDAL, nullptr, $3, yy_code.get()); }

    // Commands
    | CIDL { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CIDL , nullptr, $3, yy_code.get()); }
    | CMOV { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CMOV , $3, nullptr, yy_code.get()); }
    | CATT { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CATT , $3, nullptr, yy_code.get()); }
    | CFD  { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CFD  , $3, nullptr, yy_code.get()); }
    | CTKF { UPD_LINENO } address                       { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CTKF , $3, nullptr, yy_code.get()); }
    | CEAT { UPD_LINENO }                               { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CEAT ,              yy_code.get()); }
    | CCSL { UPD_LINENO }                               { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CCSL ,              yy_code.get()); }
    | CCWR { UPD_LINENO }                               { $$ = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CCWR ,              yy_code.get()); }
    ;

//------------------------------------------------------

address
    : expr_3                                            { $$ = $1; }
    | P0                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::PReg(WarAnts::Asm::Register::P0X), yy_code.get()); }
    | P1                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::PReg(WarAnts::Asm::Register::P1X), yy_code.get()); }
    | P2                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::PReg(WarAnts::Asm::Register::P2X), yy_code.get()); }
    | LSQUARE expr_0 RSQUARE                            { $$ = new WarAnts::Asm::Expression($2, false, yy_code.get()); }
    | LESS expr_0 GREATER                               { $$ = new WarAnts::Asm::Expression($2, true,  yy_code.get()); }
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
    | expr_0 PLUS  expr_1                               { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Plus,  $1, $3, yy_code.get()); }
    | expr_0 MINUS expr_1                               { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Minus, $1, $3, yy_code.get()); }
    ;

expr_1
    : expr_2                                            { $$ = $1; }
    | expr_1 STAR expr_2                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Star, $1, $3, yy_code.get()); }
    ;

expr_2
    : expr_3                                            { $$ = $1; }
    | LROUND expr_0 RROUND                              { $$ = $2; }
    ;

expr_3
    : R0                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::R0),  yy_code.get()); }
    | R1                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::R1),  yy_code.get()); }
    | R2                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::R2),  yy_code.get()); }
    | RC                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::RC),  yy_code.get()); }
    | RF                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::RF),  yy_code.get()); }
    | P0 COLON COORD_X                                  { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P0X), yy_code.get()); }
    | P0 COLON COORD_Y                                  { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P0Y), yy_code.get()); }
    | P1 COLON COORD_X                                  { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P1X), yy_code.get()); }
    | P1 COLON COORD_Y                                  { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P1Y), yy_code.get()); }
    | P2 COLON COORD_X                                  { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P2X), yy_code.get()); }
    | P2 COLON COORD_Y                                  { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P2Y), yy_code.get()); }
    | number                                            { $$ = new WarAnts::Asm::Expression($1, yy_code.get()); }
    | label                                             { $$ = new WarAnts::Asm::Expression(getDefine($1->get()), yy_code.get()); }
    ;

number
    : INT_NUMBER                                        { $$ = getIntNumber(yytext); }
    | HEX_NUMBER                                        { $$ = getHexNumber(yytext); }
    ;

quted_string
    : CHARACTER_STRING                                  { $$ = new WarAnts::Asm::StringNode(yytext, yy_code.get()); }
    ;

label
    : ID                                                { $$ = new WarAnts::Asm::StringNode(yytext, yy_code.get()); }
    ;

sign
    : SIGN
    ;

persent
    : PERSENT
    ;

%%

#include "_antasm.l.h"

static int16_t getHexNumber(const char* text)
{
    unsigned int val = 0;
    std::string numbers = text;
    numbers = numbers.substr(0, numbers.size() - 1);

    if (!su::String_isValidHex(numbers.c_str(), val))
    {
        yy_code->m_errors.push_back(su::String_format2("%i: number '%s' is not hex val.", yylineno, yytext));
        return 0;
    }

    if (val > 0xffff)
    {
        yy_code->m_errors.push_back(su::String_format2("%i: number '%s' is not int16.", yylineno, yytext));
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
        yy_code->m_errors.push_back(su::String_format2("%i: number '%s' is not int16.", yylineno, yytext));
        return 0;
    }
    return static_cast<uint16_t>(val);
}

static void yyerror(const char *msg)
{
    yy_code->m_errors.push_back(su::String_format2("%i: %s at or before '%s'.", yylineno, msg, yytext));
}

int16_t getDefine(const std::string& text)
{
    if (yy_code->m_defines.find(text) == yy_code->m_defines.end())
    {
        yy_code->m_errors.push_back(su::String_format2("%i: '%s' is not defined", yylineno, text.c_str()));
        return 0;
    }
    return yy_code->m_defines[text];
}

namespace WarAnts
{
namespace Asm
{

std::shared_ptr<WarAnts::Asm::Code> yy_compile(const char *source)
{
    yy_code = std::make_shared<WarAnts::Asm::Code>();

    YY_BUFFER_STATE b = yy_scan_string(source);
    yyparse();
    yy_delete_buffer(b);

    return yy_code;
}

}; // namespace Asm
}; // namespace WarAnts
