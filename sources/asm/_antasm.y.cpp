
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
     COLON = 263,
     DOT = 264,
     SIGN = 265,
     PERSENT = 266,
     LESS = 267,
     GREATER = 268,
     INT_NUMBER = 269,
     HEX_NUMBER = 270,
     ID = 271,
     CHARACTER_STRING = 272,
     NAME = 273,
     VERSION = 274,
     CLASS = 275,
     DEFINE = 276,
     CORE = 277,
     R0 = 278,
     R1 = 279,
     R2 = 280,
     RC = 281,
     RF = 282,
     P0 = 283,
     P1 = 284,
     P2 = 285,
     COORD_X = 286,
     COORD_Y = 287,
     PLUS = 288,
     MINUS = 289,
     STAR = 290,
     ADD = 291,
     AND = 292,
     DEC = 293,
     DIV = 294,
     INC = 295,
     MOD = 296,
     MUL = 297,
     NEG = 298,
     NOT = 299,
     OR = 300,
     SUB = 301,
     XOR = 302,
     MIN = 303,
     MAX = 304,
     BSF = 305,
     BSR = 306,
     BT = 307,
     BTR = 308,
     BTS = 309,
     BTC = 310,
     SHL = 311,
     SHR = 312,
     ROL = 313,
     ROR = 314,
     EQ = 315,
     NEQ = 316,
     GT = 317,
     GE = 318,
     LT = 319,
     LE = 320,
     TEST = 321,
     JMP = 322,
     JZ = 323,
     JNZ = 324,
     JT = 325,
     JF = 326,
     JO = 327,
     JNO = 328,
     JS = 329,
     JNS = 330,
     JCZ = 331,
     JCNZ = 332,
     LOOP = 333,
     CALL = 334,
     MOV = 335,
     LEN = 336,
     DIST = 337,
     RET = 338,
     DBG = 339,
     LDRC = 340,
     LDFD = 341,
     LDEN = 342,
     LDAL = 343,
     CIDL = 344,
     CMOV = 345,
     CATT = 346,
     CTKF = 347,
     CGVF = 348,
     CEAT = 349,
     CCSL = 350,
     CCWR = 351
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


    WarAnts::Asm::PragmaType TPRAGMATYPE;
    WarAnts::Asm::Pragma* TPRAGMA;
    WarAnts::Asm::Function* TFUNCTION;
    WarAnts::Asm::Expression* TEXPR;
    WarAnts::Asm::Statement* TSTATETMENT;
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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   298

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  90
/* YYNRULES -- Number of rules.  */
#define YYNRULES  181
/* YYNRULES -- Number of states.  */
#define YYNSTATES  324

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   351

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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,    10,    13,    15,    16,    21,
      23,    25,    27,    29,    31,    34,    36,    41,    44,    46,
      49,    51,    54,    55,    59,    62,    64,    65,    69,    70,
      76,    77,    83,    84,    88,    89,    95,    96,   100,   101,
     107,   108,   114,   115,   119,   120,   124,   125,   131,   132,
     138,   139,   145,   146,   152,   153,   159,   160,   166,   167,
     173,   174,   180,   181,   187,   188,   194,   195,   201,   202,
     208,   209,   215,   216,   222,   223,   229,   230,   236,   237,
     243,   244,   250,   251,   257,   258,   264,   265,   271,   272,
     278,   279,   283,   284,   288,   289,   293,   294,   298,   299,
     303,   304,   308,   309,   313,   314,   318,   319,   323,   324,
     328,   329,   333,   334,   338,   339,   343,   344,   350,   351,
     357,   358,   362,   363,   366,   367,   371,   372,   376,   377,
     381,   382,   386,   387,   391,   392,   396,   397,   401,   402,
     406,   407,   411,   412,   416,   417,   421,   422,   425,   426,
     429,   431,   433,   435,   437,   441,   445,   447,   451,   455,
     457,   461,   463,   467,   469,   471,   473,   475,   477,   481,
     485,   489,   493,   497,   501,   503,   505,   507,   509,   511,
     513,   515
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      98,     0,    -1,    99,    -1,    -1,   101,   100,   108,    -1,
     101,   102,    -1,   102,    -1,    -1,   186,   103,   104,   183,
      -1,    20,    -1,    18,    -1,    19,    -1,    22,    -1,   106,
      -1,   106,   107,    -1,   107,    -1,   185,    21,   184,   182,
      -1,   108,   109,    -1,   109,    -1,   105,   110,    -1,   110,
      -1,   111,   113,    -1,    -1,     9,   112,   184,    -1,   113,
     114,    -1,   114,    -1,    -1,   184,   115,     8,    -1,    -1,
      36,   116,   177,     7,   177,    -1,    -1,    37,   117,   177,
       7,   177,    -1,    -1,    38,   118,   177,    -1,    -1,    39,
     119,   177,     7,   177,    -1,    -1,    40,   120,   177,    -1,
      -1,    41,   121,   177,     7,   177,    -1,    -1,    42,   122,
     177,     7,   177,    -1,    -1,    43,   123,   177,    -1,    -1,
      44,   124,   177,    -1,    -1,    45,   125,   177,     7,   177,
      -1,    -1,    46,   126,   177,     7,   177,    -1,    -1,    47,
     127,   177,     7,   177,    -1,    -1,    48,   128,   177,     7,
     177,    -1,    -1,    49,   129,   177,     7,   177,    -1,    -1,
      50,   130,   177,     7,   177,    -1,    -1,    51,   131,   177,
       7,   177,    -1,    -1,    52,   132,   177,     7,   177,    -1,
      -1,    53,   133,   177,     7,   177,    -1,    -1,    54,   134,
     177,     7,   177,    -1,    -1,    55,   135,   177,     7,   177,
      -1,    -1,    56,   136,   177,     7,   177,    -1,    -1,    57,
     137,   177,     7,   177,    -1,    -1,    58,   138,   177,     7,
     177,    -1,    -1,    59,   139,   177,     7,   177,    -1,    -1,
      60,   140,   177,     7,   177,    -1,    -1,    61,   141,   177,
       7,   177,    -1,    -1,    62,   142,   177,     7,   177,    -1,
      -1,    63,   143,   177,     7,   177,    -1,    -1,    64,   144,
     177,     7,   177,    -1,    -1,    65,   145,   177,     7,   177,
      -1,    -1,    66,   146,   177,     7,   177,    -1,    -1,    67,
     147,   184,    -1,    -1,    68,   148,   184,    -1,    -1,    69,
     149,   184,    -1,    -1,    70,   150,   184,    -1,    -1,    71,
     151,   184,    -1,    -1,    72,   152,   184,    -1,    -1,    73,
     153,   184,    -1,    -1,    74,   154,   184,    -1,    -1,    75,
     155,   184,    -1,    -1,    76,   156,   184,    -1,    -1,    77,
     157,   184,    -1,    -1,    78,   158,   184,    -1,    -1,    79,
     159,   184,    -1,    -1,    80,   160,   177,     7,   177,    -1,
      -1,    81,   161,   177,     7,   177,    -1,    -1,    82,   162,
     177,    -1,    -1,    83,   163,    -1,    -1,    84,   164,   177,
      -1,    -1,    85,   165,   177,    -1,    -1,    86,   166,   177,
      -1,    -1,    87,   167,   177,    -1,    -1,    88,   168,   177,
      -1,    -1,    89,   169,   177,    -1,    -1,    90,   170,   177,
      -1,    -1,    91,   171,   177,    -1,    -1,    92,   172,   177,
      -1,    -1,    93,   173,   177,    -1,    -1,    94,   174,   177,
      -1,    -1,    95,   175,    -1,    -1,    96,   176,    -1,   181,
      -1,    28,    -1,    29,    -1,    30,    -1,     5,   178,     6,
      -1,    12,   178,    13,    -1,   179,    -1,   178,    33,   179,
      -1,   178,    34,   179,    -1,   180,    -1,   179,    35,   180,
      -1,   181,    -1,     3,   178,     4,    -1,    23,    -1,    24,
      -1,    25,    -1,    26,    -1,    27,    -1,    28,     8,    31,
      -1,    28,     8,    32,    -1,    29,     8,    31,    -1,    29,
       8,    32,    -1,    30,     8,    31,    -1,    30,     8,    32,
      -1,   182,    -1,   184,    -1,    14,    -1,    15,    -1,    17,
      -1,    16,    -1,    10,    -1,    11,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    76,    76,    80,    80,    86,    87,    91,    91,    95,
      96,    97,    98,   103,   107,   108,   112,   117,   118,   122,
     123,   127,   131,   131,   135,   136,   140,   140,   143,   143,
     144,   144,   145,   145,   146,   146,   147,   147,   148,   148,
     149,   149,   150,   150,   151,   151,   152,   152,   153,   153,
     154,   154,   155,   155,   156,   156,   159,   159,   160,   160,
     161,   161,   162,   162,   163,   163,   164,   164,   165,   165,
     166,   166,   167,   167,   168,   168,   171,   171,   172,   172,
     173,   173,   174,   174,   175,   175,   176,   176,   177,   177,
     180,   180,   181,   181,   182,   182,   183,   183,   184,   184,
     185,   185,   186,   186,   187,   187,   188,   188,   189,   189,
     190,   190,   191,   191,   192,   192,   195,   195,   196,   196,
     197,   197,   198,   198,   199,   199,   202,   202,   203,   203,
     204,   204,   205,   205,   208,   208,   209,   209,   210,   210,
     211,   211,   212,   212,   213,   213,   214,   214,   215,   215,
     221,   222,   223,   224,   225,   226,   242,   243,   244,   248,
     249,   253,   254,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   274,   275,   279,   283,
     287,   291
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LROUND", "RROUND", "LSQUARE", "RSQUARE",
  "COMMA", "COLON", "DOT", "SIGN", "PERSENT", "LESS", "GREATER",
  "INT_NUMBER", "HEX_NUMBER", "ID", "CHARACTER_STRING", "NAME", "VERSION",
  "CLASS", "DEFINE", "CORE", "R0", "R1", "R2", "RC", "RF", "P0", "P1",
  "P2", "COORD_X", "COORD_Y", "PLUS", "MINUS", "STAR", "ADD", "AND", "DEC",
  "DIV", "INC", "MOD", "MUL", "NEG", "NOT", "OR", "SUB", "XOR", "MIN",
  "MAX", "BSF", "BSR", "BT", "BTR", "BTS", "BTC", "SHL", "SHR", "ROL",
  "ROR", "EQ", "NEQ", "GT", "GE", "LT", "LE", "TEST", "JMP", "JZ", "JNZ",
  "JT", "JF", "JO", "JNO", "JS", "JNS", "JCZ", "JCNZ", "LOOP", "CALL",
  "MOV", "LEN", "DIST", "RET", "DBG", "LDRC", "LDFD", "LDEN", "LDAL",
  "CIDL", "CMOV", "CATT", "CTKF", "CGVF", "CEAT", "CCSL", "CCWR",
  "$accept", "asm_file", "asm_code", "$@1", "list_of_pragmas",
  "pragma_definition", "$@2", "pragma", "define_declaration",
  "list_of_defines", "define_definition", "list_of_asm_functions",
  "asm_function", "asm_function_declaration", "asm_function_name", "$@3",
  "list_of_commands", "asm_command", "$@4", "$@5", "$@6", "$@7", "$@8",
  "$@9", "$@10", "$@11", "$@12", "$@13", "$@14", "$@15", "$@16", "$@17",
  "$@18", "$@19", "$@20", "$@21", "$@22", "$@23", "$@24", "$@25", "$@26",
  "$@27", "$@28", "$@29", "$@30", "$@31", "$@32", "$@33", "$@34", "$@35",
  "$@36", "$@37", "$@38", "$@39", "$@40", "$@41", "$@42", "$@43", "$@44",
  "$@45", "$@46", "$@47", "$@48", "$@49", "$@50", "$@51", "$@52", "$@53",
  "$@54", "$@55", "$@56", "$@57", "$@58", "$@59", "$@60", "$@61", "$@62",
  "$@63", "$@64", "$@65", "address", "expr_0", "expr_1", "expr_2",
  "expr_3", "number", "quted_string", "label", "sign", "persent", 0
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
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,   100,    99,   101,   101,   103,   102,   104,
     104,   104,   104,   105,   106,   106,   107,   108,   108,   109,
     109,   110,   112,   111,   113,   113,   115,   114,   116,   114,
     117,   114,   118,   114,   119,   114,   120,   114,   121,   114,
     122,   114,   123,   114,   124,   114,   125,   114,   126,   114,
     127,   114,   128,   114,   129,   114,   130,   114,   131,   114,
     132,   114,   133,   114,   134,   114,   135,   114,   136,   114,
     137,   114,   138,   114,   139,   114,   140,   114,   141,   114,
     142,   114,   143,   114,   144,   114,   145,   114,   146,   114,
     147,   114,   148,   114,   149,   114,   150,   114,   151,   114,
     152,   114,   153,   114,   154,   114,   155,   114,   156,   114,
     157,   114,   158,   114,   159,   114,   160,   114,   161,   114,
     162,   114,   163,   114,   164,   114,   165,   114,   166,   114,
     167,   114,   168,   114,   169,   114,   170,   114,   171,   114,
     172,   114,   173,   114,   174,   114,   175,   114,   176,   114,
     177,   177,   177,   177,   177,   177,   178,   178,   178,   179,
     179,   180,   180,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   182,   182,   183,   184,
     185,   186
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     3,     2,     1,     0,     4,     1,
       1,     1,     1,     1,     2,     1,     4,     2,     1,     2,
       1,     2,     0,     3,     2,     1,     0,     3,     0,     5,
       0,     5,     0,     3,     0,     5,     0,     3,     0,     5,
       0,     5,     0,     3,     0,     3,     0,     5,     0,     5,
       0,     5,     0,     5,     0,     5,     0,     5,     0,     5,
       0,     5,     0,     5,     0,     5,     0,     5,     0,     5,
       0,     5,     0,     5,     0,     5,     0,     5,     0,     5,
       0,     5,     0,     5,     0,     5,     0,     5,     0,     5,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     5,     0,     5,
       0,     3,     0,     2,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     2,     0,     2,
       1,     1,     1,     1,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   181,     0,     2,     3,     6,     7,     1,     0,     5,
       0,    22,   180,     0,    13,    15,     4,    18,    20,     0,
       0,    10,    11,     9,    12,     0,     0,    19,    14,    17,
     179,    28,    30,    32,    34,    36,    38,    40,    42,    44,
      46,    48,    50,    52,    54,    56,    58,    60,    62,    64,
      66,    68,    70,    72,    74,    76,    78,    80,    82,    84,
      86,    88,    90,    92,    94,    96,    98,   100,   102,   104,
     106,   108,   110,   112,   114,   116,   118,   120,   122,   124,
     126,   128,   130,   132,   134,   136,   138,   140,   142,   144,
     146,   148,    21,    25,    26,     0,   178,     8,    23,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,   149,
      24,     0,     0,     0,     0,   176,   177,   163,   164,   165,
     166,   167,   151,   152,   153,     0,   150,   174,   175,     0,
      33,     0,    37,     0,     0,    43,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    91,
      93,    95,    97,    99,   101,   103,   105,   107,   109,   111,
     113,   115,     0,     0,   121,   125,   127,   129,   131,   133,
     135,   137,   139,   141,   143,   145,    27,    16,     0,     0,
       0,     0,     0,   156,   159,   161,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     154,     0,     0,     0,   155,   168,   169,   170,   171,   172,
     173,    29,    31,    35,    39,    41,    47,    49,    51,    53,
      55,    57,    59,    61,    63,    65,    67,    69,    71,    73,
      75,    77,    79,    81,    83,    85,    87,    89,   117,   119,
     162,   157,   158,   160
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     8,     4,     5,    10,    25,    13,    14,
      15,    16,    17,    18,    19,    26,    92,    93,   161,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     175,   242,   243,   244,   176,   177,    97,   178,    20,     6
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -218
static const yytype_int16 yypact[] =
{
      48,  -218,    74,  -218,    48,  -218,  -218,  -218,    28,  -218,
      14,  -218,  -218,    77,    78,  -218,    28,  -218,  -218,   202,
      68,  -218,  -218,  -218,  -218,    73,    75,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,   202,  -218,  -218,    75,  -218,  -218,  -218,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    82,    82,    82,  -218,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,  -218,  -218,
    -218,    84,    25,    55,    55,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,    85,    87,    91,    93,  -218,  -218,  -218,    94,
    -218,    95,  -218,    96,   106,  -218,  -218,   107,   108,   109,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,   131,   132,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,    55,    85,
      87,    91,    29,   105,  -218,  -218,    33,    10,    41,    45,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    27,
    -218,    55,    55,    55,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,   105,   105,  -218
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -218,  -218,  -218,  -218,  -218,   138,  -218,  -218,  -218,  -218,
     133,  -218,   177,   135,  -218,  -218,  -218,    51,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -100,  -134,  -217,  -138,   -46,   -16,  -218,    49,  -218,  -218
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     246,   320,    21,    22,    23,   280,    24,    11,    12,   165,
     166,   285,   286,   222,   223,   224,   284,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   238,     1,
     281,   282,   281,   282,   321,   322,   281,   282,    94,   165,
     166,    30,   287,   288,     7,    98,   289,   290,   167,   168,
     169,   170,   171,   239,   240,   241,    11,   163,    12,    95,
      96,    30,   236,   247,   164,   248,   165,   166,    30,   249,
     250,   251,   252,   253,   279,   167,   168,   169,   170,   171,
     172,   173,   174,   254,   255,   256,   257,   245,   245,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     283,    94,     9,   160,   162,   323,   237,    28,    27,     0,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   245,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   245,   245,   245,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91
};

