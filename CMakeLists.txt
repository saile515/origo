cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

### Based on https://github.com/lionkor/cpp-project-template ###

include(cmake/Vcpkg.cmake)

project(
    "origo"
    VERSION 0.1.0
    LANGUAGES CXX
)

include(cmake/StandardSettings.cmake)
include(cmake/StaticAnalyzers.cmake)
include(cmake/Git.cmake)

### SETTINGS ###

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY origo)
set(GRAPHICS_IMPLENTATION "opengl" CACHE STRING "Selects graphics API. Available options: 'opengl'")

set(PRJ_HEADERS 
    include/origo/origo.hpp
    include/origo/graphics/buffer.hpp
    include/origo/graphics/window.hpp
    include/origo/graphics/shader.hpp

    src/util/files.hpp
)

set(PRJ_SOURCES
    src/util/files.cpp
)
if(GRAPHICS_IMPLENTATION STREQUAL "opengl")
    list(APPEND PRJ_SOURCES 
        src/graphics/implementations/opengl/window.cpp
        src/graphics/implementations/opengl/buffer.cpp
        src/graphics/implementations/opengl/shader.cpp
    )
endif()

set(PRJ_TEST_MAIN tests/main.cpp)
set(LIB_INCLUDE_DIRS include) # public
set(PRJ_INCLUDE_DIRS src) # private
set(PRJ_COMPILE_FEATURES cxx_std_20)
set(PRJ_DEFINITIONS -DGRAPHICS_IMPLEMENTATION=${GRAPHICS_IMPLENTATION})
set(PRJ_LIBRARIES 
    fmt::fmt
    doctest::doctest
    Threads::Threads
    spdlog::spdlog
    glfw
    unofficial::gl3w::gl3w
)

find_package(fmt CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(gl3w CONFIG REQUIRED)

include(FindThreads)

### END SETTINGS ###

# DONT change anything beyond this point unless you've read the cmake bible and 
# swore on it not to bonk up the ci/cd pipelines with your changes.

####################


# enables compile_commands.json for clang-related tools (such as the clang LS)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# build debug builds by default (if not specified otherwise)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(UNIX)
    # this will allow to use same _DEBUG macro available in both Linux as well as Windows - MSCV environment. Easy to put Debug specific code.
    add_compile_options("$<$<CONFIG:DEBUG>:-D_DEBUG>")
endif(UNIX)

include(cmake/CompilerWarnings.cmake)

# set MT library for msvc - this is required (says documentation)
# linux/mac/etc should simply ignore this by default.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

set(PRJ_DEFINITIONS ${PRJ_DEFINITIONS}
    PRJ_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    PRJ_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    PRJ_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    PRJ_GIT_HASH="${PRJ_GIT_HASH}"
)


add_library(${PROJECT_NAME} SHARED ${PRJ_HEADERS} ${PRJ_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PRJ_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRJ_INCLUDE_DIRS} PUBLIC ${LIB_INCLUDE_DIRS})
target_compile_features(${PROJECT_NAME} PUBLIC ${PRJ_COMPILE_FEATURES})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${PRJ_DEFINITIONS} ${PRJ_WARNINGS}
    DOCTEST_CONFIG_DISABLE # disables all test code in the final executable
)

# setup all warnings (from cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME})

# copy include files to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/include/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/include/)


if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
    message(STATUS "Unit tests are enabled and will be built as '${PROJECT_NAME}-tests'")
    add_executable(${PROJECT_NAME}-tests ${PRJ_HEADERS} ${PRJ_SOURCES} ${PRJ_TEST_MAIN})
    target_link_libraries(${PROJECT_NAME}-tests ${PRJ_LIBRARIES})
    target_include_directories(${PROJECT_NAME}-tests PRIVATE ${PRJ_INCLUDE_DIRS} ${LIB_INCLUDE_DIRS})
    target_compile_features(${PROJECT_NAME}-tests PRIVATE ${PRJ_COMPILE_FEATURES})
    target_compile_definitions(${PROJECT_NAME}-tests PRIVATE ${PRJ_DEFINITIONS} ${PRJ_WARNINGS})
    set_project_warnings(${PROJECT_NAME}-tests)
endif()


