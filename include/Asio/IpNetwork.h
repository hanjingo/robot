#include "Define.h"
#include "IpAddress.h"
#include <boost/version.hpp>

namespace Robot
{
    namespace Net
    {
        inline bool IsInNetwork(const boost::asio::ip::address_v4& networkAddress, 
                                const boost::asio::ip::address_v4& mask, 
                                const boost::asio::ip::address_v4& clientAddress)
        {
            boost::asio::ip::network_v4 network = boost::asio::ip::make_network_v4(networkAddress, mask);
            boost::asio::ip::address_v4_range hosts = network.hosts();
            return hosts.find(clientAddress) != hosts.end();
        }

        inline boost::asio::ip::address_v4 GetDefaultNetmaskV4(const boost::asio::ip::address_v4& networkAddress)
        {
            if ((address_to_uint(networkAddress) & 0x80000000) == 0)
                return boost::asio::ip::address_v4(0xFF000000);
            if ((address_to_uint(networkAddress) & 0xC0000000) == 0x80000000)
                return boost::asio::ip::address_v4(0xFFFF0000);
            if ((address_to_uint(networkAddress) & 0xE0000000) == 0xC0000000)
                return boost::asio::ip::address_v4(0xFFFFFF00);
            return boost::asio::ip::address_v4(0xFFFFFFFF);
        }

        inline bool IsInNetwork(const boost::asio::ip::address_v6& networkAddress, 
                                uint16 prefixLength, 
                                const boost::asio::ip::address_v6& clientAddress)
        {
            boost::asio::ip::network_v6 network = boost::asio::ip::make_network_v6(networkAddress, prefixLength);
            boost::asio::ip::address_v6_range hosts = network.hosts();
            return hosts.find(clientAddress) != hosts.end();
        }
    }
}