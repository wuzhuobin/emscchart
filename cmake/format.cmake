include(CPM)
cpmaddpackage(
    NAME
    Format.cmake
    VERSION
    1.8.1
    GITHUB_REPOSITORY
    TheLartians/Format.cmake
    OPTIONS
    "CLANG_FORMAT_PROGRAM clang-format-18")
