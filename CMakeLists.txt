cmake_minimum_required(VERSION 3.10)

project(dcm_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(dcm_simulator
    src/main.cpp
    src/Dcm.cpp
    src/Dcm_Parser.cpp
    src/Dcm_Services.cpp
    src/Transport.cpp
    src/EcuApp.cpp
    src/DoIP.cpp
    src/TcpTransport.cpp
)