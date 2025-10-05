###############################################################################
# cmake variables
cmake_minimum_required(VERSION 4.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

###############################################################################
# convert version info to header
configure_file(${CMAKE_SOURCE_DIR}/cmake/version.hpp.in ${CMAKE_BINARY_DIR}/version.hpp)

###############################################################################
# project definition
project(${CONAN_PROJECT_NAME}
        VERSION ${CONAN_PROJECT_VERSION}
        DESCRIPTION ${CONAN_PROJECT_DESCRIPTION}
        LANGUAGES C CXX
)

###############################################################################
# embedded executable definition
add_subdirectory(src)
