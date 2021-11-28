#pragma once

#include "Define.hpp"

namespace Robot {
namespace Log {

class Logger;
typedef std::shared_ptr<Logger>  LoggerPtr;

class Logger {
 public:
  Logger() { boost::log::add_common_attributes(); }
  ~Logger() {};
  Logger& operator=(Logger const&) = delete;

  static inline LoggerPtr Instance() 
  { if (_instance == 0) { _instance = std::make_shared<Logger>(Logger{}); } return _instance; };
  static Fmt DefaultFormatter();

 public:
  SinkPtr AddFileSink(std::string const& dir, int maxFileSizeMB, int maxBackup, Fmt fmt);
  SinkPtr AddConsoleSink(Fmt fmt);
  
  inline void RemoveSink(SinkPtr const& sinkPtr) { boost::log::core::get()->remove_sink(sinkPtr); };
  inline void SetLvl(Lvl min) { boost::log::core::get()->set_filter(trivial::severity >= static_cast<int>(min)); };

  template<typename... Args>
  inline void Debug(std::string const& fmt, Args&&... args) 
  { BOOST_LOG_SEV(_slg, Lvl::DEBUG) << Robot::Log::_format(fmt, args...) << std::endl; }

  template<typename... Args>
  inline void Info(std::string const& fmt, Args&&... args) 
  { BOOST_LOG_SEV(_slg, Lvl::INFO) << Robot::Log::_format(fmt, args...) << std::endl; }

  template<typename... Args>
  inline void Warn(std::string const& fmt, Args&&... args) 
  { BOOST_LOG_SEV(_slg, Lvl::WARN) << Robot::Log::_format(fmt, args...) << std::endl; }

  template<typename... Args>
  inline void Error(std::string const& fmt, Args&&... args) 
  { BOOST_LOG_SEV(_slg, Lvl::ERROR) << Robot::Log::_format(fmt, args...) << std::endl; }

  template<typename... Args>
  inline void Fatal(std::string const& fmt, Args&&... args) 
  { BOOST_LOG_SEV(_slg, Lvl::ERROR) << Robot::Log::_format(fmt, args...) << std::endl; }

 private:
  static Slg             _slg;
  static LoggerPtr       _instance;
};

#define LOG Logger::Instance()

} } // namespace Robot:Log
