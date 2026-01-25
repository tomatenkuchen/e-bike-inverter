add_library(libbsp
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/hall-sensors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/hall-sensors.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/uart-interface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/uart-interface.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inverter.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inverter.cpp
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

target_link_libraries(libbsp PUBLIC mp-units::mp-units)
