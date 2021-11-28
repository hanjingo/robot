#pragma once

#include "Types.hpp"
#include "Duration.hpp"

class TimerI
{
 public:
  virtual void Update(Duration const& dur) = 0;
  virtual void Reset(Duration const& dur) = 0;
  virtual bool BPass() = 0;
};

struct PeriodicTimer : TimerI
{
  PeriodicTimer(Duration const& period, TimePoint startTime)
    : i_period(period), i_expireTime(startTime)
  {
  }

  void Update(Duration const& dur)
  {
  }

  void Reset(Duration const& dur)
  {
  }

  bool BPass()
  {
  }

 private:
  Duration  i_period;
  TimePoint i_expireTime;
};

