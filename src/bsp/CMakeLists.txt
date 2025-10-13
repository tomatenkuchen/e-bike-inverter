add_library(libbsp
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core.cpp
)

target_link_libraries(libbsp
  PUBLIC
    stm32g4-hal
)

target_include_directories(libbsp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(libbsp PRIVATE cxx_std_23)
