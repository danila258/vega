# Install script for directory: /Users/danila/code_c++/vega/Vega/Backend/OpenXLSX

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX/headers" TYPE FILE FILES "/Users/danila/code_c++/vega/Vega/cmake-build-debug/Backend/OpenXLSX/OpenXLSX-Exports.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX/headers" TYPE FILE FILES
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/IZipArchive.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLCell.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLCellIterator.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLCellRange.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLCellReference.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLCellValue.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLColor.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLColumn.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLCommandQuery.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLConstants.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLContentTypes.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLDateTime.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLDocument.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLException.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLFormula.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLIterator.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLProperties.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLRelationships.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLRow.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLRowData.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLSharedStrings.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLSheet.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLWorkbook.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLXmlData.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLXmlFile.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLXmlParser.hpp"
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/headers/XLZipArchive.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX" TYPE FILE FILES "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/OpenXLSX.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/danila/code_c++/vega/Vega/cmake-build-debug/Backend/OpenXLSX/libOpenXLSXd.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenXLSXd.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenXLSXd.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenXLSXd.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES
    "/Users/danila/code_c++/vega/Vega/Backend/OpenXLSX/OpenXLSXConfig.cmake"
    "/Users/danila/code_c++/vega/Vega/cmake-build-debug/Backend/OpenXLSX/OpenXLSX/OpenXLSXConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake"
         "/Users/danila/code_c++/vega/Vega/cmake-build-debug/Backend/OpenXLSX/CMakeFiles/Export/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "/Users/danila/code_c++/vega/Vega/cmake-build-debug/Backend/OpenXLSX/CMakeFiles/Export/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "/Users/danila/code_c++/vega/Vega/cmake-build-debug/Backend/OpenXLSX/CMakeFiles/Export/lib/cmake/OpenXLSX/OpenXLSXTargets-debug.cmake")
  endif()
endif()

