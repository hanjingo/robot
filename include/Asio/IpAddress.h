#pragma once

#include "Define.h"
#include <boost/asio/ip/address.hpp>

namespace Robot
{
    namespace Net
    {
        using boost::asio::ip::make_address;
        using boost::asio::ip::make_address_v4;
        inline uint32 address_to_uint(const boost::asio::ip::address_v4& address) { return address.to_uint(); }
    }
}