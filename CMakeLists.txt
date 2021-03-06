cmake_minimum_required(VERSION 3.0.0)
project(RESPECTRAL VERSION 0.1.0)

add_library(RESPECTRAL SHARED RESPECTRAL.cpp RESPECTRAL.h Injector.cpp Injector.h Logger/ILogger.h )

set (CMAKE_CXX_FLAGS "-m32")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
