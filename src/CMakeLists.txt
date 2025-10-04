###############################################################################
# target definition
add_subdirectory(hal)

###############################################################################
# target definition
add_executable(${CONAN_PROJECT_NAME}
  main.cpp
)

target_link_libraries(${CONAN_PROJECT_NAME}
  PRIVATE
    stm32g4-hal
)

target_include_directories(${CONAN_PROJECT_NAME}
  PRIVATE
    ${CMAKE_BINARY_DIR}
)
