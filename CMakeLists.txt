cmake_minimum_required(VERSION 3.5)

project(Vega VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

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
        UI/CustomElements.cpp
        UI/CustomElements.h
        UI/CommonFunctions.cpp
        UI/CommonFunctions.h
        Backend/Parser.cpp
        Backend/Parser.h
        Backend/Downloader.cpp
        Backend/Downloader.h
    )

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE Vega.icns)
    set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/Resources/VegaIcon/MacOS/Vega.icns")
    set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    qt_add_executable(Vega
        MACOSX_BUNDLE
        ${app_icon_macos}
        ${PROJECT_SOURCES}
    )
elseif(ANDROID)
    #include(${ANDROID_SDK_ROOT}/android_openssl/CMakeLists.txt)
    #include(./Backend/android_openssl/CMakeLists.txt)

    set(ANDROID_EXTRA_LIBS
        ./Backend/android_openssl/latest/arm64/libcrypto_1_1.so
        ./Backend/android_openssl/latest/arm64/libssl_1_1.so
    CACHE INTERNAL "")

    qt_add_executable(Vega
        ${PROJECT_SOURCES}
    )
elseif(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    qt_add_executable(Vega
        ${PROJECT_SOURCES}
    )
elseif(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    qt_add_executable(Vega
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    set_target_properties(Vega PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

target_link_libraries(Vega PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    OpenXLSX::OpenXLSX
)

#settings

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

    add_custom_target(lib_linking WORKING_DIRECTORY ${CMAKE_BINARY_DIR})    # xcode did not find the library

    add_custom_command(TARGET lib_linking PRE_BUILD
      COMMAND ln -sF ${CMAKE_BINARY_DIR}/Backend/OpenXLSX/Debug-${CMAKE_OSX_SYSROOT}
      ${CMAKE_BINARY_DIR}/Backend/OpenXLSX/Debug
    )

    add_dependencies(Vega lib_linking)
endif()

if (ANDROID)
    set(ANDROID_PLATFORM_ARCHITECTURE_CODE "xxx")
      if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
        set(ANDROID_PLATFORM_ARCHITECTURE_CODE "032")
      elseif (${ANDROID_ABI} STREQUAL "arm64-v8a")
        set(ANDROID_PLATFORM_ARCHITECTURE_CODE "064")
      elseif (${ANDROID_ABI} STREQUAL "x86")
        set(ANDROID_PLATFORM_ARCHITECTURE_CODE "132")
      elseif (${ANDROID_ABI} STREQUAL "x86_64")
        set(ANDROID_PLATFORM_ARCHITECTURE_CODE "164")
      endif()

      set(ANDROID_VERSION_CODE "${ANDROID_PLATFORM_ARCHITECTURE_CODE}${PROJECT_VERSION_MAJOR}${PROJECT_VERSION_MINOR}")
      set_property(TARGET Vega APPEND PROPERTY QT_ANDROID_VERSION_CODE ${ANDROID_VERSION_CODE})
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Vega)
endif()
