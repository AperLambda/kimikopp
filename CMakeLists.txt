cmake_minimum_required(VERSION 3.6)
project(kimiko)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(GenerateExportHeader)
include(utils/CompileUtility)
include(utils/InstallUtility)

set(CMAKE_CXX_STANDARD 17)

# Options
option(KIMIKO_INSTALL "Generate installation target" ON)

generate_flags(KIMIKO_COMPILE_FLAGS native 2 true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}${KIMIKO_COMPILE_FLAGS}")

# Finds the library lambdacommon.
find_package(lambdacommon REQUIRED)

include_directories(${LAMBDACOMMON_INCLUDE_DIRS})

# All files:
# There is the C++ header files.
set(HEADER_FILES include/kimiko/kimiko.h include/kimiko/context.h include/kimiko/command.h include/kimiko/manager.h include/kimiko/parser.h include/kimiko/arguments.h)
# There is the C++ source files.
set(SOURCE_FILES src/kimiko.cpp src/context.cpp)

# Build the static library.
add_library(kimiko ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(kimiko AperLambda::lambdacommon)

# Install if the option is on.
if (KIMIKO_INSTALL)
    foreach (LOOP_HEADER ${HEADER_FILES})
        get_filename_component(HEADER_PARENT_DIR ${LOOP_HEADER} DIRECTORY)
        install(FILES ${LOOP_HEADER} DESTINATION ${HEADER_PARENT_DIR})
    endforeach ()
    install(FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION share/licenses/kimiko)
    install(TARGETS kimiko
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)

    # Uninstall target.
    setup_uninstall_target()
endif ()

add_subdirectory(tests)