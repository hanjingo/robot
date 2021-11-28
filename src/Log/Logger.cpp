#include "Log/Logger.hpp"

namespace Robot {
namespace Log {

LoggerPtr Logger::_instance;
Slg       Logger::_slg;

Fmt Logger::DefaultFormatter() 
{
  return expr::stream
    << "[" << expr::format_date_time<Ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
    << "|" << expr::attr<Lvl>("Severity") << "]"
    << " " << expr::smessage;
};

// add attr (LineID, TimeStamp, ProcessID, ThreadID)
SinkPtr Logger::AddFileSink(std::string const& dir, int maxFileSizeMB, 
                            int maxBackup, Fmt fmt) 
{
  boost::shared_ptr<FileSink> fileSink(new FileSink(
    keywords::target_file_name    = "%Y%m%d_%H%M%S_%N.log",               
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

  return fileSink;
}

SinkPtr Logger::AddConsoleSink(Fmt fmt) 
{
  auto consoleSink = boost::log::add_console_log();
  consoleSink->set_formatter(fmt);
  boost::log::core::get()->add_sink(consoleSink);

  return consoleSink;
}

} } // namespace Robot::Log