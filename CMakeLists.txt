cmake_minimum_required(VERSION 3.5)

project(Vega VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/Users/danila/Qt/6.2.4/macos/lib/cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Concurrent)

qt_add_resources(SOURCES Resources.qrc)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Backend/OpenXLSX/)

set(PROJECT_SOURCES
        ${SOURCES}
        UI/main.cpp
        UI/MainWidget.cpp
        UI/MainWidget.h
        UI/ScheduleTab.cpp
        UI/ScheduleTab.h
        UI/SettingsTab.cpp
        UI/SettingsTab.h
        Backend/Parser.h
        Backend/Parser.cpp
        Backend/Downloader.h
        Backend/Downloader.cpp)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Vega
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Vega APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Vega SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Vega
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Vega PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network Qt6::Concurrent OpenXLSX::OpenXLSX)

set_target_properties(Vega PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Vega)
endif()
