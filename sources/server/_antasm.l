%option noyywrap
%option yylineno

delim     [ \t\r]
new_line  [\n]
NQUOTE    [^"]

num       ("-")*[0-9]+

%%

{delim}+                      { ; }
{num}                         { return NUMBER; }
\"({NQUOTE}|"")+\"            { return CHARACTER_STRING; }
{new_line}                    { return NEW_LINE; }

"("                           { return _LP_;                     }
")"                           { return _RP_;                     }
";"                           { return _SEMICOLON_;              }
","                           { return _COMMA_;                  }

"pit"                         { return _PIT_;                    }
"desk"                        { return _DESK_;                   }

"damage"                      { return _DAMAGE_;                 }
"health"                      { return _HEALTH_;                 }
"hand"                        { return _HAND_;                   }

"all_elements"                { return _ALL_MANA_;               }
"fire"                        { return _FIRE_;                   }
"water"                       { return _WATER_;                  }
"air"                         { return _AIR_;                    }
"earth"                       { return _EARTH_;                  }

"enemy"                       { return _ENEMY_;                  }
"you"                         { return _YOU_;                    }
"all_player"                  { return _ALL_PLAYER_;             }

"any_ench"                    { return _ANY_ENCH_;               }

"take"                        { return _TAKE_;                   }
"cost"                        { return _COST_;                   }
"enchant.cop"                 { return _ENCHANT_COP_;            }
"enchant.cop_drop"            { return _ENCHANT_COP_DROP_;       }
"enchant.drop"                { return _ENCHANT_DROP_;           }
"enchant.drop_next_turn"      { return _ENCHANT_DROP_NEXT_TURN_; }
"owner.no_drop_card"          { return _OWNER_NO_DROP_CARD_;     }
"owner.glass"                 { return _OWNER_GLASS_;            }
"owner.next_turn"             { return _OWNER_NEXT_TURN_;        }
"card.take"                   { return _CARD_TAKE_;              }
"card.drop"                   { return _CARD_DROP_;              }
"card.begin_of_turn"          { return _CARD_BEGIN_OF_TURN_;     }
"change"                      { return _CHANGE_;                 }
"suffle"                      { return _SHUFLE_;                 }
"addmana"                     { return _ADD_MANA_;               }

.                             { return yytext[0];                }

%%


