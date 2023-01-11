include_directories(../inc)

add_executable(solve solve.cpp)
add_executable(generate generate.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)