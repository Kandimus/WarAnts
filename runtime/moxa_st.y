%{
#include "Defines.h"
#include "Reg.h"
#include "Stat.h"
#include "Expr.h"

//#define YYDEBUG 1
#define YYPRINT
//#define YYERROR_VERBOSE

#define CHECK_ERROR          if(GetError()) YYABORT;
#define FREE(x)              free((void *)x)

%}

%union
{
  rReg  *REG;
  rExpr *EXPR;
  rStat *STAT;
  char  *STR;
}

%token _BY_ _CASE_ _DO_ _ELSE_ _ELSIF_ _END_CASE_ _END_FOR_ _END_IF_ _END_REPEAT_ _END_VAR_ _END_WHILE_
%token _RETURN_ _FOR_ _IF_ _OF_ _REPEAT_ _THEN_ _TO_ _VAR_ _UNTIL_ _WHILE_ _EXIT_ _VAR_REF_ _END_VAR_REF_

%token  _WORD_TO_INT_    _WORD_TO_DWORD_   _WORD_TO_LONG_    _WORD_TO_REAL_   _WORD_TO_BOOL_
%token   _INT_TO_WORD_    _INT_TO_DWORD_    _INT_TO_LONG_     _INT_TO_REAL_    _INT_TO_BOOL_
%token _DWORD_TO_WORD_  _DWORD_TO_INT_    _DWORD_TO_LONG_   _DWORD_TO_REAL_  _DWORD_TO_BOOL_
%token  _LONG_TO_WORD_   _LONG_TO_INT_     _LONG_TO_DWORD_   _LONG_TO_REAL_   _LONG_TO_BOOL_
%token  _REAL_TO_WORD_   _REAL_TO_INT_     _REAL_TO_LONG_    _REAL_TO_DWORD_  _REAL_TO_BOOL_
%token  _BOOL_TO_WORD_   _BOOL_TO_INT_     _BOOL_TO_DWORD_   _BOOL_TO_LONG_   _BOOL_TO_REAL_

%token _UNSINGED_INT_ _REALNUMBER_ _ID_ _DIGHEX_ _TRUE_ _FALSE_

%token _OR_ _AND_ _BOR_ _BAND_ _MOD_ _NOT_ _GE_ _GT_ _LE_ _LT_ _NEQUAL_ _EQUAL_ _ASSIGN_ _MINUS_ _PLUS_ _BINV_
%token _SLASH_ _STAR_ _POW_ _DOT_ _SEMICOLON_ _COLON_ _COMMA_ _XOR_
%token _LBRACKET_ _RBRACKET_ _LBRACE_ _RBRACE_ _LPAREN_ _RPAREN_ 

%token _REG_
%token _SET_REG_ _SET_REG_3X_ _SET_REG_4X_
%token _GET_REG_ _GET_REG_3X_ _GET_REG_4X_ _GET_REG_SYS_
%token _COPY_ _COPY_33_ _COPY_34_ _COPY_43_ _COPY_44_
%token _RAND_ _LN_ _LOG_ _SQRT_ _ABS_ _ODD_ _SGN_ _SIN_ _ATN_ _COS_ _EXP_ _FIX_ _INT_ _TAN_ _ROUND_
%token _SAVE_DUMP_ _DELETE_DUMP_ _COPY_DUMP_
%token _CREATEUTIME_ _CHECK_STORAGE_


%type <STAT> stat_list
%type <STAT> stat
%type <STAT> assign_stat
%type <STAT> if_stat elseif_list elseif_stat
%type <STAT> func_stat
//%type <STAT> for_stat
//%type <STAT> case_stat case_list case_decl case_else
//%type <STAT> while_stat
//%type <STAT> repeat_stat

%type <REG> reg_access
%type <REG> reg_number

%type <STR>  identifier

%type <EXPR> expr
%type <EXPR> expr1
%type <EXPR> expr2
%type <EXPR> expr3
%type <EXPR> expr4
%type <EXPR> expr5
%type <EXPR> expr6
%type <EXPR> expr7
%type <EXPR> expr8
%type <EXPR> expr9
%type <EXPR> expr10
%type <EXPR> expr11
%type <EXPR> constant
%type <EXPR> internal_func


