cmake_minimum_required(VERSION 3.5)

project(Car_Audio LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_subdirectory(MusicPlayer)
add_subdirectory(Volume)

add_executable(Car_Audio
    main.cpp
    mainwindow.cpp
    mainwindow.h
    brightness.cpp
    brightness.h
    equalizerdialog.h
    equalizerdialog.cpp
)

target_link_libraries(Car_Audio PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Volume MusicPlayer)
