add_library(cmsis INTERFACE)

target_include_directories(cmsis INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Include
  ${CMAKE_CURRENT_SOURCE_DIR}/Device/ST/STM32G4xx/Include
)