%%

script
	: var_part stat_part
	;


//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Доступ к регистру, через переменную или номер регистра
//
//////////////////////////////////////////////////////////////////////////////////////////////////
reg_number
	: _REG_                                       { $$ = new rReg(st_Reg);                   CHECK_ERROR; }
	| _REG_ _DOT_ _UNSINGED_INT_                  { $$ = new rReg(st_Reg, stToInt(st_text)); CHECK_ERROR; }
	; 

identifier
	: _ID_                                        { $$ = strdup(st_text);                    CHECK_ERROR; }
	;

reg_access
	: reg_number
	| identifier                                  { $$ = new rReg($1); FREE($1);             CHECK_ERROR; }
	;



//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Секция описания ссылок на регистры (переменные)
// 
//////////////////////////////////////////////////////////////////////////////////////////////////

var_part
	: _VAR_REF_ var_list _END_VAR_REF_
	|
	;

var_list
	: var_list var_def
	| var_def
	;

var_def
	: identifier _COLON_ reg_number sep           { AddVarRef($1, $3); CHECK_ERROR; }
	;


/**************************************************************************************************/
/** Описание блока ********************************************************************************/
/**************************************************************************************************/


stat_part
	: stat_list                                   { st_RootStat = $1; CHECK_ERROR; }
	|                                             
	;

stat_list
	: stat_list stat                              { $$ = $1->Add($2); CHECK_ERROR; }
	| stat                                        { $$ = $1;          CHECK_ERROR; }
	;

stat
  	: assign_stat sep
	| if_stat sep
//	| for_stat sep
//	| case_stat sep
//	| while_stat sep
//	| repeat_stat sep
	| func_stat sep                               
	| _RETURN_ sep                                { $$ = new rStatReturn();   CHECK_ERROR; }
	;


//-------------------------------------------------------------------------------------------------
// IF..THEN..ELSIF..THEN..ELSE..END_IF
if_stat
	: _IF_ expr _THEN_ stat_list _END_IF_         { $$ = new rStatIf($2, $4, NULL, NULL); CHECK_ERROR; }
	| _IF_ expr _THEN_ stat_list
	  _ELSE_ stat_list _END_IF_                   { $$ = new rStatIf($2, $4, NULL,   $6); CHECK_ERROR; }
	| _IF_ expr _THEN_ stat_list elseif_list
	  _END_IF_                                    { $$ = new rStatIf($2, $4,   $5, NULL); CHECK_ERROR; }
	| _IF_ expr _THEN_ stat_list elseif_list
	  _ELSE_ stat_list  _END_IF_                  { $$ = new rStatIf($2, $4,   $5,   $7); CHECK_ERROR; }
	;

elseif_list
	: elseif_list elseif_stat                     { $$ = ((rStatIf *)$1)->AddElse($2); CHECK_ERROR; }
	| elseif_stat                                 { $$ = $1;                           CHECK_ERROR; }
	;	

elseif_stat
	: _ELSIF_ expr _THEN_ stat_list               { $$ = new rStatIf($2, $4); CHECK_ERROR; }
	;


//-------------------------------------------------------------------------------------------------
// CASE..OF..END_CASE
//? Доделать с "1,3,5..8"
//case_stat
//	: _CASE_ expr _OF_
//	  case_list case_else _END_CASE_              { $$ = new rStatCase($2, (rStatIf *)$4, $5); CHECK_ERROR; }
//	;
//
//case_list
//	: case_list case_decl                         { $$ = ((rStatIf *)$1)->AddElse($2); CHECK_ERROR; }
//	| case_decl                                   { $$ = $1;                           CHECK_ERROR; }
//	;
//
//case_decl
//?	: int_list _COLON_ stat_list                  { $$ = new rStatIf(
//	: integer _COLON_ stat_list                   { $$ = new rStatIf(new rExpr($1), $3); CHECK_ERROR; }
//	;
//
//int_list
//	: int_list _COMMA_ integer
// | integer .. integer
//	| integer
//	;
//
//case_else
//	: _ELSE_ stat_list                            { $$ = $2;   CHECK_ERROR; }
//	|                                             { $$ = NULL; CHECK_ERROR; }
//	;


