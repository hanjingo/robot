#include "Log/Logger.hpp"

namespace Robot {
namespace Log {

LoggerPtr Logger::_instance;
Slg       Logger::_slg;
FmtPtr    Logger::_fmt;

static std::ostream& operator<<(std::ostream& stream, Lvl lvl) {
  static const char* const LvlStr[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

  if (static_cast<std::size_t>(lvl) < sizeof(LvlStr) / sizeof(*LvlStr))
    stream << LvlStr[lvl];
  else
    stream << static_cast<int>(lvl);

  return stream;
};

LoggerPtr Logger::Instance() {
  if (_instance == 0)
    _instance = std::make_shared<Logger>(Logger{});
  return _instance;
};

FmtPtr Logger::DefaultFormatter() {
  if (_fmt == 0)
    _fmt = std::make_shared<Fmt>(expr::stream
      << "[" << expr::format_date_time<Ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
      << "|" << expr::attr<Lvl>("Severity") << "]"
      << " " << expr::smessage);
  return _fmt;
}

// add attr (LineID, TimeStamp, ProcessID, ThreadID)
void Logger::AddFileSink(const std::string& dir, int maxFileSizeMB, int maxBackup, Fmt fmt) {
  boost::shared_ptr<FileSink> fileSink(new FileSink(
    //keywords::target_file_name    = "%Y%m%d_%H%M%S_%N.log",               
    keywords::time_based_rotation = file::rotation_at_time_point(0, 0, 0), 
    keywords::rotation_size       = maxFileSizeMB * 1024 * 1024,
    keywords::open_mode           = std::ios::out | std::ios::app));

  fileSink->locked_backend()->set_file_collector(file::make_collector(
    keywords::target         = dir,
    keywords::max_size       = maxBackup * maxFileSizeMB * 1024 * 1024,
    keywords::min_free_space = maxBackup * maxFileSizeMB * 1024 * 1024));
    
  fileSink->set_formatter(fmt);
  fileSink->locked_backend()->scan_for_files();
  fileSink->locked_backend()->auto_flush(true);
  boost::log::core::get()->add_sink(fileSink);
}

void Logger::AddConsoleSink(boost::log::formatter fmt) {
  auto consoleSink = boost::log::add_console_log();
  consoleSink->set_formatter(fmt);
  boost::log::core::get()->add_sink(consoleSink);
}

void Logger::SetLvl(Lvl min) {
  auto lvl = static_cast<int>(min);
  boost::log::core::get()->set_filter(trivial::severity >= lvl);
}

}; };