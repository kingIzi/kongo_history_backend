cmake_minimum_required(VERSION 3.14)

project(kongo_history_backend LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools Network)

set(TS_FILES kongo_history_backend_fr_BE.ts)

add_subdirectory(backend_tests/)
include_directories(src/include)

set(HEADER_FILES 
    src/include/request.hpp
)

set(SOURCE_FILES 
    src/src/request.cpp
)

add_library(kongo_history_backend
  main.cpp
  ${HEADER_FILES}
  ${SOURCE_FILES}
  ${TS_FILES}
)
target_link_libraries(kongo_history_backend Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

install(TARGETS kongo_history_backend
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