//-------------------------------------------------------------------------------------------------
// FOR..TO..BY..DO..END_FOR
//for_stat
//	: _FOR_ var_access _ASSIGN_ expr
//	  _TO_ expr by_stat _DO_ stat_list
//	  _END_FOR_                                   { $$ = new rStatFor($2, $4, $6, $7, $9); CHECK_ERROR; }
//	;

//by_stat
//	: _BY_ expr                                   { $$ = $2; CHECK_ERROR;           }
//	|                                             { $$ = new rExpr(1); CHECK_ERROR; }
//	;


//-------------------------------------------------------------------------------------------------
// WHILE..DO..END_WHILE
//while_stat
//	: _WHILE_ expr _DO_ stat_list _END_WHILE_     { $$ = new rStatWhile(true, $2, $4); CHECK_ERROR; }
//	;


//-------------------------------------------------------------------------------------------------
// REPEAT..UNTIL..END_REPEAT
//repeat_stat
//	: _REPEAT_ stat_list _UNTIL_
//	  expr _END_REPEAT_                           { $$ U= new rStatWhile(false, $4, $2); CHECK_ERROR; }
//	;


//-------------------------------------------------------------------------------------------------
// .. := ..
assign_stat
	: reg_access _ASSIGN_ expr                    { $$ = new rStatAssign($1, $3); CHECK_ERROR; }
	;



//-------------------------------------------------------------------------------------------------
// ФУНКЦИИ И ПРОЦЕДУРЫ
func_stat
	: _SET_REG_ _LPAREN_ expr _COMMA_ expr
	  _COMMA_ expr _RPAREN_                       { $$ = new rStatSetReg($3, $5, $7); CHECK_ERROR; }
	| _SET_REG_3X_ _LPAREN_ expr _COMMA_
	  expr _RPAREN_                               { $$ = new rStatSetReg((BYTE)false, $3, $5); CHECK_ERROR; }
	| _SET_REG_4X_ _LPAREN_ expr _COMMA_
	  expr _RPAREN_                               { $$ = new rStatSetReg((BYTE)true, $3, $5); CHECK_ERROR; }
	| _COPY_ _LPAREN_ expr _COMMA_ expr _COMMA_
	  expr _COMMA_ expr _COMMA_ expr _RPAREN_     { $$ = new rCopy($3, $5, $7, $9, $11); CHECK_ERROR; } 
	| _COPY_33_ _LPAREN_ expr _COMMA_ expr
	  _COMMA_ expr _RPAREN_                       { $$ = new rCopy(new rExpr(0, STT_BOOL), $3, new rExpr(0, STT_BOOL), $5, $7); CHECK_ERROR; } 
	| _COPY_34_ _LPAREN_ expr _COMMA_ expr
	  _COMMA_ expr _RPAREN_                       { $$ = new rCopy(new rExpr(0, STT_BOOL), $3, new rExpr(1, STT_BOOL), $5, $7); CHECK_ERROR; }
	| _COPY_43_ _LPAREN_ expr _COMMA_ expr
	  _COMMA_ expr _RPAREN_                       { $$ = new rCopy(new rExpr(1, STT_BOOL), $3, new rExpr(0, STT_BOOL), $5, $7); CHECK_ERROR; } 
	| _COPY_44_ _LPAREN_ expr _COMMA_ expr
	  _COMMA_ expr _RPAREN_                       { $$ = new rCopy(new rExpr(1, STT_BOOL), $3, new rExpr(1, STT_BOOL), $5, $7); CHECK_ERROR; } 
	| _SAVE_DUMP_ _LPAREN_ expr _COMMA_ expr
	  _COMMA_ expr _COMMA_ expr _COMMA_ expr
	  _RPAREN_                                    { $$ = new rSaveDump($3, $5, $7, $9, $11); CHECK_ERROR; }
	| _DELETE_DUMP_ _LPAREN_ expr _COMMA_ expr
	  _COMMA_ expr _RPAREN_                       { $$ = new rDeleteDump($3, $5, $7); CHECK_ERROR; }
	| _COPY_DUMP_ _LPAREN_ expr _COMMA_ expr
	  _COMMA_ expr _RPAREN_                       { $$ = new rCopyDump($3, $5, $7); CHECK_ERROR; }
	;



