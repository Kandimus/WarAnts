%{
#pragma warning(disable:4996)

#include <memory>
#include <string>

#include "stringex.h"

#include "code.h"
#include "expression.h"
#include "function.h"
#include "pragma.h"
#include "statetment.h"
#include "stringNode.h"

static std::shared_ptr<WarAnts::Asm::Code> yy_code;

/* For BISON */
extern char *yytext;

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
    WarAnts::Asm::Statetment* TSTATETMENT;
    WarAnts::Asm::StringNode* TSTRING;
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
%type <TFUNCTION> list_of_asm_functions asm_function asm_function_declaration
%type <TSTATETMENT> list_of_commands asm_command_line asm_command
%type <TSTRING> asm_function_name label quted_string
%type <TEXPR> address expr_0 expr_1 expr_2 expr_3
%type <TINEGER> number

%start asm_file

%%

asm_file
    : newline asm_code
    | asm_code
    ;

asm_code
    : list_of_pragmas                                   { yy_code->m_pragma = $1; printf("add pragma list\n"); }
      list_of_asm_functions                             { yy_code->m_function = $3; printf("add funct list\n"); }
    ;

list_of_pragmas
    : list_of_pragmas pragma_definition                 { $$ = $1->add($2); }
    | pragma_definition                                 { $$ = $1; }
    ;

pragma_definition
    : pragma quted_string newline                       { $$ = new WarAnts::Asm::Pragma($1, $2->get(), yy_code.get()); }
    ;

pragma
    : PRAGMA_CLASS                                      { $$ = WarAnts::Asm::PragmaType::Class; }
    | PRAGMA_NAME                                       { $$ = WarAnts::Asm::PragmaType::Name; }
    | PRAGMA_VERSION                                    { $$ = WarAnts::Asm::PragmaType::Version; }
    ;

define_declaration
    : list_of_defines
    ;

list_of_defines
    : list_of_defines define_definition
    | define_definition
    ;

define_definition
    : PRAGMA_DEFINE label number newline                { yy_code->m_defines[$2->get()] = $3; printf("define %s = %i\n", $2->get().c_str(), $3); }
    ;

list_of_asm_functions
    : list_of_asm_functions asm_function                { $$ = $1->add($2); printf("list_of_asm_functions\n"); }
    | asm_function                                      { $$ = $1; printf("asm_function\n"); }
    ;

asm_function
    : define_declaration asm_function_declaration          { $$ = $2; }
    | asm_function_declaration                          { $$ = $1; }
    ;

asm_function_declaration
    : asm_function_name list_of_commands                { $$ = new WarAnts::Asm::Function($1->get(), $2, yy_code.get()); }
    ;

asm_function_name
    : DOT label newline                                 { $$ = $2; printf("Found function '%s'\n", $2->get().c_str()); }
    ;

list_of_commands
    : list_of_commands asm_command_line                 { $$ = $1->add($2); }
    | asm_command_line                                  { $$ = $1; }
    ;

asm_command_line
    : asm_command newline                               { $$ = $1; }
    ;

asm_command
    : label COLON                                       { $$ = new WarAnts::Asm::Statetment($1->get(), yy_code.get()); }

    // Arithmetic
    | ADD  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ADD , $2, $4, yy_code.get()); }
    | AND  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::AND , $2, $4, yy_code.get()); }
    | DEC  address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::DEC , $2,     yy_code.get()); }
    | DIV  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::DIV , $2, $4, yy_code.get()); }
    | INC  address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::INC , $2,     yy_code.get()); }
    | MOD  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MOD , $2, $4, yy_code.get()); }
    | MUL  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MUL , $2, $4, yy_code.get()); }
    | NEG  address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NEG , $2,     yy_code.get()); }
    | NOT  address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NOT , $2,     yy_code.get()); }
    | OR   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::OR  , $2, $4, yy_code.get()); }
    | SUB  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SUB , $2, $4, yy_code.get()); }
    | XOR  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::XOR , $2, $4, yy_code.get()); }
    | MIN  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MIN , $2, $4, yy_code.get()); }
    | MAX  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MAX , $2, $4, yy_code.get()); }

    // Bit manipulation
    | BSF  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BSF , $2, $4, yy_code.get()); }
    | BSR  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BSR , $2, $4, yy_code.get()); }
    | BT   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BT  , $2, $4, yy_code.get()); }
    | BTR  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTR , $2, $4, yy_code.get()); }
    | BTS  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTS , $2, $4, yy_code.get()); }
    | BTC  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTC , $2, $4, yy_code.get()); }
    | SHL  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SHL , $2, $4, yy_code.get()); }
    | SHR  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SHR , $2, $4, yy_code.get()); }
    | ROL  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ROL , $2, $4, yy_code.get()); }
    | ROR  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ROR , $2, $4, yy_code.get()); }

    // Compare
    | EQ   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::EQ  , $2, $4, yy_code.get()); }
    | NEQ  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NEQ , $2, $4, yy_code.get()); }
    | GT   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::GT  , $2, $4, yy_code.get()); }
    | GE   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::GE  , $2, $4, yy_code.get()); }
    | LT   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LT  , $2, $4, yy_code.get()); }
    | LE   address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LE  , $2, $4, yy_code.get()); }
    | TEST address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::TEST, $2, $4, yy_code.get()); }

    // Jump
    | JMP  label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JMP , $2->get(), yy_code.get()); }
    | JZ   label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JZ  , $2->get(), yy_code.get()); }
    | JNZ  label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JNZ , $2->get(), yy_code.get()); }
    | JO   label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JO  , $2->get(), yy_code.get()); }
    | JNO  label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JNO , $2->get(), yy_code.get()); }
    | JCZ  label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JCZ , $2->get(), yy_code.get()); }
    | JCNZ label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JCNZ, $2->get(), yy_code.get()); }
    | LOOP label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LOOP, $2->get(), yy_code.get()); }

    // Other
    | MOV  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MOV , $2, $4, yy_code.get()); }
    | CALL label                                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CALL, $2->get(), yy_code.get()); }
    | LEN  address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LEN , $2, $4, yy_code.get()); }
    | EXIT                                              { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::EXIT, yy_code.get()); }

    // Load data to memory
    | LDTR address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDTR, $2, yy_code.get()); }
    | LDFD address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDFD, $2, yy_code.get()); }
    | LDEN address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDEN, $2, yy_code.get()); }
    | LDFR address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDFR, $2, yy_code.get()); }

    // Commands
    | CIDL address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CIDL , $2,     yy_code.get()); }
    | CMOV address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CMOV , $2, $4, yy_code.get()); }
    | CATT address COMMA address                        { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CATT , $2, $4, yy_code.get()); }
    | CTKF  address COMMA address                       { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CTKF , $2, $4, yy_code.get()); }
    | CGVF  address COMMA address                       { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CGVF , $2, $4, yy_code.get()); }
    | CEAT address                                      { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CEAT , $2,     yy_code.get()); }
    | CPS                                               { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CPS  ,         yy_code.get()); }
    | CPW                                               { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CPW  ,         yy_code.get()); }

    | NOP                                               { $$ = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NOP  ,         yy_code.get()); }
    ;

