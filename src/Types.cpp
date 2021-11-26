#include "Types.hpp"

std::string ByteArrayToHexStr(uint8 const* bytes, size_t arrayLen, bool reverse)
{
  int32 init = 0;
  int32 end  = arrayLen;
  int8  op   = 1;

  if (reverse)
  {
    init = arrayLen - 1;
    end  = -1;
    op   = -1;
  }

  std::ostringstream ss;
  for (int32 i = init; i != end; i += op)
  {
    char buffer[4];
    sprintf(buffer, "%02X", bytes[i]);
    ss << buffer;
  }

  return ss.str();
};

bool StringToBool(const std::string& str)
{
  std::string lower = str;

  std::transform(str.begin(), str.end(), lower.begin(), [](char c){ 
      return char(::tolower(c)); });

  return lower == "1" || lower == "true" || lower == "yes";
};
