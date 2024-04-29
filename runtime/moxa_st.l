%{
#define YY_NO_UNISTD_H
#include <io.h>

void stlexRem1(void);
void stlexRem2();

%}

%option noyywrap
%option yylineno

delim     [ \t\r\n]
ws        {delim}+

digit     [0-9]
hexdigit  [0-9a-fA-F]

float     {digit}+"."{digit}+
uint      {digit}+
hex       "0x"{hexdigit}+

id        [a-zA-Z_]([a-zA-Z0-9_])*

%%

"VAR_REF"                                        { return _VAR_REF_;       }
"END_VAR_REF"                                    { return _END_VAR_REF_;   }
"ELSE"                                           { return _ELSE_;          }
"ELSIF"                                          { return _ELSIF_;         }
"END_IF"                                         { return _END_IF_;        }
"RETURN"                                         { return _RETURN_;        }
"IF"                                             { return _IF_;            }
"THEN"                                           { return _THEN_;          }

"GetSysReg"                                      { return _GET_REG_SYS_;   }
"GetReg"                                         { return _GET_REG_;       }
"GetReg4x"                                       { return _GET_REG_4X_;    }
"GetReg3x"                                       { return _GET_REG_3X_;    }

"SetReg"                                         { return _SET_REG_;       }
"SetReg4x"                                       { return _SET_REG_4X_;    }
"SetReg3x"                                       { return _SET_REG_3X_;    }

"Copy"                                           { return _COPY_;          }
"Copy3xTo3x"                                     { return _COPY_33_;       }
"Copy3xTo4x"                                     { return _COPY_34_;       }
"Copy4xTo3x"                                     { return _COPY_43_;       }
"Copy4xTo4x"                                     { return _COPY_44_;       }

"SaveDump"                                       { return _SAVE_DUMP_;     }
"DeleteDump"                                     { return _DELETE_DUMP_;   }
"CopyDump"                                       { return _COPY_DUMP_;     }
"CheckStorage"                                   { return _CHECK_STORAGE_; }

"CreateUTime"                                    { return _CREATEUTIME_;   }


"ABS"                                            { return _ABS_;           }
"SQRT"                                           { return _SQRT_;          }
"LN"                                             { return _LN_;            }
"LOG"                                            { return _LOG_;           }
"RAND"                                           { return _RAND_;          }
"POW"                                            { return _POW_;           }
"ODD"                                            { return _ODD_;           }
"SIGN"                                           { return _SGN_;           }
"SIN"                                            { return _SIN_;           }
"ATN"                                            { return _ATN_;           }
"COS"                                            { return _COS_;           }
"EXP"                                            { return _EXP_;           }
"FIX"                                            { return _FIX_;           }
"INT"                                            { return _INT_;           }
"TAN"                                            { return _TAN_;           }
"ROUND"                                          { return _ROUND_;         }

"WORD_TO_INT"                                    { return _WORD_TO_INT_;   }
"WORD_TO_DWORD"                                  { return _WORD_TO_DWORD_; }
"WORD_TO_LONG"                                   { return _WORD_TO_LONG_;  }
"WORD_TO_REAL"                                   { return _WORD_TO_REAL_;  }
"WORD_TO_BOOL"                                   { return _WORD_TO_BOOL_;  }
"INT_TO_WORD"                                    { return _INT_TO_WORD_;   }
"INT_TO_DWORD"                                   { return _INT_TO_DWORD_;  }
"INT_TO_LONG"                                    { return _INT_TO_LONG_;   }
"INT_TO_REAL"                                    { return _INT_TO_REAL_;   }
"INT_TO_BOOL"                                    { return _INT_TO_BOOL_;   }
"DWORD_TO_WORD"                                  { return _DWORD_TO_WORD_; }
"DWORD_TO_INT"                                   { return _DWORD_TO_INT_;  }
"DWORD_TO_LONG"                                  { return _DWORD_TO_LONG_; }
"DWORD_TO_REAL"                                  { return _DWORD_TO_REAL_; }
"DWORD_TO_BOOL"                                  { return _DWORD_TO_BOOL_; }
"LONG_TO_WORD"                                   { return _LONG_TO_WORD_;  }
"LONG_TO_INT"                                    { return _LONG_TO_INT_;   }
"LONG_TO_DWORD"                                  { return _LONG_TO_DWORD_; }
"LONG_TO_REAL"                                   { return _LONG_TO_REAL_;  }
"LONG_TO_BOOL"                                   { return _LONG_TO_BOOL_;  }
"REAL_TO_WORD"                                   { return _REAL_TO_WORD_;  }
"REAL_TO_INT"                                    { return _REAL_TO_INT_;   }
"REAL_TO_LONG"                                   { return _REAL_TO_LONG_;  }
"REAL_TO_DWORD"                                  { return _REAL_TO_DWORD_; }
"REAL_TO_BOOL"                                   { return _REAL_TO_BOOL_;  }
"BOOL_TO_WORD"                                   { return _BOOL_TO_WORD_;  }
"BOOL_TO_INT"                                    { return _BOOL_TO_INT_;   }
"BOOL_TO_DWORD"                                  { return _BOOL_TO_DWORD_; }
"BOOL_TO_LONG"                                   { return _BOOL_TO_LONG_;  }
"BOOL_TO_REAL"                                   { return _BOOL_TO_REAL_;  }

