#pragma once

#include <boost/asio/deadline_timer.hpp>

#define BasicDeadlineTimerThirdTemplateArg , boost::asio::io_context::executor_type

#define DeadlineTimerBase boost::asio::basic_deadline_timer<boost::posix_time::ptime, boost::asio::time_traits<boost::posix_time::ptime> BasicDeadlineTimerThirdTemplateArg>

namespace Trinity
{
    namespace Asio
    {
        class DeadlineTimer : public DeadlineTimerBase
        {
        public:
            using DeadlineTimerBase::basic_deadline_timer;
        };
    }
}