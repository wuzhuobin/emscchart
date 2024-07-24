include(googletest)

file(GLOB_RECURSE TEST_SRC ${PROJECT_SOURCE_DIR}/test/*.[c|h]*)

add_executable(${PROJECT_NAME}_test ${TEST_SRC})

target_link_libraries(
    ${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock
                                 GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
