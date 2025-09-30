cmake_minimum_required(VERSION 3.15)
project(batterycharger CXX)



add_executable(batterycharger src/batterycharger.cpp src/main.cpp)



install(TARGETS batterycharger DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
