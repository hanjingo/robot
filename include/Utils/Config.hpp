#pragma once

#include "Types.hpp"
#include <string>
#include <vector>

namespace Robot {

class Config
{
  Config() = default;
  Config(const Config&) = delete;
  Config& operator=(const Config&) = delete;
  ~Config() = default;

public:
  bool LoadInitial(const std::string& file, std::vector<std::string> args, std::string& error);
  static Config* Instance();
  bool Reload(std::string& error);
  
  std::string DefaultString(const std::string& name, const std::string& def) const;
  bool DefaultBool(const std::string& name, bool def) const;
  int32 DefaultInt(const std::string& name, int32 def) const;
  int64 DefaultInt64(const std::string& name, int64 def) const;
  float DefaultFloat(const std::string& name, float def) const;

  const std::string& FileName();
  const std::vector<std::string>& Arguments() const;
  std::vector<std::string> KeysByString(const std::string& name);

private:
  template<class T>
  T DefaultValue(const std::string& name, T def) const;
};

#define Configer Config::Instance()

};