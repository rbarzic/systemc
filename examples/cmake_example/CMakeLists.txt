cmake_minimum_required(VERSION 3.0)
project(test_systemc)

set (CMAKE_PREFIX_PATH /opt/systemc-cmake/2.3.3 )
find_package(SystemCLanguage CONFIG REQUIRED)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

add_executable(test_systemc main.cpp)
target_link_libraries(test_systemc SystemC::systemc)

