cmake_minimum_required(VERSION 3.5)
project(TestQuadReg LANGUAGES CXX)

set(TEST_QUADREG_SOURCES
	test_regression.cpp)

add_compile_options(--std=c++11)

add_subdirectory(quad_reg)

add_executable(test_regression 
	${TEST_QUADREG_SOURCES})
	
target_link_libraries(test_regression 
	moving_quad_reg) 

