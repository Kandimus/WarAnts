#pragma once

#include <stdio.h>
#include <stdint.h>

#define NOCOPY_STRUCT(name)                 name(const name&) = delete;name(name&&) = delete;name& operator =(const name&) = delete;
#define DELETE_POINTER(x)                   { if (x) { delete x; x = nullptr; } }