/**************************************************************************************************/
/** ВЫРАЖЕНИЯ                                                                                    **/
/**                                                                                              **/
/**   0  OR   Логическое ИЛИ                                                                     **/
/**   1  AND  Логическое И                                                                       **/
/**   2  |    Бинарное ИЛИ                                                                       **/
/**   3  XOR  Бинарное ИЛИ ИСКЛЮЧАЮЩЕЕ                                                           **/
/**   4  &    Бинарное И                                                                         **/
/**   5  ==   Равно                                                                              **/
/**      <>   Не равно                                                                           **/
/**   6  <    Меньше                                                                             **/
/**      <=   Меньше или равно                                                                   **/
/**      >    Больше                                                                             **/
/**      >=   Больше или равно                                                                   **/
/**   7  +    Сложение                                                                           **/
/**      -    Вычитание                                                                          **/
/**   8  *    Умножение                                                                          **/
/**      /    Деление                                                                            **/
/**      MOD  Остаток от деления                                                                 **/
/**   9  ~    Бинарная инверсия                                                                  **/
/**      NOT  Логическое НЕ                                                                      **/
/**      -    Унарный минус                                                                      **/
/**  10  ()   Круглые скобки                                                                     **/
/**  11  var  Переменная (функция)                                                               **/
/**                                                                                              **/
/**************************************************************************************************/
expr
	: expr1
	| expr _OR_       expr1                       { $$ = new rExpr(EXP_OR, $1, $3); CHECK_ERROR; }
	;

expr1
	: expr2
	| expr1 _AND_     expr2                       { $$ = new rExpr(EXP_AND, $1, $3); CHECK_ERROR; }
	;

expr2
	: expr3
	| expr2 _BOR_     expr3                       { $$ = new rExpr(EXP_BOR , $1, $3); CHECK_ERROR; }
	;

expr3
	: expr4
	| expr3 _XOR_     expr4                       { $$ = new rExpr(EXP_XOR , $1, $3); CHECK_ERROR; }
	;

expr4
	: expr5
	| expr4 _BAND_    expr5                       { $$ = new rExpr(EXP_BAND, $1, $3); CHECK_ERROR; }
	;

expr5
	: expr6
	| expr5 _EQUAL_   expr6                       { $$ = new rExpr(EXP_EQ , $1, $3); CHECK_ERROR; }
	| expr5 _NEQUAL_  expr6                       { $$ = new rExpr(EXP_NEQ, $1, $3); CHECK_ERROR; }
	;

expr6
	: expr7
	| expr6 _GT_      expr7                       { $$ = new rExpr(EXP_GT, $1, $3); CHECK_ERROR; }
	| expr6 _GE_      expr7                       { $$ = new rExpr(EXP_GE, $1, $3); CHECK_ERROR; }
	| expr6 _LT_      expr7                       { $$ = new rExpr(EXP_LT, $1, $3); CHECK_ERROR; }
	| expr6 _LE_      expr7                       { $$ = new rExpr(EXP_LE, $1, $3); CHECK_ERROR; }
	;

expr7
	: expr8
	| expr7 _PLUS_    expr8                       { $$ = new rExpr(EXP_ADD, $1, $3); CHECK_ERROR; }
	| expr7 _MINUS_   expr8                       { $$ = new rExpr(EXP_SUB, $1, $3); CHECK_ERROR; }
	;

expr8
	: expr9
	| expr8 _STAR_  expr9                         { $$ = new rExpr(EXP_MUL, $1, $3); CHECK_ERROR; }
	| expr8 _SLASH_ expr9                         { $$ = new rExpr(EXP_DIV, $1, $3); CHECK_ERROR; }
	| expr8 _MOD_   expr9                         { $$ = new rExpr(EXP_MOD, $1, $3); CHECK_ERROR; }
	;

