include(FetchContent)
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    # Enable exceptions for Emscripten
    add_compile_options(-fwasm-exceptions)
    add_link_options(-fwasm-exceptions)
    # Disable gtest pthreads for Emscripten pthreads and std::shared_ptr are not
    # supported in Emscripten
    set(gtest_disable_pthreads ON)
endif ()
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
