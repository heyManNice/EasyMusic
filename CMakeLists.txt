cmake_minimum_required(VERSION 3.20)

project(EasyMusic CXX C)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include(scripts/cpr.cmake)
include(scripts/json.cmake)
include(scripts/stb.cmake)

set(SRC_DIR "${PROJECT_SOURCE_DIR}")

add_executable(client WIN32 "${SRC_DIR}/main.cpp" "${SRC_DIR}/all_class.cpp" "${SRC_DIR}/all_proc.cpp" "${SRC_DIR}/foot_tool.cpp" "${SRC_DIR}/gdi_device.cpp" "${SRC_DIR}/head_tool.cpp" "${SRC_DIR}/mytools.cpp" "${SRC_DIR}/navigation_bar.cpp" "${SRC_DIR}/player.cpp" "${SRC_DIR}/player_service.cpp" "${SRC_DIR}/apiservice.cpp"  "${SRC_DIR}/config_service.cpp" "${SRC_DIR}/utils.cpp" "${SRC_DIR}/tooltip/tooltip.cpp" "${SRC_DIR}/utfconvert.cpp")

target_include_directories(client PRIVATE 
    "${json_SOURCE_DIR}/single_include"
    "${stb_SOURCE_DIR}"
)

target_link_libraries(client PRIVATE dwmapi WinMM cpr)