#pragma once

#include <chrono>

typedef std::chrono::nanoseconds                      NanoSeconds;
typedef std::chrono::microseconds                     MicroSeconds;
typedef std::chrono::milliseconds                     MilliSeconds;
typedef std::chrono::seconds                          Seconds;
typedef std::chrono::minutes                          Minutes;
typedef std::chrono::hours                            Hours;
typedef std::chrono::steady_clock::time_point         TimePoint;
typedef std::chrono::system_clock::time_point         SystemTimePoint;

//typedef std::chrono::duration                         Duration;

struct Duration 
{
//   Duration() : _ns() {}
//   ~Duration() {} 

//   Duration operator+(Duration const& dur);
//   void operator+=(Duration const& dur);

//   Duration operator-(Duration const& dur);
//   void operator-=(Duration const& dur);

//   Duration operator*(Duration const& dur);
//   Duration operator*=(Duration const& dur);

//   Duration operator/(Duration const& dur);
//   Duration operator/=(Duration const& dur);

//  private:
//   NanoSeconds _ns;
};