# CMakeList.txt : CMake project for LastAssignment, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("LastAssignment")

# Add source to this project's executable.
add_executable (LastAssignment "LastAssignment.cpp" "LastAssignment.h")
target_include_directories(LastAssignment PUBLIC "D:\\Algonquin College\\Level 4\\C++\\Labs\\Assignment\\LastAssignment\\nana_1.7.4\\nana\\include")
add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
target_include_directories(LastAssignment PUBLIC "D:\\Algonquin College\\Level 4\\C++\\Labs\\Assignment\\LastAssignment\\nana_1.7.4\\nana\\build\\bin")
target_link_libraries(LastAssignment "nana_v142_Debug_x64")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} /NANA_ENABLE_AUDIO")
add_definitions(-DNANA_ENABLE_AUDIO)

# TODO: Add tests and install targets if needed.
