#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <fstream>

#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>

namespace Robot {
namespace Log {

class Logger;

enum Lvl { DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3, FATAL = 4 };

namespace expr     = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace trivial  = boost::log::trivial;
namespace file     = boost::log::sinks::file;

typedef std::shared_ptr<Logger>                                                   LoggerPtr;
typedef boost::log::sources::severity_logger<Lvl>                                 Slg;
typedef boost::log::formatter                                                     Fmt;
typedef std::shared_ptr<boost::log::formatter>                                    FmtPtr;
typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> FileSink;
typedef boost::posix_time::ptime                                                  Ptime;

static std::ostream& operator<<(std::ostream& stream, Lvl lvl);

template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == 0>::type>
inline std::ostream& _output(std::ostream& stream, Args&&... args) { return stream; }

template<typename Arg, typename... Args>
inline std::ostream& _output(std::ostream& stream, Arg&& arg, Args&&... args) 
{ stream << arg; return _output(stream, std::forward<Args>(args)...); }

template<typename... Args>
inline std::string _format(Args&&... args) {
  std::ostringstream stream;
  Robot::Log::_output(stream, std::forward<Args>(args)...);
  return stream.str();
}

class Logger {
 public:
  Logger() { boost::log::add_common_attributes(); }
  ~Logger() {};
  Logger& operator=(const Logger&) = delete;

 public:
  static LoggerPtr Instance();
  static FmtPtr DefaultFormatter();

  void AddFileSink(const std::string& dir, int max_file_size_mb, int max_backup, Fmt fmt);
  void AddConsoleSink(Fmt fmt);
  void SetLvl(Lvl min);

  template<typename... Args>
  inline void Debug(const std::string& fmt, Args&&... args) {
    BOOST_LOG_SEV(_slg, Lvl::DEBUG) << Robot::Log::_format(fmt, args...) << std::endl;
  }

  template<typename... Args>
  inline void Info(const std::string& fmt, Args&&... args) {
    BOOST_LOG_SEV(_slg, Lvl::INFO) << Robot::Log::_format(fmt, args...) << std::endl;
  }

  template<typename... Args>
  inline void Warn(const std::string& fmt, Args&&... args) {
    BOOST_LOG_SEV(_slg, Lvl::WARN) << Robot::Log::_format(fmt, args...) << std::endl;
  }

  template<typename... Args>
  inline void Error(const std::string& fmt, Args&&... args) {
    BOOST_LOG_SEV(_slg, Lvl::ERROR) << Robot::Log::_format(fmt, args...) << std::endl;
  }

  template<typename... Args>
  inline void Fatal(const std::string& fmt, Args&&... args) {
    BOOST_LOG_SEV(_slg, Lvl::ERROR) << Robot::Log::_format(fmt, args...) << std::endl;
  }

 private:
  static Slg       _slg;
  static LoggerPtr _instance;
  static FmtPtr    _fmt;
};

}; };