static const yytype_int16 yycheck[] =
{
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     164,     4,    18,    19,    20,     6,    22,     9,    10,    14,
      15,    31,    32,   143,   144,   145,    13,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,     3,    11,
      33,    34,    33,    34,   281,   282,    33,    34,    19,    14,
      15,    16,    31,    32,     0,    26,    31,    32,    23,    24,
      25,    26,    27,    28,    29,    30,     9,     5,    10,    21,
      17,    16,     8,     8,    12,     8,    14,    15,    16,     8,
       7,     7,     7,     7,   238,    23,    24,    25,    26,    27,
      28,    29,    30,     7,     7,     7,     7,   163,   164,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
      35,    92,     4,    92,    95,   283,   162,    14,    13,    -1,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   238,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   281,   282,   283,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    98,    99,   101,   102,   186,     0,   100,   102,
     103,     9,    10,   105,   106,   107,   108,   109,   110,   111,
     185,    18,    19,    20,    22,   104,   112,   110,   107,   109,
      16,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,   113,   114,   184,    21,    17,   183,   184,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     114,   115,   184,     5,    12,    14,    15,    23,    24,    25,
      26,    27,    28,    29,    30,   177,   181,   182,   184,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,     8,   182,     3,    28,
      29,    30,   178,   179,   180,   181,   178,     8,     8,     8,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,   178,
       6,    33,    34,    35,    13,    31,    32,    31,    32,    31,
      32,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
       4,   179,   179,   180
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
        case 3:

    { yy_code->m_pragma   = (yyvsp[(1) - (1)].TPRAGMA); ;}
    break;

  case 4:

    { yy_code->m_function = (yyvsp[(3) - (3)].TFUNCTION); ;}
    break;

  case 5:

    { (yyval.TPRAGMA) = (yyvsp[(1) - (2)].TPRAGMA)->add((yyvsp[(2) - (2)].TPRAGMA)); ;}
    break;

  case 6:

    { (yyval.TPRAGMA) = (yyvsp[(1) - (1)].TPRAGMA); ;}
    break;

  case 7:

    { UPD_LINENO ;}
    break;

  case 8:

    { (yyval.TPRAGMA) = new WarAnts::Asm::Pragma((yyvsp[(3) - (4)].TPRAGMATYPE), (yyvsp[(4) - (4)].TSTRING)->get(), yy_code.get()); ;}
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

  case 12:

    { (yyval.TPRAGMATYPE) = WarAnts::Asm::PragmaType::Core; ;}
    break;

  case 16:

    { yy_code->m_defines[(yyvsp[(3) - (4)].TSTRING)->get()] = (yyvsp[(4) - (4)].TINEGER); ;}
    break;

  case 17:

    { (yyval.TFUNCTION) = (yyvsp[(1) - (2)].TFUNCTION)->add((yyvsp[(2) - (2)].TFUNCTION)); ;}
    break;

  case 18:

    { (yyval.TFUNCTION) = (yyvsp[(1) - (1)].TFUNCTION); ;}
    break;

  case 19:

    { (yyval.TFUNCTION) = (yyvsp[(2) - (2)].TFUNCTION); ;}
    break;

  case 20:

    { (yyval.TFUNCTION) = (yyvsp[(1) - (1)].TFUNCTION); ;}
    break;

  case 21:

    { (yyval.TFUNCTION) = new WarAnts::Asm::Function((yyvsp[(1) - (2)].TSTRING), (yyvsp[(2) - (2)].TSTATETMENT), yy_code.get()); ;}
    break;

  case 22:

    { UPD_LINENO ;}
    break;

  case 23:

    { (yyval.TSTRING) = (yyvsp[(3) - (3)].TSTRING); ;}
    break;

  case 24:

    { (yyval.TSTATETMENT) = (yyvsp[(1) - (2)].TSTATETMENT)->add((yyvsp[(2) - (2)].TSTATETMENT)); ;}
    break;

  case 25:

    { (yyval.TSTATETMENT) = (yyvsp[(1) - (1)].TSTATETMENT); ;}
    break;

  case 26:

    { UPD_LINENO ;}
    break;

  case 27:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement((yyvsp[(1) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 28:

    { UPD_LINENO ;}
    break;

  case 29:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::ADD , (yyvsp[(3) - (5)].TEXPR),      (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 30:

    { UPD_LINENO ;}
    break;

  case 31:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::AND , (yyvsp[(3) - (5)].TEXPR),      (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 32:

    { UPD_LINENO ;}
    break;

  case 33:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::DEC , (yyvsp[(3) - (3)].TEXPR), nullptr, yy_code.get()); ;}
    break;

  case 34:

    { UPD_LINENO ;}
    break;

  case 35:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::DIV , (yyvsp[(3) - (5)].TEXPR),      (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 36:

    { UPD_LINENO ;}
    break;

  case 37:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::INC , (yyvsp[(3) - (3)].TEXPR), nullptr, yy_code.get()); ;}
    break;

  case 38:

    { UPD_LINENO ;}
    break;

  case 39:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MOD , (yyvsp[(3) - (5)].TEXPR),      (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 40:

    { UPD_LINENO ;}
    break;

  case 41:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MUL , (yyvsp[(3) - (5)].TEXPR),      (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 42:

    { UPD_LINENO ;}
    break;

  case 43:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::NEG , (yyvsp[(3) - (3)].TEXPR), nullptr, yy_code.get()); ;}
    break;

  case 44:

    { UPD_LINENO ;}
    break;

  case 45:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::NOT , (yyvsp[(3) - (3)].TEXPR), nullptr, yy_code.get()); ;}
    break;

  case 46:

    { UPD_LINENO ;}
    break;

  case 47:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::OR  , (yyvsp[(3) - (5)].TEXPR),      (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 48:

    { UPD_LINENO ;}
    break;

  case 49:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::SUB , (yyvsp[(3) - (5)].TEXPR),      (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 50:

    { UPD_LINENO ;}
    break;

  case 51:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::XOR , (yyvsp[(3) - (5)].TEXPR),      (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 52:

    { UPD_LINENO ;}
    break;

  case 53:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MIN , (yyvsp[(3) - (5)].TEXPR),      (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 54:

    { UPD_LINENO ;}
    break;

  case 55:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MAX , (yyvsp[(3) - (5)].TEXPR),      (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 56:

    { UPD_LINENO ;}
    break;

  case 57:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BSF , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 58:

    { UPD_LINENO ;}
    break;

  case 59:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BSR , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 60:

    { UPD_LINENO ;}
    break;

  case 61:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BT  , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 62:

    { UPD_LINENO ;}
    break;

  case 63:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BTR , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 64:

    { UPD_LINENO ;}
    break;

  case 65:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BTS , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 66:

    { UPD_LINENO ;}
    break;

  case 67:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::BTC , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 68:

    { UPD_LINENO ;}
    break;

  case 69:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::SHL , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 70:

    { UPD_LINENO ;}
    break;

  case 71:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::SHR , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 72:

    { UPD_LINENO ;}
    break;

  case 73:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::ROL , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 74:

    { UPD_LINENO ;}
    break;

  case 75:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::ROR , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 76:

    { UPD_LINENO ;}
    break;

  case 77:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::EQ  , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 78:

    { UPD_LINENO ;}
    break;

  case 79:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::NEQ , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 80:

    { UPD_LINENO ;}
    break;

  case 81:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::GT  , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 82:

    { UPD_LINENO ;}
    break;

  case 83:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::GE  , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 84:

    { UPD_LINENO ;}
    break;

  case 85:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LT  , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 86:

    { UPD_LINENO ;}
    break;

  case 87:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LE  , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 88:

    { UPD_LINENO ;}
    break;

  case 89:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::TEST, (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 90:

    { UPD_LINENO ;}
    break;

  case 91:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JMP , (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 92:

    { UPD_LINENO ;}
    break;

  case 93:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JZ  , (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 94:

    { UPD_LINENO ;}
    break;

  case 95:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JNZ , (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 96:

    { UPD_LINENO ;}
    break;

  case 97:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JNZ , (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 98:

    { UPD_LINENO ;}
    break;

  case 99:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JZ  , (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 100:

    { UPD_LINENO ;}
    break;

  case 101:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JO  , (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 102:

    { UPD_LINENO ;}
    break;

  case 103:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JNO , (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 104:

    { UPD_LINENO ;}
    break;

  case 105:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JS  , (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 106:

    { UPD_LINENO ;}
    break;

  case 107:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JNS , (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 108:

    { UPD_LINENO ;}
    break;

  case 109:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JCZ , (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 110:

    { UPD_LINENO ;}
    break;

  case 111:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::JCNZ, (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 112:

    { UPD_LINENO ;}
    break;

  case 113:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LOOP, (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 114:

    { UPD_LINENO ;}
    break;

  case 115:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CALL, (yyvsp[(3) - (3)].TSTRING)->get(), yy_code.get()); ;}
    break;

  case 116:

    { UPD_LINENO ;}
    break;

  case 117:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::MOV , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 118:

    { UPD_LINENO ;}
    break;

  case 119:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LEN , (yyvsp[(3) - (5)].TEXPR), (yyvsp[(5) - (5)].TEXPR), yy_code.get()); ;}
    break;

  case 120:

    { UPD_LINENO ;}
    break;

  case 121:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::DIST, (yyvsp[(3) - (3)].TEXPR), nullptr, yy_code.get()); ;}
    break;

  case 122:

    { UPD_LINENO ;}
    break;

  case 123:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::RET ,              yy_code.get()); ;}
    break;

  case 124:

    { UPD_LINENO ;}
    break;

  case 125:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::DBG , nullptr, (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 126:

    { UPD_LINENO ;}
    break;

  case 127:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LDRC, nullptr, (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 128:

    { UPD_LINENO ;}
    break;

  case 129:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LDFD, nullptr, (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 130:

    { UPD_LINENO ;}
    break;

  case 131:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LDEN, nullptr, (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 132:

    { UPD_LINENO ;}
    break;

  case 133:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::LDAL, nullptr, (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 134:

    { UPD_LINENO ;}
    break;

  case 135:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CIDL , nullptr, (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 136:

    { UPD_LINENO ;}
    break;

  case 137:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CMOV , (yyvsp[(3) - (3)].TEXPR), nullptr, yy_code.get()); ;}
    break;

  case 138:

    { UPD_LINENO ;}
    break;

  case 139:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CATT , (yyvsp[(3) - (3)].TEXPR), nullptr, yy_code.get()); ;}
    break;

  case 140:

    { UPD_LINENO ;}
    break;

  case 141:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CTKF , (yyvsp[(3) - (3)].TEXPR), nullptr, yy_code.get()); ;}
    break;

  case 142:

    { UPD_LINENO ;}
    break;

  case 143:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CGVF , (yyvsp[(3) - (3)].TEXPR), nullptr, yy_code.get()); ;}
    break;

  case 144:

    { UPD_LINENO ;}
    break;

  case 145:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CEAT , nullptr, (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 146:

    { UPD_LINENO ;}
    break;

  case 147:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CCSL ,              yy_code.get()); ;}
    break;

  case 148:

    { UPD_LINENO ;}
    break;

  case 149:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statement(WarAnts::Asm::AsmCommand::CCWR ,              yy_code.get()); ;}
    break;

  case 150:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 151:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::PReg(WarAnts::Asm::Register::P0X), yy_code.get()); ;}
    break;

  case 152:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::PReg(WarAnts::Asm::Register::P1X), yy_code.get()); ;}
    break;

  case 153:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::PReg(WarAnts::Asm::Register::P2X), yy_code.get()); ;}
    break;

  case 154:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression((yyvsp[(2) - (3)].TEXPR), false, yy_code.get()); ;}
    break;

  case 155:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression((yyvsp[(2) - (3)].TEXPR), true,  yy_code.get()); ;}
    break;

  case 156:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 157:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Plus,  (yyvsp[(1) - (3)].TEXPR), (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 158:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Minus, (yyvsp[(1) - (3)].TEXPR), (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 159:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 160:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Star, (yyvsp[(1) - (3)].TEXPR), (yyvsp[(3) - (3)].TEXPR), yy_code.get()); ;}
    break;

  case 161:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 162:

    { (yyval.TEXPR) = (yyvsp[(2) - (3)].TEXPR); ;}
    break;

  case 163:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::R0),  yy_code.get()); ;}
    break;

  case 164:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::R1),  yy_code.get()); ;}
    break;

  case 165:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::R2),  yy_code.get()); ;}
    break;

  case 166:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::RC),  yy_code.get()); ;}
    break;

  case 167:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::RF),  yy_code.get()); ;}
    break;

  case 168:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P0X), yy_code.get()); ;}
    break;

  case 169:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P0Y), yy_code.get()); ;}
    break;

  case 170:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P1X), yy_code.get()); ;}
    break;

  case 171:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P1Y), yy_code.get()); ;}
    break;

  case 172:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P2X), yy_code.get()); ;}
    break;

  case 173:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::CReg(WarAnts::Asm::Register::P2Y), yy_code.get()); ;}
    break;

  case 174:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression((yyvsp[(1) - (1)].TINEGER), yy_code.get()); ;}
    break;

  case 175:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(getDefine((yyvsp[(1) - (1)].TSTRING)->get()), yy_code.get()); ;}
    break;

  case 176:

    { (yyval.TINEGER) = getIntNumber(yytext); ;}
    break;

  case 177:

    { (yyval.TINEGER) = getHexNumber(yytext); ;}
    break;

  case 178:

    { (yyval.TSTRING) = new WarAnts::Asm::StringNode(yytext, yy_code.get()); ;}
    break;

  case 179:

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

