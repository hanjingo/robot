#include "Utils/Config.hpp"
#include <boost/property_tree/ini_parser.hpp>
#include <algorithm>
#include <memory>
#include <mutex>

namespace Robot {

namespace bpt = boost::property_tree;

namespace
{
  std::string _filename;
  std::vector<std::string> _args;
  bpt::ptree _config;
  std::mutex _configLock;
}

bool Config::LoadInitial(const std::string& file, std::vector<std::string> args, 
                         std::string& error)
{
  std::lock_guard<std::mutex> lock(_configLock);

  _filename = file;
  _args = args;

  try
  {
    bpt::ptree fullTree;
    bpt::ini_parser::read_ini(file, fullTree);

    if (fullTree.empty())
    {
      error = "empty file (" + file + ")";
      return false;
    }

    _config = fullTree.begin()->second;
  }
  catch(const bpt::ini_parser::ini_parser_error& e)
  {
    if (e.line() == 0)
      error = e.message() + "(" + e.filename() + ")";
    else
      error = e.message() + "(" + e.filename() + ":" + std::to_string(e.line()) + ")";
    return false;
  }
  
  return true;
}

Config* Config::Instance()
{
  static Config instance;
  return &instance;
}

bool Config::Reload(std::string& error)
{
  return LoadInitial(_filename, std::move(_args), error);
}

template<class T>
T Config::DefaultValue(const std::string& name, T def) const
{
  try
  {
    return _config.get<T>(bpt::ptree::path_type(name, '/'));
  }
  catch(const bpt::ptree_bad_path&)
  {
    // TODO
  }
  catch (const bpt::ptree_bad_data&)
  {
    // TODO
  }

  return def;
}

template<>
std::string Config::DefaultValue<std::string>(const std::string& name, std::string def) const 
{
  try
  {
    return _config.get<std::string>(bpt::ptree::path_type(name, '/'));
  }
  catch(const bpt::ptree_bad_path&)
  {
    // TODO
  }
  catch (const bpt::ptree_bad_data&)
  {
    // TODO
  }

  return def;
}

std::string Config::DefaultString(const std::string& name, const std::string& def) const
{
  std::string bak = DefaultValue(name, def);
  bak.erase(std::remove(bak.begin(), bak.end(), '"'), bak.end());
  return bak;
}

bool Config::DefaultBool(const std::string& name, bool def) const
{
  auto bak = DefaultValue(name, std::string(def ? "1" : "0"));
  bak.erase(std::remove(bak.begin(), bak.end(), '"'), bak.end());
  return StringToBool(bak);
}

int32 Config::DefaultInt(const std::string& name, int32 def) const
{
  return DefaultValue(name, def);
}

int64 Config::DefaultInt64(const std::string& name, int64 def) const
{
  return DefaultValue(name, def);
}

float Config::DefaultFloat(const std::string& name, float def) const
{
  return DefaultValue(name, def);
}

const std::string& Config::FileName()
{
  std::lock_guard<std::mutex> lock(_configLock);
  return _filename;
}

const std::vector<std::string>& Config::Arguments() const
{
  return _args;
}

std::vector<std::string> Config::KeysByString(const std::string& name)
{
  std::lock_guard<std::mutex> lock(_configLock);

  std::vector<std::string> keys;

  for (const bpt::ptree::value_type& child : _config)
    if (child.first.compare(0, name.length(), name) == 0)
      keys.push_back(child.first);

  return keys;
}

};