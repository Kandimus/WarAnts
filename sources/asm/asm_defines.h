#pragma once

#include <stdio.h>
#include <stdint.h>

#define NOCOPY_STRUCT(name)                 name(const name&) = delete;name(name&&) = delete;name& operator =(const name&) = delete;
#define DELETE_POINTER(x)                   { if (x) { delete x; x = nullptr; } }

namespace WarAnts
{
namespace Asm
{

enum Version : uint16_t
{
    Core = 0x0100,
};

union Int16And8
{
    int16_t i16;
    int8_t i8[2];
};

enum class PragmaType
{
    Class,
    Name,
    Version,
    Core,
};


enum class ExpressionType
{
    Register,
    Number,
    Operand,
    Address,
};

enum class OperandType
{
    Plus,
    Minus,
    Star,
};

enum class RegisterType
{
    R0 = 0,
    R1,
    R2,
    RC,
    P0X,
    P0Y,
    P1X,
    P1Y,
    P2X,
    P2Y,
    CHAR,
    SHORT,
    RESERVED,
    RF,
    RD,
    RS,
    P0,
    P1,
    P2,

    ADDRESS = 128,
    INVALIDE = 255
};

/*

+--
| 0...
+--


*/


enum class AsmCommand
{
    UNDEF = 0,

    ADD,
    AND,
    DEC,
    DIV,
    INC,
    MOD,
    MUL,
    NEG,
    NOT,
    OR,
    SUB,
    XOR,
    MIN,
    MAX,

    BSF,
    BSR,
    BT,
    BTR,
    BTS,
    BTC,
    SHL,
    SHR,
    ROL,
    ROR,

    EQ,
    NEQ,
    GT,
    GE,
    LT,
    LE,
    TEST,

    JMP,
    JZ,
    JNZ,
    JO,
    JNO,
    JCZ,
    JCNZ,
    LOOP,
    CALL,

    MOV,
    LEN,
    DIST,
    EXIT,

    LDTR,
    LDFD,
    LDEN,
    LDFR,

    CIDL,
    CMOV,
    CATT,
    CTKF,
    CGVF,
    CEAT,
    CPS,
    CPW,

    NOP
};

/*

+---+-----+-----------------+
| 0 | 0 0 | X  X  X   X   X |
+---+-----+-----------------+
| 0 | 0 1 | X  X  X   X   X |
+---+-----+-------------+---+
| 0 | 1 0 | X  X  X   X | Y |  X - number of jump command, Y - 0 - char, 1 - short
+---+-----+---------+---+---+
| 0 | 1 1 | X  X  X | Y   Y |  X - number of value command, Y - 00 - using next char as register, 01 - char, 10 - short, 11 - undefined
+---+-----+---------+-------+

*/

enum class BCodeType : int8_t
{
    COMMON = 0x00,
    POSITION = 0x20,
    JUMP = 0x40,
    VALUE = 0x60
};

enum class BCodeJump : int8_t
{
    CHAR = 0x00,
    SHORT = 0x01
};

enum class BCodeValue : int8_t
{
    REGISTER = 0x00,
    CHAR = 0x01,
    SHORT = 0x10,
    UNDEFINED = 0x11
};

enum class BCodeCommand : int8_t
{
    NOP = 0,

    ADD,
    AND,
    DEC,
    DIV,
    INC,
    MOD,
    MUL,
    NEG,
    NOT,
    OR,
    SUB,
    XOR,
    MIN,
    MAX,

    BSF,
    BSR,
    BT,
    BTR,
    BTS,
    BTC,
    SHL,
    SHR,
    ROL,
    ROR,

    EQ,
    NEQ,
    GT,
    GE,
    LT,
    LE,
    TEST,

    MOV,
    LEN,
    DIST,
    EXIT,

    CMOV,
    CATT,
    CTKF,
    CGVF,
    CPS,
    CPW,

    JMP = 0x40,
    JMPl = 0x41,
    JZ = 0x42,
    JZl = 0x43,
    JNZ = 0x44,
    JNZl = 0x45,
    JO = 0x46,
    JOl = 0x47,
    JNO = 0x48,
    JNOl = 0x49,
    JCZ = 0x4a,
    JCZl = 0x4b,
    JCNZ = 0x4c,
    JCNZl = 0x4d,
    LOOP = 0x4e,
    LOOPl = 0x4f,
    CALL = 0x50,
    CALLl = 0x51,

    LDTR = 0x60,
    LDFD = 0x64,
    LDEN = 0x68,
    LDFR = 0x6c,
    CIDL = 0x70,
    CEAT = 0x74,
};

}; // namespace Asm
}; // namespace WarAnts
