
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

#include <string>

#include "stringex.h"

#include "code.h"
#include "define.h"
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
    WarAnts::Asm::Define* TDEFINE;
    WarAnts::Asm::Function* TFUNCTION;
    WarAnts::Asm::Expression* TEXPR;
    WarAnts::Asm::Statetment* TSTATETMENT;
    WarAnts::Asm::Code* TCODE;
    std::string* TSTRING;
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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   266

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  237

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
       0,     0,     3,     7,    10,    12,    16,    18,    20,    22,
      25,    27,    28,    33,    36,    38,    41,    45,    48,    50,
      53,    56,    61,    66,    69,    74,    77,    82,    87,    90,
      93,    98,   103,   108,   113,   118,   123,   128,   133,   138,
     143,   148,   153,   158,   163,   168,   173,   178,   183,   188,
     193,   198,   203,   206,   209,   212,   215,   218,   221,   224,
     227,   232,   235,   240,   242,   245,   248,   251,   254,   257,
     262,   267,   272,   277,   280,   282,   284,   286,   288,   290,
     292,   296,   298,   302,   306,   308,   312,   314,   318,   320,
     322,   324,   326,   328,   330,   332,   334,   336,   338,   340
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      87,     0,    -1,    88,    91,    93,    -1,    88,    89,    -1,
      89,    -1,    90,    99,     8,    -1,    17,    -1,    15,    -1,
      16,    -1,    91,    92,    -1,    92,    -1,    -1,    18,   100,
     106,     8,    -1,    93,    94,    -1,    94,    -1,    95,    96,
      -1,    10,   100,     8,    -1,    96,    97,    -1,    97,    -1,
      98,     8,    -1,   100,     9,    -1,    30,   101,     7,   101,
      -1,    31,   101,     7,   101,    -1,    32,   101,    -1,    33,
     101,     7,   101,    -1,    34,   101,    -1,    35,   101,     7,
     101,    -1,    36,   101,     7,   101,    -1,    37,   101,    -1,
      38,   101,    -1,    39,   101,     7,   101,    -1,    40,   101,
       7,   101,    -1,    41,   101,     7,   101,    -1,    42,   101,
       7,   101,    -1,    43,   101,     7,   101,    -1,    44,   101,
       7,   101,    -1,    45,   101,     7,   101,    -1,    46,   101,
       7,   101,    -1,    47,   101,     7,   101,    -1,    48,   101,
       7,   101,    -1,    49,   101,     7,   101,    -1,    50,   101,
       7,   101,    -1,    51,   101,     7,   101,    -1,    52,   101,
       7,   101,    -1,    53,   101,     7,   101,    -1,    54,   101,
       7,   101,    -1,    55,   101,     7,   101,    -1,    56,   101,
       7,   101,    -1,    57,   101,     7,   101,    -1,    58,   101,
       7,   101,    -1,    59,   101,     7,   101,    -1,    60,   101,
       7,   101,    -1,    61,   100,    -1,    62,   100,    -1,    63,
     100,    -1,    64,   100,    -1,    65,   100,    -1,    66,   100,
      -1,    67,   100,    -1,    68,   100,    -1,    69,   101,     7,
     101,    -1,    70,   100,    -1,    71,   101,     7,   101,    -1,
      72,    -1,    73,   101,    -1,    74,   101,    -1,    75,   101,
      -1,    76,   101,    -1,    77,   101,    -1,    78,   101,     7,
     101,    -1,    79,   101,     7,   101,    -1,    80,   101,     7,
     101,    -1,    81,   101,     7,   101,    -1,    82,   101,    -1,
      83,    -1,    84,    -1,    85,    -1,    14,    -1,    13,    -1,
     102,    -1,     5,   102,     6,    -1,   103,    -1,   102,    27,
     103,    -1,   102,    28,   103,    -1,   104,    -1,   103,    29,
     104,    -1,   105,    -1,     3,   102,     4,    -1,    19,    -1,
      20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,
      25,    -1,    26,    -1,   106,    -1,   100,    -1,    11,    -1,
      12,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    75,    75,    81,    82,    86,    90,    91,    92,    96,
      97,    98,   102,   106,   107,   111,   115,   119,   120,   124,
     128,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   159,   160,   161,   162,   163,
     164,   165,   168,   169,   170,   171,   172,   173,   174,   175,
     178,   179,   180,   181,   184,   185,   186,   187,   190,   191,
     192,   193,   194,   195,   196,   197,   199,   205,   209,   213,
     214,   230,   231,   232,   236,   237,   241,   242,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   259,   260
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
  "code", "list_of_pragmas", "pragma_definition", "pragma",
  "list_of_defines", "define_declaration", "list_of_asm_functions",
  "asm_function", "asm_function_name", "list_of_commands",
  "asm_command_line", "asm_command", "quted_string", "label", "address",
  "expr_0", "expr_1", "expr_2", "expr_3", "number", 0
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
       0,    86,    87,    88,    88,    89,    90,    90,    90,    91,
      91,    91,    92,    93,    93,    94,    95,    96,    96,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    99,   100,   101,
     101,   102,   102,   102,   103,   103,   104,   104,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   106,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     1,     3,     1,     1,     1,     2,
       1,     0,     4,     2,     1,     2,     3,     2,     1,     2,
       2,     4,     4,     2,     4,     2,     4,     4,     2,     2,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     2,     2,     2,     2,     2,     2,     2,     2,
       4,     2,     4,     1,     2,     2,     2,     2,     2,     4,
       4,     4,     4,     2,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     8,     6,     0,    11,     4,     0,     1,     0,
       3,     0,    10,    77,     0,    78,     0,     0,     9,     2,
      14,     0,     5,    98,    99,     0,     0,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      63,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74,    75,    76,    15,    18,     0,     0,    12,    16,
       0,     0,    88,    89,    90,    91,    92,    93,    94,    95,
      97,     0,    79,    81,    84,    86,    96,     0,    23,     0,
      25,     0,     0,    28,    29,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    52,    53,    54,
      55,    56,    57,    58,    59,     0,    61,     0,    64,    65,
      66,    67,    68,     0,     0,     0,     0,    73,    17,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    87,
      80,    21,    82,    83,    85,    22,    24,    26,    27,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    60,    62,    69,    70,    71,    72
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    11,    12,    19,    20,    21,
      84,    85,    86,    14,   100,   101,   102,   103,   104,   105,
     106
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -82
static const yytype_int16 yypact[] =
{
      20,   -82,   -82,   -82,    41,    53,   -82,    44,   -82,    59,
     -82,    21,   -82,   -82,    55,   -82,    50,    59,   -82,    75,
     -82,   157,   -82,   -82,   -82,    78,    79,   -82,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    59,
      59,    59,    59,    59,    59,    59,    59,    54,    59,    54,
     -82,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,   -82,   -82,   -82,   157,   -82,    80,    81,   -82,   -82,
     240,   240,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,    82,     5,    62,   -82,   -82,   -82,    85,   -82,    86,
     -82,    87,    88,   -82,   -82,    89,    90,    91,    92,    93,
      94,   103,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,   121,   -82,   122,   -82,   -82,
     -82,   -82,   -82,   123,   124,   125,   126,   -82,   -82,   -82,
     -82,    26,    28,    54,   240,   240,   240,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,   -82,
     -82,   -82,    62,    62,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,   -82,   -82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -82,   -82,   -82,   130,   -82,   -82,   160,   -82,   153,   -82,
     -82,    52,   -82,   -82,    43,   -29,    -9,   -81,     7,   -82,
     158
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     199,    17,   164,   165,   200,     1,     2,     3,   145,     9,
     147,     8,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,    16,   164,   165,   164,   165,    90,    13,    91,
      26,    23,    24,    22,    87,    23,    24,    15,     1,     2,
       3,     9,    15,    92,    93,    94,    95,    96,    97,    98,
      99,   161,   162,   202,   203,    17,    88,    89,   159,   163,
     160,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   137,   138,   139,   140,   141,   142,   143,   144,
     177,   146,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,    87,   193,   194,
     195,   196,   197,   198,   201,    10,   158,     0,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
      15,    18,    27,   204,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    90,     0,     0,     0,     0,     0,     0,
       0,    23,    24,    15,     0,     0,     0,     0,     0,    92,
      93,    94,    95,    96,    97,    98,    99
};

