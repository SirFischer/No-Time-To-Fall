cmake_minimum_required(VERSION 3.10)
project(No-Time-To-Fall VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Add profiling build type
set(CMAKE_CXX_FLAGS_PROFILING "-pg -g -O1 -Wall -Werror -Wextra")
set(CMAKE_EXE_LINKER_FLAGS_PROFILING "-pg")

# Add profiling flags to Debug build for convenience
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif()

# Use Ninja as the preferred generator if available
find_program(NINJA_EXECUTABLE ninja)
if(NINJA_EXECUTABLE)
    set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "")
endif()

# Find required packages
find_package(SFML 2.6.2 REQUIRED COMPONENTS graphics window system network audio)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src/*
    ${CMAKE_CURRENT_SOURCE_DIR}/Yuna/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/Yuna/mfGUI/include
)

# Recursive search for source files
file(GLOB_RECURSE SANDBOX_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(No-Time-To-Fall ${SANDBOX_SOURCES})

target_link_libraries(No-Time-To-Fall
	PRIVATE
		${CMAKE_BINARY_DIR}/Yuna/libYuna.a
		${CMAKE_BINARY_DIR}/Yuna/mfGUI/lib/libMFGUId.a
		sfml-graphics
		sfml-window
		sfml-system
		sfml-network
		sfml-audio
)