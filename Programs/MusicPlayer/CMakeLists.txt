cmake_minimum_required(VERSION 3.5)

project(MusicPlayer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia REQUIRED)


#add_executable(player
#    main.cpp)

add_library(MusicPlayer
    album.h
    album.cpp
    albumview.cpp
    albumview.h
    player.cpp
    player.h
    musicplayer.cpp
    musicplayer.h
)

target_compile_definitions(MusicPlayer PRIVATE -DMUSIC_LIBRARY="/home/daniel/Documents/music2/")

target_link_libraries(MusicPlayer PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
target_link_libraries(MusicPlayer PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(player PUBLIC MusicPlayer)
