
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */


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




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 1
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LROUND = 258,
     RROUND = 259,
     LSQUARE = 260,
     RSQUARE = 261,
     COMMA = 262,
     NEW_LINE = 263,
     COLON = 264,
     DOT = 265,
     INT_NUMBER = 266,
     HEX_NUMBER = 267,
     ID = 268,
     CHARACTER_STRING = 269,
     PRAGMA_NAME = 270,
     PRAGMA_VERSION = 271,
     PRAGMA_CLASS = 272,
     PRAGMA_DEFINE = 273,
     R0 = 274,
     R1 = 275,
     R2 = 276,
     R3 = 277,
     RC = 278,
     RF = 279,
     IF = 280,
     IR = 281,
     PLUS = 282,
     MINUS = 283,
     STAR = 284,
     ADD = 285,
     AND = 286,
     DEC = 287,
     DIV = 288,
     INC = 289,
     MOD = 290,
     MUL = 291,
     NEG = 292,
     NOT = 293,
     OR = 294,
     SUB = 295,
     XOR = 296,
     MIN = 297,
     MAX = 298,
     BSF = 299,
     BSR = 300,
     BT = 301,
     BTR = 302,
     BTS = 303,
     BTC = 304,
     SHL = 305,
     SHR = 306,
     ROL = 307,
     ROR = 308,
     EQ = 309,
     NEQ = 310,
     GT = 311,
     GE = 312,
     LT = 313,
     LE = 314,
     TEST = 315,
     JMP = 316,
     JZ = 317,
     JNZ = 318,
     JO = 319,
     JNO = 320,
     JCZ = 321,
     JCNZ = 322,
     LOOP = 323,
     MOV = 324,
     CALL = 325,
     LEN = 326,
     EXIT = 327,
     LDTR = 328,
     LDFD = 329,
     LDEN = 330,
     LDFR = 331,
     CIDL = 332,
     CMOV = 333,
     CATT = 334,
     CTKF = 335,
     CGVF = 336,
     CEAT = 337,
     CPS = 338,
     CPW = 339,
     NOP = 340
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


    WarAnts::Asm::PragmaType TPRAGMATYPE;
    WarAnts::Asm::Pragma* TPRAGMA;
    WarAnts::Asm::Function* TFUNCTION;
    WarAnts::Asm::Expression* TEXPR;
    WarAnts::Asm::Statetment* TSTATETMENT;
    WarAnts::Asm::StringNode* TSTRING;
    int64_t TINEGER;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   245

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNRULES -- Number of states.  */
#define YYNSTATES  245

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,     9,    13,    16,    18,    22,
      24,    26,    28,    30,    33,    35,    40,    43,    45,    48,
      50,    53,    57,    60,    62,    65,    68,    73,    78,    81,
      86,    89,    94,    99,   102,   105,   110,   115,   120,   125,
     130,   135,   140,   145,   150,   155,   160,   165,   170,   175,
     180,   185,   190,   195,   200,   205,   210,   215,   218,   221,
     224,   227,   230,   233,   236,   239,   244,   247,   252,   254,
     257,   260,   263,   266,   269,   274,   279,   284,   289,   292,
     294,   296,   298,   300,   304,   306,   310,   314,   316,   320,
     322,   326,   328,   330,   332,   334,   336,   338,   340,   342,
     344,   346,   348,   350,   352,   354
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      87,     0,    -1,   109,    88,    -1,    88,    -1,    -1,    90,
      89,    96,    -1,    90,    91,    -1,    91,    -1,    92,   110,
     109,    -1,    17,    -1,    15,    -1,    16,    -1,    94,    -1,
      94,    95,    -1,    95,    -1,    18,   111,   108,   109,    -1,
      96,    97,    -1,    97,    -1,    93,    98,    -1,    98,    -1,
      99,   100,    -1,    10,   111,   109,    -1,   100,   101,    -1,
     101,    -1,   102,   109,    -1,   111,     9,    -1,    30,   103,
       7,   103,    -1,    31,   103,     7,   103,    -1,    32,   103,
      -1,    33,   103,     7,   103,    -1,    34,   103,    -1,    35,
     103,     7,   103,    -1,    36,   103,     7,   103,    -1,    37,
     103,    -1,    38,   103,    -1,    39,   103,     7,   103,    -1,
      40,   103,     7,   103,    -1,    41,   103,     7,   103,    -1,
      42,   103,     7,   103,    -1,    43,   103,     7,   103,    -1,
      44,   103,     7,   103,    -1,    45,   103,     7,   103,    -1,
      46,   103,     7,   103,    -1,    47,   103,     7,   103,    -1,
      48,   103,     7,   103,    -1,    49,   103,     7,   103,    -1,
      50,   103,     7,   103,    -1,    51,   103,     7,   103,    -1,
      52,   103,     7,   103,    -1,    53,   103,     7,   103,    -1,
      54,   103,     7,   103,    -1,    55,   103,     7,   103,    -1,
      56,   103,     7,   103,    -1,    57,   103,     7,   103,    -1,
      58,   103,     7,   103,    -1,    59,   103,     7,   103,    -1,
      60,   103,     7,   103,    -1,    61,   111,    -1,    62,   111,
      -1,    63,   111,    -1,    64,   111,    -1,    65,   111,    -1,
      66,   111,    -1,    67,   111,    -1,    68,   111,    -1,    69,
     103,     7,   103,    -1,    70,   111,    -1,    71,   103,     7,
     103,    -1,    72,    -1,    73,   103,    -1,    74,   103,    -1,
      75,   103,    -1,    76,   103,    -1,    77,   103,    -1,    78,
     103,     7,   103,    -1,    79,   103,     7,   103,    -1,    80,
     103,     7,   103,    -1,    81,   103,     7,   103,    -1,    82,
     103,    -1,    83,    -1,    84,    -1,    85,    -1,   104,    -1,
       5,   104,     6,    -1,   105,    -1,   104,    27,   105,    -1,
     104,    28,   105,    -1,   106,    -1,   105,    29,   106,    -1,
     107,    -1,     3,   104,     4,    -1,    19,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      26,    -1,   108,    -1,   111,    -1,    11,    -1,    12,    -1,
       8,    -1,    14,    -1,    13,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    72,    72,    73,    77,    77,    82,    83,    87,    91,
      92,    93,    97,   101,   102,   106,   110,   111,   115,   116,
     120,   124,   128,   129,   133,   137,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     168,   169,   170,   171,   172,   173,   174,   177,   178,   179,
     180,   181,   182,   183,   184,   187,   188,   189,   190,   193,
     194,   195,   196,   199,   200,   201,   202,   203,   204,   205,
     206,   208,   214,   215,   231,   232,   233,   237,   238,   242,
     243,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   260,   261,   265,   269,   273
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LROUND", "RROUND", "LSQUARE", "RSQUARE",
  "COMMA", "NEW_LINE", "COLON", "DOT", "INT_NUMBER", "HEX_NUMBER", "ID",
  "CHARACTER_STRING", "PRAGMA_NAME", "PRAGMA_VERSION", "PRAGMA_CLASS",
  "PRAGMA_DEFINE", "R0", "R1", "R2", "R3", "RC", "RF", "IF", "IR", "PLUS",
  "MINUS", "STAR", "ADD", "AND", "DEC", "DIV", "INC", "MOD", "MUL", "NEG",
  "NOT", "OR", "SUB", "XOR", "MIN", "MAX", "BSF", "BSR", "BT", "BTR",
  "BTS", "BTC", "SHL", "SHR", "ROL", "ROR", "EQ", "NEQ", "GT", "GE", "LT",
  "LE", "TEST", "JMP", "JZ", "JNZ", "JO", "JNO", "JCZ", "JCNZ", "LOOP",
  "MOV", "CALL", "LEN", "EXIT", "LDTR", "LDFD", "LDEN", "LDFR", "CIDL",
  "CMOV", "CATT", "CTKF", "CGVF", "CEAT", "CPS", "CPW", "NOP", "$accept",
  "asm_file", "asm_code", "$@1", "list_of_pragmas", "pragma_definition",
  "pragma", "define_declaration", "list_of_defines", "define_definition",
  "list_of_asm_functions", "asm_function", "asm_function_declaration",
  "asm_function_name", "list_of_commands", "asm_command_line",
  "asm_command", "address", "expr_0", "expr_1", "expr_2", "expr_3",
  "number", "newline", "quted_string", "label", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    89,    88,    90,    90,    91,    92,
      92,    92,    93,    94,    94,    95,    96,    96,    97,    97,
      98,    99,   100,   100,   101,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   103,   103,   104,   104,   104,   105,   105,   106,
     106,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   108,   108,   109,   110,   111
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     3,     2,     1,     3,     1,
       1,     1,     1,     2,     1,     4,     2,     1,     2,     1,
       2,     3,     2,     1,     2,     2,     4,     4,     2,     4,
       2,     4,     4,     2,     2,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     2,     2,     2,
       2,     2,     2,     2,     2,     4,     2,     4,     1,     2,
       2,     2,     2,     2,     4,     4,     4,     4,     2,     1,
       1,     1,     1,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   103,    10,    11,     9,     0,     3,     4,     7,     0,
       0,     1,     0,     6,   104,     0,     2,     0,     0,     0,
      12,    14,     5,    17,    19,     0,     8,   105,     0,     0,
      18,    13,    16,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    79,    80,    81,    20,
      23,     0,     0,    21,   101,   102,     0,     0,     0,    91,
      92,    93,    94,    95,    96,    97,    98,     0,    82,    84,
      87,    89,    99,   100,     0,    28,     0,    30,     0,     0,
      33,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,    58,    59,    60,    61,    62,
      63,    64,     0,    66,     0,    69,    70,    71,    72,    73,
       0,     0,     0,     0,    78,    22,    24,    25,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90,    83,    26,
      85,    86,    88,    27,    29,    31,    32,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    65,
      67,    74,    75,    76,    77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,    12,     7,     8,     9,    19,    20,    21,
      22,    23,    24,    25,    89,    90,    91,   107,   108,   109,
     110,   111,   112,    10,    15,   113
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -49
static const yytype_int16 yypact[] =
{
     102,   -49,   -49,   -49,   -49,    35,   -49,    15,   -49,    27,
      15,   -49,   103,   -49,   -49,    29,   -49,   115,   115,   106,
     111,   -49,   103,   -49,   -49,    23,   -49,   -49,    29,    22,
     -49,   -49,   -49,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   115,   115,   115,   115,   115,   115,
     115,   115,   180,   115,   180,   -49,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   -49,   -49,   -49,    23,
     -49,    29,   121,   -49,   -49,   -49,    29,   204,   204,   -49,
     -49,   -49,   -49,   -49,   -49,   -49,   -49,   124,    84,   110,
     -49,   -49,   -49,   -49,   131,   -49,   133,   -49,   174,   177,
     -49,   -49,   179,   181,   182,   183,   187,   188,   189,   190,
     201,   202,   203,   205,   206,   207,   211,   212,   213,   214,
     215,   224,   225,   226,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   227,   -49,   228,   -49,   -49,   -49,   -49,   -49,
     229,   230,   231,   232,   -49,   -49,   -49,   -49,   -49,   105,
     108,   180,   204,   204,   204,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   -49,   -49,   -49,
     110,   110,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   -49,   -49,   -49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -49,   -49,   233,   -49,   -49,   234,   -49,   -49,   -49,   167,
     -49,   218,   192,   -49,   -49,   153,   -49,   -34,    25,   -48,
      70,   -49,   216,    24,   -49,   109
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
       2,     3,     4,    94,    95,    11,    27,     1,   152,    26,
     154,    14,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,    93,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,   207,
       1,   172,   173,    17,   208,   166,    17,     2,     3,     4,
     168,    18,   169,   170,   210,   211,    28,    29,    27,    18,
     167,   171,   172,   173,    92,   172,   173,   209,   175,   174,
     176,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   144,   145,   146,   147,   148,   149,   150,
     151,   177,   153,    97,   178,    98,   179,    31,   180,   181,
     182,    94,    95,    27,   183,   184,   185,   186,    92,    99,
     100,   101,   102,   103,   104,   105,   106,    97,   187,   188,
     189,    30,   190,   191,   192,    94,    95,    27,   193,   194,
     195,   196,   197,    99,   100,   101,   102,   103,   104,   105,
     106,   198,   199,   200,   201,   202,   203,   204,   205,   206,
      32,    13,   165,    16,   212,    96
};

