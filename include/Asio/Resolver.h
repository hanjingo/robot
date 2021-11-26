#pragma once

#include "IoContext.h"
#include "Optional.h"
#include <boost/asio/ip/tcp.hpp>
#include <string>

namespace Robot
{
    namespace Asio
    {
        class Resolver
        {
        public:
            explicit Resolver(IoContext& IoContext) : _impl(ioContext) { }

            Optional<boost::asio::ip::tcp::endpoint> Resolve(const boost::asio::ip::tcp& protocol, 
                                                             const std::string& host, 
                                                             const std::string& service)
            {
                boost::system::error_code ec;
                boost::asio::ip::resolver_base::flags flagsResolver  = 
                    boost::asio::ip::resolver_base::all_matching;
                boost::asio::ip::tcp::resolver::results_type results = 
                    _impl.resolve(protocol, host, service, flagsResolver, ec);
                if (results.begin() == results.end() || ec)
                    return {};

                return results.begin()->endpoint();
            }
        private:
            boost::asio::ip::tcp::resolver _impl;
        };
    }
}