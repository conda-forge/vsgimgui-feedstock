cmake_minimum_required(VERSION 3.7)

project(vsghelloworld LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(vsgXchange CONFIG REQUIRED)
find_package(vsgImGui CONFIG REQUIRED)

add_executable(vsghelloworld main.cpp)
target_link_libraries(vsghelloworld PRIVATE vsgXchange::vsgXchange vsgImGui::vsgImGui)

add_executable(vsgimgui_smoke smoke.cpp)
target_link_libraries(vsgimgui_smoke PRIVATE vsgImGui::vsgImGui)
add_test(NAME vsgimgui_smoke COMMAND vsgimgui_smoke)
