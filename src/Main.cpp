#include "Utils/Config.hpp"
#include "Log/Logger.hpp"
#include <iostream>

using namespace Robot::Log;

int main(int arch, char** argv)
{
    LOG->Info("FUN MAIN");

    LOG->AddFileSink("~/tmp", 2, 2, std::move(LOG->DefaultFormatter()));
    LOG->Info("test file sink");

    LOG->AddConsoleSink(LOG->DefaultFormatter());
    LOG->Info("test console sink");

    std::cin.get();
}