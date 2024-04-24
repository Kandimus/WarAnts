#pragma once

#include <stdint.h>

#include <vector>

namespace Core {

class Hardware
{
public:
    Hardware() = default;
    Hardware(const Hardware& h) { *this = h; }
    virtual ~Hardware() = default;

public:
    std::vector<int16_t> m_memory;
    int16_t m_register[6]; // AX, BX, CX, DX, EX, FX (�����?)
    std::vector<int16_t> m_recieve; // R0, R1 + �� ���� �������� ���-�� ������� ��������� � ������� ������
    int16_t m_send[2]; // S0, S1
};

};
