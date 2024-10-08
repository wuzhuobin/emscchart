cmake_minimum_required(VERSION 3.22)

project(emscchart)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
option(BUILD_TESTING "Build Testing" OFF)
option(BUILD_EXAMPLE "Build Example" OFF)
option(COMPILE_WARNING_AS_ERROR "Compile Warning as Error" OFF)

file(GLOB_RECURSE INC ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.[c|h]*)

add_library(${PROJECT_NAME} ${SRC} ${INC})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/W4>
           $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>)

if (COMPILE_WARNING_AS_ERROR)
    target_compile_options(
        ${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/WX>
                               $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Werror>)
endif ()

include(nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")

    message(STATUS "Emscripten detected")
    target_link_options(${PROJECT_NAME} PUBLIC --use-port=sdl2
                        --use-port=sdl2_gfx -fwasm-exceptions)
    target_compile_options(
        ${PROJECT_NAME} PUBLIC --use-port=sdl2 --use-port=sdl2_gfx
                               -fwasm-exceptions)

else ()

    message(STATUS "Emscripten not detected")
    find_package(SDL2 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 SDL2_gfx)

endif ()

if (BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif ()

if (BUILD_EXAMPLE)
    add_subdirectory(example)
endif ()

# Add targets for clang-format and cmake-format
find_program(CLANG_FORMAT NAMES clang-format-18)
find_program(CMAKE_FORMAT NAMES cmake-format)
if (CLANG_FORMAT AND CMAKE_FORMAT)
    include(format)
endif ()
