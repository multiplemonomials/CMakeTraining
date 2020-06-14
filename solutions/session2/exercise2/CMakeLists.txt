cmake_minimum_required(VERSION 3.5)
project(TestQuadReg LANGUAGES CXX)

set(TEST_QUADREG_SOURCES
	test_regression.cpp)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Type of build, options are: Debug, Release" FORCE)
endif()

# set compile options
add_compile_options(-Wall -Wextra)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "-g2 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

add_subdirectory(quad_reg)

add_executable(test_regression 
	${TEST_QUADREG_SOURCES})
	
target_link_libraries(test_regression 
	moving_quad_reg) 

string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UCASE)
message(STATUS ">> CXX Compile Flags (For ${CMAKE_BUILD_TYPE}):\
 ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UCASE}}")

