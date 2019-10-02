cmake_minimum_required(VERSION 3.0)

project(dicegame-cpp)

#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)

# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
#if(UNIX)
#        message("${CMAKE_SYSTEM_NAME} system")
#elseif(WIN32)
#        message("Windows system")
#endif()

#MATCHES
if(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
        message("Apple's system name is Darwin")
elseif(${CMAKE_SYSTEM_NAME} MATCHES Windows)
        message("Windows system")
endif()

#onde vai ficar o executavel
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

#can't do in-source builds
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

set (SOURCE 
        ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
)

add_executable(
        dicegame
        ${SOURCE}
)
