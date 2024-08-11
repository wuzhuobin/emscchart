include(FetchContent)
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    # Enable exceptions for Emscripten
    add_compile_options(-fwasm-exceptions)
    add_link_options(-fwasm-exceptions)
endif ()
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3)
FetchContent_MakeAvailable(json)
