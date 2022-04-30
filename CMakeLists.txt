cmake_minimum_required(VERSION 3.0.0)
project(PDFU-CPP VERSION 0.1.0)

include(CTest)
enable_testing()

add_library( podofo SHARED IMPORTED GLOBAL)
set_property(TARGET podofo PROPERTY
             IMPORTED_LOCATION "/lib/libpodofo.so")



add_executable(PDFU-CPP main.cpp)

TARGET_LINK_LIBRARIES(PDFU-CPP podofo)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