static const yytype_uint8 yycheck[] =
{
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      15,    16,    17,    11,    12,     0,    13,     8,    72,    15,
      74,    14,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    28,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,     4,
       8,    27,    28,    10,     6,    91,    10,    15,    16,    17,
      96,    18,    97,    98,   172,   173,    17,    18,    13,    18,
       9,     7,    27,    28,    25,    27,    28,   171,     7,    29,
       7,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,    64,    65,    66,    67,    68,    69,    70,
      71,     7,    73,     3,     7,     5,     7,    20,     7,     7,
       7,    11,    12,    13,     7,     7,     7,     7,    89,    19,
      20,    21,    22,    23,    24,    25,    26,     3,     7,     7,
       7,    19,     7,     7,     7,    11,    12,    13,     7,     7,
       7,     7,     7,    19,    20,    21,    22,    23,    24,    25,
      26,     7,     7,     7,     7,     7,     7,     7,     7,     7,
      22,     7,    89,    10,   174,    29
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    15,    16,    17,    87,    88,    90,    91,    92,
     109,     0,    89,    91,    14,   110,    88,    10,    18,    93,
      94,    95,    96,    97,    98,    99,   109,    13,   111,   111,
      98,    95,    97,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,   100,
     101,   102,   111,   109,    11,    12,   108,     3,     5,    19,
      20,    21,    22,    23,    24,    25,    26,   103,   104,   105,
     106,   107,   108,   111,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   111,   111,   111,   111,   111,   111,
     111,   111,   103,   111,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   101,   109,     9,   109,   104,
     104,     7,    27,    28,    29,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     4,     6,   103,
     105,   105,   106,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:

    { yy_code->m_pragma = (yyvsp[(1) - (1)].TPRAGMA); printf("add pragma list\n"); ;}
    break;

  case 5:

    { yy_code->m_function = (yyvsp[(3) - (3)].TFUNCTION); printf("add funct list\n"); ;}
    break;

  case 6:

    { (yyval.TPRAGMA) = (yyvsp[(1) - (2)].TPRAGMA)->add((yyvsp[(2) - (2)].TPRAGMA)); ;}
    break;

  case 7:

    { (yyval.TPRAGMA) = (yyvsp[(1) - (1)].TPRAGMA); ;}
    break;

  case 8:

    { (yyval.TPRAGMA) = new WarAnts::Asm::Pragma((yyvsp[(1) - (3)].TPRAGMATYPE), (yyvsp[(2) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 9:

    { (yyval.TPRAGMATYPE) = WarAnts::Asm::PragmaType::Class; ;}
    break;

  case 10:

    { (yyval.TPRAGMATYPE) = WarAnts::Asm::PragmaType::Name; ;}
    break;

  case 11:

    { (yyval.TPRAGMATYPE) = WarAnts::Asm::PragmaType::Version; ;}
    break;

  case 15:

    { yy_code->m_defines[(yyvsp[(2) - (4)].TSTRING)->get()] = (yyvsp[(3) - (4)].TINEGER); printf("define %s = %i\n", (yyvsp[(2) - (4)].TSTRING)->get().c_str(), (yyvsp[(3) - (4)].TINEGER)); ;}
    break;

  case 16:

    { (yyval.TFUNCTION) = (yyvsp[(1) - (2)].TFUNCTION)->add((yyvsp[(2) - (2)].TFUNCTION)); printf("list_of_asm_functions\n"); ;}
    break;

  case 17:

    { (yyval.TFUNCTION) = (yyvsp[(1) - (1)].TFUNCTION); printf("asm_function\n"); ;}
    break;

  case 18:

    { (yyval.TFUNCTION) = (yyvsp[(2) - (2)].TFUNCTION); ;}
    break;

  case 19:

    { (yyval.TFUNCTION) = (yyvsp[(1) - (1)].TFUNCTION); ;}
    break;

  case 20:

    { (yyval.TFUNCTION) = new WarAnts::Asm::Function((yyvsp[(1) - (2)].TSTRING)->get(), (yyvsp[(2) - (2)].TSTATETMENT), yy_code.get()); ;}
    break;

  case 21:

    { (yyval.TSTRING) = (yyvsp[(2) - (3)].TSTRING); printf("Found function '%s'\n", (yyvsp[(2) - (3)].TSTRING)->get().c_str()); ;}
    break;

  case 22:

    { (yyval.TSTATETMENT) = (yyvsp[(1) - (2)].TSTATETMENT)->add((yyvsp[(2) - (2)].TSTATETMENT)); ;}
    break;

  case 23:

    { (yyval.TSTATETMENT) = (yyvsp[(1) - (1)].TSTATETMENT); ;}
    break;

  case 24:

    { (yyval.TSTATETMENT) = (yyvsp[(1) - (2)].TSTATETMENT); ;}
    break;

  case 25:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment((yyvsp[(1) - (2)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 26:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ADD , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 27:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::AND , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 28:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::DEC , (yyvsp[(2) - (2)].TEXPR),     yy_code.get()); ;}
    break;

  case 29:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::DIV , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 30:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::INC , (yyvsp[(2) - (2)].TEXPR),     yy_code.get()); ;}
    break;

  case 31:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MOD , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 32:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MUL , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 33:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NEG , (yyvsp[(2) - (2)].TEXPR),     yy_code.get()); ;}
    break;

  case 34:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NOT , (yyvsp[(2) - (2)].TEXPR),     yy_code.get()); ;}
    break;

  case 35:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::OR  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 36:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SUB , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 37:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::XOR , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 38:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MIN , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 39:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MAX , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 40:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BSF , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 41:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BSR , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 42:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BT  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 43:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTR , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 44:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTS , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 45:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTC , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 46:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SHL , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 47:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SHR , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 48:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ROL , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 49:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ROR , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 50:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::EQ  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 51:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NEQ , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 52:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::GT  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 53:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::GE  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 54:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LT  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 55:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LE  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 56:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::TEST, (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 57:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JMP , (yyvsp[(2) - (2)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 58:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JZ  , (yyvsp[(2) - (2)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 59:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JNZ , (yyvsp[(2) - (2)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 60:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JO  , (yyvsp[(2) - (2)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 61:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JNO , (yyvsp[(2) - (2)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 62:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JCZ , (yyvsp[(2) - (2)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 63:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JCNZ, (yyvsp[(2) - (2)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 64:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LOOP, (yyvsp[(2) - (2)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 65:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MOV , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 66:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CALL, (yyvsp[(2) - (2)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 67:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LEN , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 68:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::EXIT, yy_code.get()); ;}
    break;

  case 69:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDTR, (yyvsp[(2) - (2)].TEXPR), yy_code.get()); ;}
    break;

  case 70:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDFD, (yyvsp[(2) - (2)].TEXPR), yy_code.get()); ;}
    break;

  case 71:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDEN, (yyvsp[(2) - (2)].TEXPR), yy_code.get()); ;}
    break;

  case 72:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDFR, (yyvsp[(2) - (2)].TEXPR), yy_code.get()); ;}
    break;

  case 73:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CIDL , (yyvsp[(2) - (2)].TEXPR),     yy_code.get()); ;}
    break;

  case 74:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CMOV , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 75:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CATT , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 76:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CTKF , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 77:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CGVF , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR), yy_code.get()); ;}
    break;

  case 78:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CEAT , (yyvsp[(2) - (2)].TEXPR),     yy_code.get()); ;}
    break;

  case 79:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CPS  ,         yy_code.get()); ;}
    break;

  case 80:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CPW  ,         yy_code.get()); ;}
    break;

  case 81:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NOP  ,         yy_code.get()); ;}
    break;

  case 82:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 83:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression((yyvsp[(2) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 84:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 85:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Plus,  (yyvsp[(1) - (3)].TEXPR), (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 86:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Minus, (yyvsp[(1) - (3)].TEXPR), (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 87:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 88:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Star, (yyvsp[(1) - (3)].TEXPR), (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 89:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 90:

    { (yyval.TEXPR) = (yyvsp[(2) - (3)].TEXPR); ;}
    break;

  case 91:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R0, yy_code.get()); ;}
    break;

  case 92:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R1, yy_code.get()); ;}
    break;

  case 93:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R2, yy_code.get()); ;}
    break;

  case 94:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R3, yy_code.get()); ;}
    break;

  case 95:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::RC, yy_code.get()); ;}
    break;

  case 96:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::RF, yy_code.get()); ;}
    break;

  case 97:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::IF, yy_code.get()); ;}
    break;

  case 98:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::IR, yy_code.get()); ;}
    break;

  case 99:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression((yyvsp[(1) - (1)].TINEGER), yy_code.get()); ;}
    break;

  case 100:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(getDefine((yyvsp[(1) - (1)].TSTRING)->get()), yy_code.get()); ;}
    break;

  case 101:

    { (yyval.TINEGER) = getIntNumber(yytext); ;}
    break;

  case 102:

    { (yyval.TINEGER) = getHexNumber(yytext); ;}
    break;

  case 104:

    { (yyval.TSTRING) = new WarAnts::Asm::StringNode(yytext, yy_code.get()); ;}
    break;

  case 105:

    { (yyval.TSTRING) = new WarAnts::Asm::StringNode(yytext, yy_code.get()); ;}
    break;



      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}





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