static const yytype_int16 yycheck[] =
{
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
       4,    10,    27,    28,     6,    15,    16,    17,    67,    18,
      69,     0,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     9,    27,    28,    27,    28,     3,    14,     5,
      17,    11,    12,     8,    21,    11,    12,    13,    15,    16,
      17,    18,    13,    19,    20,    21,    22,    23,    24,    25,
      26,    90,    91,   164,   165,    10,     8,     8,     8,     7,
       9,    29,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,    59,    60,    61,    62,    63,    64,    65,    66,
       7,    68,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,    84,     7,     7,
       7,     7,     7,     7,   163,     5,    84,    -1,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
      13,    11,    19,   166,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    26
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    15,    16,    17,    87,    88,    89,    90,     0,    18,
      89,    91,    92,    14,    99,    13,   100,    10,    92,    93,
      94,    95,     8,    11,    12,   106,   100,    94,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    96,    97,    98,   100,     8,     8,
       3,     5,    19,    20,    21,    22,    23,    24,    25,    26,
     100,   101,   102,   103,   104,   105,   106,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   100,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,    97,     8,
       9,   102,   102,     7,    27,    28,    29,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     4,
       6,   101,   103,   103,   104,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101
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
        case 2:

    { (yyval.TCODE) = yy_result = new WarAnts::Asm::Code((yyvsp[(1) - (3)].TPRAGMA), (yyvsp[(2) - (3)].TDEFINE), (yyvsp[(3) - (3)].TFUNCTION)); ;}
    break;

  case 3:

    { (yyval.TPRAGMA) = (yyvsp[(1) - (2)].TPRAGMA)->add((yyvsp[(2) - (2)].TPRAGMA)); ;}
    break;

  case 4:

    { (yyval.TPRAGMA) = (yyvsp[(1) - (1)].TPRAGMA); ;}
    break;

  case 5:

    { (yyval.TPRAGMA) = new WarAnts::Asm::Pragma((yyvsp[(1) - (3)].TPRAGMATYPE), *(yyvsp[(2) - (3)].TSTRING)); delete (yyvsp[(2) - (3)].TSTRING); ;}
    break;

  case 6:

    { (yyval.TPRAGMATYPE) = WarAnts::Asm::PragmaType::Class; ;}
    break;

  case 7:

    { (yyval.TPRAGMATYPE) = WarAnts::Asm::PragmaType::Name; ;}
    break;

  case 8:

    { (yyval.TPRAGMATYPE) = WarAnts::Asm::PragmaType::Version; ;}
    break;

  case 9:

    { (yyval.TDEFINE) = (yyvsp[(1) - (2)].TDEFINE)->add((yyvsp[(2) - (2)].TDEFINE)); ;}
    break;

  case 10:

    { (yyval.TDEFINE) = (yyvsp[(1) - (1)].TDEFINE); ;}
    break;

  case 12:

    { (yyval.TDEFINE) = new WarAnts::Asm::Define(*(yyvsp[(2) - (4)].TSTRING), (yyvsp[(3) - (4)].TINEGER)); delete (yyvsp[(2) - (4)].TSTRING); ;}
    break;

  case 13:

    { (yyval.TFUNCTION) = (yyvsp[(1) - (2)].TFUNCTION)->add((yyvsp[(2) - (2)].TFUNCTION)); ;}
    break;

  case 14:

    { (yyval.TFUNCTION) = (yyvsp[(1) - (1)].TFUNCTION); ;}
    break;

  case 15:

    { (yyval.TFUNCTION) = new WarAnts::Asm::Function(*(yyvsp[(1) - (2)].TSTRING), (yyvsp[(2) - (2)].TSTATETMENT)); delete (yyvsp[(1) - (2)].TSTRING); ;}
    break;

  case 16:

    { (yyval.TSTRING) = (yyvsp[(2) - (3)].TSTRING); ;}
    break;

  case 17:

    { (yyval.TSTATETMENT) = (yyvsp[(1) - (2)].TSTATETMENT)->add((yyvsp[(2) - (2)].TSTATETMENT)); ;}
    break;

  case 18:

    { (yyval.TSTATETMENT) = (yyvsp[(1) - (1)].TSTATETMENT); ;}
    break;

  case 19:

    { (yyval.TSTATETMENT) = (yyvsp[(1) - (2)].TSTATETMENT); ;}
    break;

  case 20:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(*(yyvsp[(1) - (2)].TSTRING)); delete (yyvsp[(1) - (2)].TSTRING);;}
    break;

  case 21:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ADD , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 22:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::AND , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 23:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::DEC , (yyvsp[(2) - (2)].TEXPR), nullptr); ;}
    break;

  case 24:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::DIV , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 25:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::INC , (yyvsp[(2) - (2)].TEXPR), nullptr); ;}
    break;

  case 26:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MOD , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 27:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MUL , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 28:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NEG , (yyvsp[(2) - (2)].TEXPR), nullptr); ;}
    break;

  case 29:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NOT , (yyvsp[(2) - (2)].TEXPR), nullptr); ;}
    break;

  case 30:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::OR  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 31:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SUB , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 32:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::XOR , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 33:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MIN , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 34:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MAX , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 35:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BSF , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 36:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BSR , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 37:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BT  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 38:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTR , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 39:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTS , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 40:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::BTC , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 41:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SHL , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 42:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::SHR , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 43:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ROL , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 44:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::ROR , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 45:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::EQ  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 46:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NEQ , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 47:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::GT  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 48:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::GE  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 49:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LT  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 50:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LE  , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 51:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::TEST, (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 52:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JMP , *(yyvsp[(2) - (2)].TSTRING)); ;}
    break;

  case 53:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JZ  , *(yyvsp[(2) - (2)].TSTRING)); ;}
    break;

  case 54:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JNZ , *(yyvsp[(2) - (2)].TSTRING)); ;}
    break;

  case 55:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JO  , *(yyvsp[(2) - (2)].TSTRING)); ;}
    break;

  case 56:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JNO , *(yyvsp[(2) - (2)].TSTRING)); ;}
    break;

  case 57:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JCZ , *(yyvsp[(2) - (2)].TSTRING)); ;}
    break;

  case 58:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::JCNZ, *(yyvsp[(2) - (2)].TSTRING)); ;}
    break;

  case 59:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LOOP, *(yyvsp[(2) - (2)].TSTRING)); ;}
    break;

  case 60:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::MOV , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 61:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CALL, *(yyvsp[(2) - (2)].TSTRING)); ;}
    break;

  case 62:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LEN , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 63:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::EXIT, nullptr, nullptr); ;}
    break;

  case 64:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDTR, (yyvsp[(2) - (2)].TEXPR), nullptr); ;}
    break;

  case 65:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDFD, (yyvsp[(2) - (2)].TEXPR), nullptr); ;}
    break;

  case 66:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDEN, (yyvsp[(2) - (2)].TEXPR), nullptr); ;}
    break;

  case 67:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::LDFR, (yyvsp[(2) - (2)].TEXPR), nullptr); ;}
    break;

  case 68:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CIDL , (yyvsp[(2) - (2)].TEXPR), nullptr); ;}
    break;

  case 69:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CMOV , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 70:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CATT , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 71:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CTKF , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 72:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CGVF , (yyvsp[(2) - (4)].TEXPR), (yyvsp[(4) - (4)].TEXPR)); ;}
    break;

  case 73:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CEAT , (yyvsp[(2) - (2)].TEXPR), nullptr); ;}
    break;

  case 74:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CPS  , nullptr, nullptr); ;}
    break;

  case 75:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::CPW  , nullptr, nullptr); ;}
    break;

  case 76:

    { (yyval.TSTATETMENT) = new WarAnts::Asm::Statetment(WarAnts::Asm::AsmCommand::NOP  , nullptr, nullptr); ;}
    break;

  case 77:

    { (yyval.TSTRING) = new std::string(yytext); ;}
    break;

  case 78:

    { (yyval.TSTRING) = new std::string(yytext); ;}
    break;

  case 79:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 80:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression((yyvsp[(2) - (3)].TEXPR)); ;}
    break;

  case 81:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 82:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Plus, (yyvsp[(1) - (3)].TEXPR), (yyvsp[(3) - (3)].TEXPR)); ;}
    break;

  case 83:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Minus, (yyvsp[(1) - (3)].TEXPR), (yyvsp[(3) - (3)].TEXPR)); ;}
    break;

  case 84:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 85:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::OperandType::Star, (yyvsp[(1) - (3)].TEXPR), (yyvsp[(3) - (3)].TEXPR)); ;}
    break;

  case 86:

    { (yyval.TEXPR) = (yyvsp[(1) - (1)].TEXPR); ;}
    break;

  case 87:

    { (yyval.TEXPR) = (yyvsp[(2) - (3)].TEXPR); ;}
    break;

  case 88:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R0); ;}
    break;

  case 89:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R1); ;}
    break;

  case 90:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R2); ;}
    break;

  case 91:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::R3); ;}
    break;

  case 92:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::RC); ;}
    break;

  case 93:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::RF); ;}
    break;

  case 94:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::IF); ;}
    break;

  case 95:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(WarAnts::Asm::RegisterType::IR); ;}
    break;

  case 96:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression((yyvsp[(1) - (1)].TINEGER)); ;}
    break;

  case 97:

    { (yyval.TEXPR) = new WarAnts::Asm::Expression(*(yyvsp[(1) - (1)].TSTRING)); ;}
    break;

  case 98:

    { (yyval.TINEGER) = getIntNumber(yytext); ;}
    break;

  case 99:

    { (yyval.TINEGER) = getHexNumber(yytext); ;}
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

