%{
#pragma warning(disable:4102)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4273)

void skipSignleLineComment(void);
void skipMultiLineComment(void);

%}

%option noyywrap
%option yylineno

delim     [ \t]
new_line  [\n]
NQUOTE    [^"]
id        [A-Z_]([A-Z0-9_])*
digit     [0-9]
hexdigit  [0-9a-fA-F]

uint_num   {digit}+
int_num    "-"{digit}+
hex_num   {hexdigit}+"H"

%%

{delim}+                    { ; }
{uint_num}                  { return INT_NUMBER; }
{int_num}                   { return INT_NUMBER; }
{hex_num}                   { return HEX_NUMBER; }
\"({NQUOTE}|"")+\"          { return CHARACTER_STRING; }
{new_line}+                 { return NEW_LINE; }

"("                         { return LROUND; }
")"                         { return RROUND; }
"["                         { return LSQUARE; }
"]"                         { return RSQUARE; }
","                         { return COMMA; }
":"                         { return COLON; }
"."                         { return DOT; }
"#"                         { return SIGN; }
"%"                         { return PERSENT; }

"core"                      { return CORE; }
"name"                      { return NAME; }
"version"                   { return VERSION; }
"class"                     { return CLASS; }
"define"                    { return DEFINE; }

"p0"                        { return P0; }
"p1"                        { return P1; }
"p2"                        { return P2; }
"r0"                        { return R0; }
"r1"                        { return R1; }
"r2"                        { return R2; }
"rc"                        { return RC; }
"rf"                        { return RF; }
"x"                         { return COORD_X;}
"y"                         { return COORD_Y;}

"+"                         { return PLUS; }
"-"                         { return MINUS; }
"*"                         { return STAR; }

"add"                       { return ADD; }
"and"                       { return AND; }
"dec"                       { return DEC; }
"div"                       { return DIV; }
"inc"                       { return INC; }
"mod"                       { return MOD; }
"mul"                       { return MUL; }
"neg"                       { return NEG; }
"not"                       { return NOT; }
"or"                        { return OR; }
"sub"                       { return SUB; }
"xor"                       { return XOR; }
"min"                       { return MIN; }
"max"                       { return MAX; }

"bsf"                       { return BSF; }
"bsr"                       { return BSR; }
"bt"                        { return BT; }
"btr"                       { return BTR; }
"btc"                       { return BTC; }
"shl"                       { return SHL; }
"shr"                       { return SHR; }
"rol"                       { return ROL; }
"ror"                       { return ROR; }

"eq"                        { return EQ; }
"neq"                       { return NEQ; }
"gt"                        { return GT; }
"ge"                        { return GE; }
"lt"                        { return LT; }
"le"                        { return LE; }
"test"                      { return TEST; }

"jmp"                       { return JMP; }
"jz"                        { return JZ; }
"jnz"                       { return JNZ; }
"jo"                        { return JO; }
"jno"                       { return JNO; }
"jcz"                       { return JCZ; }
"jncz"                      { return JCNZ; }
"loop"                      { return LOOP; }

"mov"                       { return MOV; }
"call"                      { return CALL; }
"len"                       { return LEN; }
"dist"                      { return DIST; }
"exit"                      { return EXIT; }

"ldtr"                      { return LDTR; }
"ldfd"                      { return LDFD; }
"lden"                      { return LDEN; }
"ldfr"                      { return LDFR; }

"cidl"                      { return CIDL; }
"cmov"                      { return CMOV; }
"catt"                      { return CATT; }
"ctkf"                      { return CTKF; }
"cgvf"                      { return CGVF; }
"ceat"                      { return CEAT; }
"cps"                       { return CPS; }
"spw"                       { return CPW; }

"//"                        { skipSignleLineComment(); }
"/*"                        { skipMultiLineComment(); }

{id}                        { return ID; }

.                           { printf("flex: UNDEF!!!!\n");  return yytext[0]; }

%%

static void skipSignleLineComment(void)
{
    int c;
    while ((c = yyinput()))
    {
        if('\r' == c || '\n' == c)
        {
            break;
        }
        else
        {
            if(c == EOF)
            {
                return;
            }
        }
    }
}

static void skipMultiLineComment(void)
{
    int c;
    while((c = yyinput()))
    {
        if('*' == c)
        {
            if('/' == (c = yyinput()))
            {
                return;
            }
            unput(c);
        }
        else
        {
            if('\n' == c)
            {
                ;//++stlineno;
            }
            else
            {
                if(c == EOF)
                {
                    //Compiler.SetError(stlineno, ERR_END_OF_FILE_);
                }
            }
        }
    }
}
