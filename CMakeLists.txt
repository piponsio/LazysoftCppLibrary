cmake_minimum_required(VERSION 3.0)
project(LazysoftCppLibrary VERSION 0.1.0)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(SERIAL_HEADER
        ${CMAKE_CURRENT_SOURCE_DIR}/src/serial.cpp
)
set(CHECKSUM_HEADER
        ${CMAKE_CURRENT_SOURCE_DIR}/src/checksum.cpp
)
set(STORM32_COMMAND_HEADER
        ${CMAKE_CURRENT_SOURCE_DIR}/src/serial.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/checksum.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm32_command.cpp
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/lib/shared)

add_library(serial SHARED ${SERIAL_HEADER})
add_library(checksum SHARED ${CHECKSUM_HEADER})
add_library(storm32_command SHARED ${STORM32_COMMAND_HEADER})

#Examples
set(EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/example)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(serialWrite ${EXAMPLES_DIR}/serialWrite.cpp)
target_link_libraries(serialWrite serial)

add_executable(storm32_commandSetAngle ${EXAMPLES_DIR}/storm32_commandSetAngle.cpp)
target_link_libraries(storm32_commandSetAngle storm32_command)

add_executable(serialRead ${EXAMPLES_DIR}/serialRead.cpp)
target_link_libraries(serialRead storm32_command)