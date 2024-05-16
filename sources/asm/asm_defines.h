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

//union Int16And8
//{
//    int16_t i16;
//    int8_t i8[2];
//};

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

namespace Register
{
enum Type : uint8_t
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
    RF,
    RD,
    RS,
    RESERVED, // 15

    MASK = 0x1f,
    POSITION = 0x10,
    ADDRESS = 0x20,
    INVALIDE = 0xff
};

enum Flag
{
    ZF = 0x01,
    OF = 0x02,
    SF = 0x04,
};

} //namespace Register

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

    JMP, // 0
    JZ,
    JNZ,
    JO,
    JNO,
    JS,
    JNS,
    JCZ,
    JCNZ,
    LOOP,
    CALL, // 10

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

namespace BCode
{
enum Type : uint8_t
{
    TYPE_COMMON = 0x00,
    TYPE_POSITION = 0x20,
    TYPE_JUMP = 0x40,
    TYPE_VALUE = 0x60
};

enum Jump : uint8_t
{
    JUMP_CHAR = 0x00,
    JUMP_SHORT = 0x01,

    JUMP_MASK = 0x01,
};

enum Value : uint8_t
{
    VALUE_REGISTER = 0x00,
    VALUE_CHAR = 0x01,
    VALUE_SHORT = 0x02,
    VALUE_UNDEFINED = 0x03,
    
    VALUE_MASK = 0x03,
};

enum Command : int8_t
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
    JZ = 0x42,
    JNZ = 0x44,
    JO = 0x46,
    JNO = 0x48,
    JS = 0x4a,
    JNS = 0x4c,
    JCZ = 0x4e,
    JCNZ = 0x50,
    LOOP = 0x52,
    CALL = 0x54,
    // max 0x5e (5 free)

    LDTR = 0x60,
    LDFD = 0x64,
    LDEN = 0x68,
    LDFR = 0x6c,
    CIDL = 0x70,
    CEAT = 0x74,
    // max 0x7c (2 free)
};
}; // namespace BCode

}; // namespace Asm
}; // namespace WarAnts