expr9
	: expr10
	| _MINUS_ expr9                               { $$ = new rExpr(EXP_NEG , $2); CHECK_ERROR; }
	| _BINV_  expr9                               { $$ = new rExpr(EXP_BINV, $2); CHECK_ERROR; }
	| _NOT_   expr9                               { $$ = new rExpr(EXP_NOT , $2); CHECK_ERROR; }
	;

expr10
	: expr11
	| _LPAREN_ expr _RPAREN_                      { $$ = $2;            CHECK_ERROR; }
	;

expr11
	: reg_access                                  { $$ = new rExpr($1); CHECK_ERROR; }
	| constant                                    { $$ = $1;            CHECK_ERROR; }
	| internal_func                               { $$ = $1;            CHECK_ERROR; }
	;

internal_func
	: _WORD_TO_INT_   _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_W2I, 0, 0, $3, 0); CHECK_ERROR; } 
	| _WORD_TO_DWORD_ _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_W2D, 0, 0, $3, 0); CHECK_ERROR; } 
	| _WORD_TO_LONG_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_W2L, 0, 0, $3, 0); CHECK_ERROR; } 
	| _WORD_TO_REAL_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_W2R, 0, 0, $3, 0); CHECK_ERROR; } 
	| _WORD_TO_BOOL_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_W2B, 0, 0, $3, 0); CHECK_ERROR; } 
	| _INT_TO_WORD_   _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_I2W, 0, 0, $3, 0); CHECK_ERROR; } 
	| _INT_TO_DWORD_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_I2D, 0, 0, $3, 0); CHECK_ERROR; } 
	| _INT_TO_LONG_   _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_I2L, 0, 0, $3, 0); CHECK_ERROR; } 
	| _INT_TO_REAL_   _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_I2R, 0, 0, $3, 0); CHECK_ERROR; } 
	| _INT_TO_BOOL_   _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_I2B, 0, 0, $3, 0); CHECK_ERROR; } 
	| _DWORD_TO_WORD_ _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_D2W, 0, 0, $3, 0); CHECK_ERROR; } 
	| _DWORD_TO_INT_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_D2I, 0, 0, $3, 0); CHECK_ERROR; } 
	| _DWORD_TO_LONG_ _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_D2L, 0, 0, $3, 0); CHECK_ERROR; } 
	| _DWORD_TO_REAL_ _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_D2R, 0, 0, $3, 0); CHECK_ERROR; } 
	| _DWORD_TO_BOOL_ _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_D2B, 0, 0, $3, 0); CHECK_ERROR; } 
	| _LONG_TO_WORD_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_L2W, 0, 0, $3, 0); CHECK_ERROR; } 
	| _LONG_TO_INT_   _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_L2I, 0, 0, $3, 0); CHECK_ERROR; } 
	| _LONG_TO_DWORD_ _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_L2D, 0, 0, $3, 0); CHECK_ERROR; } 
	| _LONG_TO_REAL_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_L2R, 0, 0, $3, 0); CHECK_ERROR; } 
	| _LONG_TO_BOOL_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_L2B, 0, 0, $3, 0); CHECK_ERROR; } 
	| _REAL_TO_WORD_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_R2W, 0, 0, $3, 0); CHECK_ERROR; } 
	| _REAL_TO_INT_   _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_R2I, 0, 0, $3, 0); CHECK_ERROR; } 
	| _REAL_TO_LONG_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_R2L, 0, 0, $3, 0); CHECK_ERROR; } 
	| _REAL_TO_DWORD_ _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_R2D, 0, 0, $3, 0); CHECK_ERROR; } 
	| _REAL_TO_BOOL_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_R2B, 0, 0, $3, 0); CHECK_ERROR; } 
	| _BOOL_TO_WORD_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_B2W, 0, 0, $3, 0); CHECK_ERROR; } 
	| _BOOL_TO_INT_   _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_B2I, 0, 0, $3, 0); CHECK_ERROR; } 
	| _BOOL_TO_DWORD_ _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_B2D, 0, 0, $3, 0); CHECK_ERROR; } 
	| _BOOL_TO_LONG_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_B2L, 0, 0, $3, 0); CHECK_ERROR; } 
	| _BOOL_TO_REAL_  _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_B2R, 0, 0, $3, 0); CHECK_ERROR; } 
	| _GET_REG_SYS_   _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_GRS, 0, 0, $3, 0); CHECK_ERROR; } 
	| _GET_REG_3X_    _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_GR3, 0, 0, $3, 0); CHECK_ERROR; } 
	| _GET_REG_4X_    _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_GR4, 0, 0, $3, 0); CHECK_ERROR; } 
	| _GET_REG_       _LPAREN_ expr _COMMA_ 
	  expr _RPAREN_                               { $$ = new rExpr(EXP_GR  , 0, 0, $3, $5); CHECK_ERROR; } 
	| _ABS_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_ABS , 0, 0, $3, 0); CHECK_ERROR; } 
	| _SQRT_          _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_SQRT, 0, 0, $3, 0); CHECK_ERROR; } 
	| _LN_            _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_LN  , 0, 0, $3, 0); CHECK_ERROR; } 
	| _LOG_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_LOG , 0, 0, $3, 0); CHECK_ERROR; } 
	| _RAND_          _LPAREN_ _RPAREN_           { $$ = new rExpr(EXP_RND , 0, 0,  0, 0); CHECK_ERROR; } 
	| _POW_           _LPAREN_ expr _COMMA_
	  expr _RPAREN_                               { $$ = new rExpr(EXP_POW , 0, 0, $3, $5); CHECK_ERROR; } 
	| _ODD_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_ODD , 0, 0, $3, 0); CHECK_ERROR; } 
	| _SGN_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_SGN , 0, 0, $3, 0); CHECK_ERROR; } 
	| _SIN_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_SIN , 0, 0, $3, 0); CHECK_ERROR; } 
	| _ATN_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_ATN , 0, 0, $3, 0); CHECK_ERROR; } 
	| _COS_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_COS , 0, 0, $3, 0); CHECK_ERROR; } 
	| _EXP_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_EXP , 0, 0, $3, 0); CHECK_ERROR; } 
	| _FIX_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_FIX , 0, 0, $3, 0); CHECK_ERROR; } 
	| _INT_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_INT , 0, 0, $3, 0); CHECK_ERROR; } 
	| _TAN_           _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_TAN , 0, 0, $3, 0); CHECK_ERROR; } 
	| _ROUND_         _LPAREN_ expr _COMMA_
	  expr _RPAREN_                               { $$ = new rExpr(EXP_ROU , 0, 0, $3, $5); CHECK_ERROR; } 
	| _CREATEUTIME_   _LPAREN_ expr _COMMA_ 
	  expr _COMMA_ expr _COMMA_ expr _COMMA_
	  expr _COMMA_ expr _RPAREN_                  { $$ = new rExpr(EXP_CRTUTIME, 0, 0, $3, $5, $7, $9, $11, $13, NULL, NULL); CHECK_ERROR; }
	| _CHECK_STORAGE_ _LPAREN_ expr _RPAREN_      { $$ = new rExpr(EXP_CHKSTRG , 0, 0, $3, 0); CHECK_ERROR; }
	;	

constant
	: _DIGHEX_                                    { $$ = new rExpr(stHexToInt(st_text + 2)); CHECK_ERROR; }
	| _UNSINGED_INT_                              { $$ = new rExpr(stToInt   (st_text)); CHECK_ERROR; }
	| _REALNUMBER_                                { $$ = new rExpr(stToReal  (st_text));                CHECK_ERROR; }
	| _TRUE_                                      { $$ = new rExpr(   1, STT_BOOL     ); CHECK_ERROR; }
	| _FALSE_                                     { $$ = new rExpr(   0, STT_BOOL     ); CHECK_ERROR; }
	;


sep
	: _SEMICOLON_
	;

%%

#include "moxa_st.l.cpp"

