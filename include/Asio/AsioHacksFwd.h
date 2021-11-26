#pragma once

#include <boost/version.hpp>

namespace boost
{
    namespace posix_time
    {
        class ptime;
    }

    namespace asio
    {
        template <typename Time>
        struct time_traits;

        namespace ip
        {
            class address;

            class tcp;

            template <typename InternetProtocol>
            class basic_endpoint;

            typedef basic_endpoint<tcp> tcp_endpoint;
        }
    }
}

namespace Robot
{
    namespace Asio
    {
        class DeadlineTimer;
        class IoContext;
        class Resolver;
        class Strand;
    }
}