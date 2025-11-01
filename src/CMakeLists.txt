###############################################################################
# hal definition
add_subdirectory(hal)

###############################################################################
# bsp definition
add_subdirectory(bsp)

###############################################################################
# target definition
add_executable(${CONAN_PROJECT_NAME}.elf
  main.cpp
  isr.cpp
  syscalls.cpp
)

target_link_libraries(${CONAN_PROJECT_NAME}.elf
  PRIVATE
    libbsp
)

target_include_directories(${CONAN_PROJECT_NAME}.elf
  PRIVATE
    ${CMAKE_BINARY_DIR} # version.hpp
)

target_compile_features(${CONAN_PROJECT_NAME}.elf
  PRIVATE
    cxx_std_23
)

target_compile_options(${CONAN_PROJECT_NAME}.elf
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Og
    # -Werror
)

target_link_options(${CONAN_PROJECT_NAME}.elf
  PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
)

add_custom_target(${CONAN_PROJECT_NAME}.hex ALL 
  COMMAND ${CMAKE_OBJCOPY} -O ihex
            ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME}.elf
            ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME}.hex

)
add_dependencies(${CONAN_PROJECT_NAME}.hex ${CONAN_PROJECT_NAME}.elf)

add_custom_target(${CONAN_PROJECT_NAME}.bin ALL 
  COMMAND ${CMAKE_OBJCOPY} -O binary
            ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME}.elf
            ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME}.bin
)
add_dependencies(${CONAN_PROJECT_NAME}.bin ${CONAN_PROJECT_NAME}.elf)

add_custom_target(${CONAN_PROJECT_NAME}.readelf ALL 
  COMMAND ${CMAKE_READELF} -aC
            ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME}.elf
            > ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME}.readelf
)
add_dependencies(${CONAN_PROJECT_NAME}.readelf ${CONAN_PROJECT_NAME}.elf)
