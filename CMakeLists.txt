cmake_minimum_required(VERSION 3.20)

project(EasyMusic CXX C)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(SRC_DIR "${PROJECT_SOURCE_DIR}")

add_executable(client WIN32 "${SRC_DIR}/main.cpp" "${SRC_DIR}/allClass.cpp" "${SRC_DIR}/allProc.cpp" "${SRC_DIR}/foottool.cpp" "${SRC_DIR}/gdiDevice.cpp" "${SRC_DIR}/headtool.cpp" "${SRC_DIR}/Lmenu.cpp" "${SRC_DIR}/mytools.cpp" "${SRC_DIR}/network.cpp" "${SRC_DIR}/PlayingSong.cpp" "${SRC_DIR}/tooltip.cpp" "${SRC_DIR}/yyjson/yyjson.c")
