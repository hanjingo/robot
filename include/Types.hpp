#pragma once

#include <algorithm>
#include <cinttypes>
#include <sstream>
#include <string>

typedef int64_t  int64;
typedef int32_t  int32;
typedef int16_t  int16;
typedef int8_t   int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t  uint8;

std::string ByteArrayToHexStr(uint8 const* bytes, size_t arrayLen, bool reverse);
bool StringToBool(const std::string& str);