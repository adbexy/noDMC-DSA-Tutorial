cmake_minimum_required(VERSION 3.18)

project(dml-tutorial)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(DML_PATH "../third_party/DML")

set(DML_SOURCE_DIR "${DML_PATH}/include/")
# make the linker find -ldml == libdml.a
set(CMAKE_EXE_LINKER_FLAGS
	"${CMAKE_EXE_LINKER_FLAGS} -Wl,-L${DML_PATH}/build/dml_install/lib")

set(SOURCES memcpy_example.cpp)

set(DEBUG_FLAGS "-g3" "-ggdb")
set(RELEASE_FLAGS "-O3")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -march=sapphirerapids")

add_executable(cpp_example ${SOURCES})
add_executable(c_example memcpy_example.c)

target_include_directories(cpp_example PRIVATE ${CMAKE_SOURCE_DIR} ${DML_SOURCE_DIR})
target_link_libraries(cpp_example PRIVATE libdml.a)

target_include_directories(c_example PRIVATE ${CMAKE_SOURCE_DIR} ${DML_SOURCE_DIR})
target_link_libraries(c_example PRIVATE libdmlhl.a)

#install(TARGETS dml-benchmark DESTINATION ${CMAKE_INSTALL_PREFIX})
