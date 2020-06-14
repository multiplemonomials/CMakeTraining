cmake_minimum_required(VERSION 3.5)
project(TestQuadReg LANGUAGES CXX)

set(TEST_QUADREG_SOURCES
	quad_reg/MovingQuadReg.cpp
	test_regression.cpp)

include_directories(quad_reg)
add_compile_options(--std=c++11)

add_executable(test_regression 
	${TEST_QUADREG_SOURCES})
	
