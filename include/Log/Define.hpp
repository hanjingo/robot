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

enum Lvl { DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3, FATAL = 4 };

namespace expr     = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace trivial  = boost::log::trivial;
namespace file     = boost::log::sinks::file;

typedef boost::log::sources::severity_logger<Lvl>               Slg;
typedef boost::log::formatter                                   Fmt;
typedef boost::posix_time::ptime                                Ptime;

typedef boost::shared_ptr<boost::log::v2_mt_posix::sinks::sink>                   SinkPtr;
typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> FileSink;

static std::ostream& operator<<(std::ostream& stream, Lvl lvl) 
{
  static const char* const LvlStr[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

  if (static_cast<std::size_t>(lvl) < sizeof(LvlStr) / sizeof(*LvlStr))
    stream << LvlStr[lvl];
  else
    stream << static_cast<int>(lvl);

  return stream;
};

template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == 0>::type>
inline std::ostream& _output(std::ostream& stream, Args&&... args) { return stream; }

template<typename Arg, typename... Args>
inline std::ostream& _output(std::ostream& stream, Arg&& arg, Args&&... args) 
{ stream << arg; return _output(stream, std::forward<Args>(args)...); }

template<typename... Args>
inline std::string _format(Args&&... args) 
{
  std::ostringstream stream;
  Robot::Log::_output(stream, std::forward<Args>(args)...);
  return stream.str();
}

}} // namespace Robot::Log