//------------------------------------------------------

address
    : expr_0                                            { $$ = $1; }
    | LSQUARE expr_0 RSQUARE                            { $$ = new WarAnts::Asm::Expression($2, yy_code.get()); }
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
    : R0                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R0, yy_code.get()); }
    | R1                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R1, yy_code.get()); }
    | R2                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R2, yy_code.get()); }
    | R3                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R3, yy_code.get()); }
    | RC                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::RC, yy_code.get()); }
    | RF                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::RF, yy_code.get()); }
    | IF                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::IF, yy_code.get()); }
    | IR                                                { $$ = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::IR, yy_code.get()); }
    | number                                            { $$ = new WarAnts::Asm::Expression($1, yy_code.get()); }
    | label                                             { $$ = new WarAnts::Asm::Expression(getDefine($1->get()), yy_code.get()); }
    ;

number
    : INT_NUMBER                                        { $$ = getIntNumber(yytext); }
    | HEX_NUMBER                                        { $$ = getHexNumber(yytext); }
    ;

newline
    : NEW_LINE
    ;

quted_string
    : CHARACTER_STRING                                  { $$ = new WarAnts::Asm::StringNode(yytext, yy_code.get()); }
    ;

label
    : ID                                                { $$ = new WarAnts::Asm::StringNode(yytext, yy_code.get()); }
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
