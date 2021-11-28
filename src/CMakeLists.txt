add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Threads REQUIRED) 
find_package(Boost 1.75.0 REQUIRED COMPONENTS 
    log 
    log_setup 
    chrono 
    atomic 
    filesystem 
    regex 
    thread) 

# import head file
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

if(TEST)
    add_subdirectory(Test)
endif(TEST)

add_executable(${PROJECT_NAME}
    Main.cpp
    
    Log/Logger.cpp
    
    Utils/Config.cpp)

target_link_libraries(${PROJECT_NAME}
    Boost::log
    Boost::log_setup
    Boost::chrono
    Boost::atomic
    Boost::filesystem
    Boost::regex
    Boost::thread
    Threads::Threads)