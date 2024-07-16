cmake_minimum_required(VERSION 3.5)

project(TCPServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TCPServer main.cpp tcpserver.cpp tcpserver.h logger.cpp logger.h)

install(TARGETS TCPServer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
