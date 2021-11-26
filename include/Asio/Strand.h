#pragma once

#include "IoContext.h"
#include <boost/asio/strand.hpp>
#include <boost/asio/bind_executor.hpp>

namespace Robot
{
    namespace Asio
    {
        class Strand : public IoContextBaseNamespace::IoContextBase::strand
        {
        public:
            Strand(IoContext& ioContext) : IoContextBaseNamespace::IoContextBase::strand(ioContext) {}
        };

        using boost::asio::bind_executor;
    }
}