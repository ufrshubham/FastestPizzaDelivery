cmake_minimum_required(VERSION 3.0.0)
project(FastestPizzaDelivery VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions(SHOW_COLLISION_BOXES)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/)

add_subdirectory(vendor/raylib/)

file(GLOB FPD_SOURCE_FILES src/*.cpp)
file(GLOB FPD_HEADER_FILES include/*.hpp)

add_executable(${PROJECT_NAME} ${FPD_SOURCE_FILES} ${FPD_HEADER_FILES})

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}/include/
    PUBLIC ${PROJECT_SOURCE_DIR}/vendors/raylib/src/
)

target_link_libraries(${PROJECT_NAME} raylib)
