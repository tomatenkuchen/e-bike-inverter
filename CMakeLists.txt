###############################################################################
# cmake variables
cmake_minimum_required(VERSION 4.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###############################################################################
# convert version info to header
configure_file(${CMAKE_SOURCE_DIR}/cmake/version.hpp.in ${CMAKE_BINARY_DIR}/version.hpp)

###############################################################################
# find dependencies

# compiler suite
find_program(CMAKE_OBJCOPY arm-none-eabi-objcopy)
find_program(CMAKE_SIZE    arm-none-eabi-size)
find_program(CMAKE_OBJDUMP arm-none-eabi-objdump)
find_program(CMAKE_READELF arm-none-eabi-readelf)

# cppcheck
# find_program(CMAKE_CXX_CPPCHECK cppcheck REQUIRED)

###############################################################################
# cppcheck configuration
# list(
#     APPEND CMAKE_CXX_CPPCHECK
#       "--enable=warning,style"
#       "-cppcheck-build-dir=${CMAKE_BINARY_DIR}"
# )

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
