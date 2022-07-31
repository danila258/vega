cmake_minimum_required(VERSION 3.5)

project(Vega VERSION 1.0 LANGUAGES CXX)

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
        UI/CommonFunctions.cpp
        UI/CommonFunctions.h
        Backend/Parser.cpp
        Backend/Parser.h
        Backend/Downloader.cpp
        Backend/Downloader.h)

if (APPLE)
    # set icon
    set(MACOSX_BUNDLE_ICON_FILE Vega.icns)
    set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/Resources/App_icon/Apple/Vega.icns")
    set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    qt_add_executable(Vega
        MACOSX_BUNDLE
        MANUAL_FINALIZATION
        ${app_icon_macos}
        ${PROJECT_SOURCES}
    )
endif()

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#    qt_add_executable(Vega
#        MACOSX_BUNDLE
#        ${app_icon_macos}
#        MANUAL_FINALIZATION
#        ${PROJECT_SOURCES}
#    )
#else()
#    if(ANDROID)
#        add_library(Vega SHARED
#            ${PROJECT_SOURCES}
#        )
#    else()
#        qt_add_executable(Vega
#            MACOSX_BUNDLE
#            ${app_icon_macos}
#            ${PROJECT_SOURCES}
#        )
#    endif()
#endif()

target_link_libraries(Vega PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network Qt6::Concurrent OpenXLSX::OpenXLSX)

if (APPLE)

    set_target_properties(Vega PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_EXECUTABLE_NAME Vega
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}

        XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER my.example.com
        XCODE_ATTRIBUTE_EXECUTABLE_NAME Vega
    )

    # xcode did not find the library
    add_custom_target(lib_linking WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

    add_custom_command(TARGET lib_linking PRE_BUILD
      COMMAND ln -sF ${CMAKE_BINARY_DIR}/Backend/OpenXLSX/Debug-${CMAKE_OSX_SYSROOT}
      ${CMAKE_BINARY_DIR}/Backend/OpenXLSX/Debug
    )

    add_dependencies(Vega lib_linking)

endif()

set_target_properties(Vega PROPERTIES
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Vega Icon)
endif()
