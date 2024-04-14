cmake_minimum_required()
project(inverter)

set(SOURCES main.cpp src/bits.cpp)
set(HEADERS include/bits.h)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)