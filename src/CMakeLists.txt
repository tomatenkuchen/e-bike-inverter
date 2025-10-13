###############################################################################
# hal definition
add_subdirectory(hal)

###############################################################################
# bsp definition
add_subdirectory(bsp)

###############################################################################
# target definition
add_executable(${CONAN_PROJECT_NAME}
  main.cpp
  isr.cpp
  syscalls.cpp
)

target_link_libraries(${CONAN_PROJECT_NAME}
  PRIVATE
    libbsp
)

target_include_directories(${CONAN_PROJECT_NAME}
  PRIVATE
    ${CMAKE_BINARY_DIR} # version.hpp
)

target_compile_features(${CONAN_PROJECT_NAME}
  PRIVATE
    cxx_std_23
)

target_compile_options(${CONAN_PROJECT_NAME}
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    # -Werror
)

target_link_options(${CONAN_PROJECT_NAME}
  PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
)

add_custom_command(
  TARGET ${CONAN_PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME}.hex
)

add_custom_command(
  TARGET ${CONAN_PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME}.bin
)

add_custom_command(
  TARGET ${CONAN_PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_READELF} -aC ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME} > ${CMAKE_CURRENT_BINARY_DIR}/${CONAN_PROJECT_NAME}.readelf
)
