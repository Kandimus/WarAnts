%option noyywrap
%option yylineno

delim     [ \t\r]
new_line  [\n]
NQUOTE    [^"]
id        [A-Z_]([A-Z0-9_])*
digit     [0-9]
hexdigit  [0-9a-fA-F]

int_num    "-"{digit}+
hex_num   "0x"{hexdigit}+

%%

{delim}+                      { ; }
{int_num}                     { return INT_NUMBER; }
{hex_num}                     { return HEX_NUMBER; }
\"({NQUOTE}|"")+\"            { return CHARACTER_STRING; }
{new_line}+                   { return NEW_LINE; }
{id}                          { return ID; }

"("                           { return LROUND; }
")"                           { return RROUND; }
"["                           { return LSQUARE; }
"]"                           { return RSQUARE; }
","                           { return COMMA; }
":"                           { return COLON; }
"."                           { return DOT; }

"#name"                       { return PRAGMA_NAME; }
"#version"                    { return PRAGMA_VERSION; }
"#class"                      { return PRAGMA_CLASS; }

"R0"                          { return R0; }
"R1"                          { return R1; }
"R2"                          { return R2; }
"R3"                          { return R3; }
"RC"                          { return RC; }
"RF"                          { return RF; }
"IF"                          { return IF; }
"IR"                          { return IR; }

"+"                           { return PLUS; }
"-"                           { return MINUS; }
"*"                           { return STAR; }

"add"                         { return ADD; }
"and"                         { return AND; }

"//"                          { skipSignleLineComment(); }
"/*"                          { skipMultiLineComment(); }

.                             { return yytext[0]; }

%%

void skipSignleLineComment(void)
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

void skipMultiLineComment(void)
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
