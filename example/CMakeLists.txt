file(GLOB EXAMPLES ${PROJECT_SOURCE_DIR}/example/*.cc)

foreach (EXAMPLE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${PROJECT_NAME})
    target_include_directories(${EXAMPLE_NAME}
                               PRIVATE ${PROJECT_SOURCE_DIR}/src)
    if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
        set_target_properties(${EXAMPLE_NAME} PROPERTIES SUFFIX .html)
    endif ()

endforeach ()
