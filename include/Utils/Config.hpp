#pragma once

#include "Types.hpp"
#include <string>
#include <vector>

namespace Robot {
namespace Utils {

class Config
{
  Config() = default;
  Config(const Config&) = delete;
  Config& operator=(const Config&) = delete;
  ~Config() = default;

public:
  bool LoadInitial(std::string const&  file, std::vector<std::string> args, std::string& error);
  static Config* Instance();
  bool Reload(std::string& error);
  
  std::string GetDefaultString(std::string const&  name, std::string const&  def) const;
  bool GetDefaultBool(std::string const&  name, bool def) const;
  int32 GetDefaultInt(std::string const&  name, int32 def) const;
  int64 GetDefaultInt64(std::string const&  name, int64 def) const;
  float GetDefaultFloat(std::string const&  name, float def) const;

  std::string const&  GetFileName();
  const std::vector<std::string>& GetArguments() const;
  std::vector<std::string> GetKeysByString(std::string const&  name);

private:
  template<class T>
  T GetDefaultValue(std::string const&  name, T def) const;
};

#define Configer Config::Instance()

}} // namespace Robot::Utils