"TRUE"                                           { return _TRUE_;          }
"FALSE"                                          { return _FALSE_;         }

"%4"{uint}                                       { st_Reg->Init(REG_4X , STT_WORD , yytext + 2, -1); return _REG_; }
"%M"{uint}                                       { st_Reg->Init(REG_4X , STT_WORD , yytext + 2, -1); return _REG_; }
"%MW"{uint}                                      { st_Reg->Init(REG_4X , STT_WORD , yytext + 3, -1); return _REG_; }
"%MI"{uint}                                      { st_Reg->Init(REG_4X , STT_INT  , yytext + 3, -1); return _REG_; }
"%MD"{uint}                                      { st_Reg->Init(REG_4X , STT_DWORD, yytext + 3, -1); return _REG_; }
"%ML"{uint}                                      { st_Reg->Init(REG_4X , STT_LONG , yytext + 3, -1); return _REG_; }
"%MR"{uint}                                      { st_Reg->Init(REG_4X , STT_REAL , yytext + 3, -1); return _REG_; }

"%3"{uint}                                       { st_Reg->Init(REG_3X , STT_WORD , yytext + 2, -1); return _REG_; }
"%I"{uint}                                       { st_Reg->Init(REG_3X , STT_WORD , yytext + 2, -1); return _REG_; }
"%IW"{uint}                                      { st_Reg->Init(REG_3X , STT_WORD , yytext + 3, -1); return _REG_; }
"%II"{uint}                                      { st_Reg->Init(REG_3X , STT_INT  , yytext + 3, -1); return _REG_; }
"%ID"{uint}                                      { st_Reg->Init(REG_3X , STT_DWORD, yytext + 3, -1); return _REG_; }
"%IL"{uint}                                      { st_Reg->Init(REG_3X , STT_LONG , yytext + 3, -1); return _REG_; }
"%IR"{uint}                                      { st_Reg->Init(REG_3X , STT_REAL , yytext + 3, -1); return _REG_; }

"%C"{uint}                                       { st_Reg->Init(REG_SYS, STT_BOOL , yytext + 2, -1); return _REG_; }

{uint}                                           { return _UNSINGED_INT_;  }
{float}                                          { return _REALNUMBER_;    }
{hex}                                            { return _DIGHEX_;        }

{ws}                                             ;
                                                
"OR"                                             { return _OR_;            }
"AND"                                            { return _AND_;           }
"XOR"                                            { return _XOR_;         }
"|"                                              { return _BOR_;         }
"&"                                              { return _BAND_;        }
"~"                                              { return _BINV_;        }
"MOD"                                            { return _MOD_;         }
"NOT"                                            { return _NOT_;         }
">="                                             { return _GE_;          }
">"                                              { return _GT_;          }
"<="                                             { return _LE_;          }
"<"                                              { return _LT_;          }
"<>"                                             { return _NEQUAL_;      }
"="                                              { return _EQUAL_;       }
":="                                             { return _ASSIGN_;      }
"-"                                              { return _MINUS_;       }
"+"                                              { return _PLUS_;        }
"/"                                              { return _SLASH_;       }
"*"                                              { return _STAR_;        }
"["                                              { return _LBRACKET_;    }
"]"                                              { return _RBRACKET_;    }
"{"                                              { return _LBRACE_;      }
"}"                                              { return _RBRACE_;      }
"("                                              { return _LPAREN_;      }
")"                                              { return _RPAREN_;      }
"."                                              { return _DOT_;         }
";"                                              { return _SEMICOLON_;   }
":"                                              { return _COLON_;       }
","                                              { return _COMMA_;       }
                                               
"(*"                                             { stlexRem1();          }
"//"                                             { stlexRem2();          }

{id}                                             { return _ID_;           }

.                                                { SetError(st_lineno, "Unknow char '%c'", yytext[0]); }


%%

void stlexRem1(void)
{
	int c;
	while((c = yyinput()))
	{
		if('*' == c)
		{
			if(')' == (c = yyinput()))
			{
				break;
			}
			else
			{
				unput(c);
			}
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
					SetError(st_lineno, "Not closed comment. End of file.");
				}
			}
		}
	}
}


void stlexRem2(void)
{
	int c;
	while ((c = yyinput()))
	{
		if('\r' == c || '\n' == c)
		{
			//++stlineno;
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

//"BY"                    { return _BY_;          }
//"CASE"                  { return _CASE_;        }
//"DO"                    { return _DO_;          }
//"END_CASE"              { return _END_CASE_;    }
//"END_FOR"               { return _END_FOR_;     }
//"END_REPEAT"            { return _END_REPEAT_;  }
//"END_WHILE"             { return _END_WHILE_;   }
//"FOR"                   { return _FOR_;         }
//"OF"                    { return _OF_;          }
//"REPEAT"                { return _REPEAT_;      }
//"TO"                    { return _TO_;          }
//"UNTIL"                 { return _UNTIL_;       }
//"WHILE"                 { return _WHILE_;       }


/* {id}                          { return _LABEL_;                       }*/
// \"({NQUOTE}|"")+\"            { return _STRING_;      }
//{int}                         { return _SINGED_INT_;  }
//"\n"                          { ++stlineno; }