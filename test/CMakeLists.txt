include(googletest)

file(GLOB_RECURSE TEST_SRC ${PROJECT_SOURCE_DIR}/test/*.[c|h]*)

add_executable(${PROJECT_NAME}_test ${TEST_SRC})

target_link_libraries(
    ${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main
                                 GTest::gmock GTest::gmock_main)

target_compile_definitions(${PROJECT_NAME}_test PRIVATE TESTING)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test EXTRA_ARGS --gtest_color=yes)

# if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
# set_target_properties(${PROJECT_NAME}_test PROPERTIES SUFFIX .html) endif ()
