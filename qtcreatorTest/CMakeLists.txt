cmake_minimum_required(VERSION 3.20)

project(qtcreatorTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        Sources/mainwindow.cpp
        Headers/mainwindow.h
        Headers/mainwindow.ui
        Sources/Date.cpp Headers/Date.h Sources/Vcalendar.cpp Headers/Vcalendar.h Sources/Vevent.cpp Headers/Vevent.h Sources/Vtodo.cpp Headers/Vtodo.h Sources/loginwindow.cpp Headers/loginwindow.h Headers/loginwindow.ui Sources/API.cpp Headers/API.h Sources/createcalendarform.cpp Headers/createcalendarform.h Headers/createcalendarform.ui Sources/IcsParser.cpp Headers/IcsParser.h Sources/todo_information.cpp Headers/todo_information.h Headers/todo_information.ui Sources/event_information.cpp Headers/event_information.h Headers/event_information.ui Sources/createevent.cpp Headers/createevent.h Headers/createevent.ui Sources/createtodo.cpp Headers/createtodo.h Headers/createtodo.ui Sources/updatetodo.cpp Headers/updatetodo.h Headers/updatetodo.ui)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qtcreatorTest
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
else()
    if(ANDROID)
        add_library(qtcreatorTest SHARED
                ${PROJECT_SOURCES}
                )
    else()
        add_executable(qtcreatorTest
                ${PROJECT_SOURCES}
                )
    endif()
endif()


set_target_properties(qtcreatorTest PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qtcreatorTest)
endif()

########### CURL/CURLPP ############

if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW) # MACOSX_RPATH
    set(CMAKE_MACOSX_RPATH TRUE)
endif()

# for unix platform, define install directories.
include(GNUInstallDirs)

if(WIN32)
    # cmake 3.4 is required for CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS
    cmake_minimum_required(VERSION 3.4)

    # c++ 11 support from cmake 3.4 or newer
    set(CMAKE_CXX_STANDARD 11) # C++11...
    set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
    set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} VERSION_LESS 3.1)
        cmake_minimum_required(VERSION 2.8)
        # c++11 support for cmake 2.8.12 - 3.0.x
        #
        # for non-windows platform we try to keep cmake 2.8 support
        # since entreprise distribution tends to have 2.8 version.
        add_compile_options(-std=c++11)
    else()
        # c++ 11 support from cmake 3.1 or newer
        set(CMAKE_CXX_STANDARD 11) # C++11...
        set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
        set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
    endif()
endif()



# Conan.io integration
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

# extra (pkg-config-related files)
add_subdirectory(curlpp-0.8.1/extras)

#########################################################################################
# Look for dependencies

# Documented at https://cmake.org/cmake/help/v3.0/module/FindCURL.html?highlight=curlpp
# Seems simple.

message(STATUS "Looking for CURL")
include(FindCURL)
find_package(CURL REQUIRED)

if(CURL_FOUND)
    message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
    message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
    message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
else()
    message(FATAL_ERROR "Could not find CURL")
endif()

# All following targets should search these directories for headers
include_directories(
        curlpp-0.8.1/include
        ${CURL_INCLUDE_DIRS}
)

#########################################################################################
# Define Targets

# If building on windows, install path will be in build/winbuild
if(CMAKE_SYSTEM MATCHES "Windows")
    set(CMAKE_INSTALL_PREFIX "winbuild")
endif()

file(GLOB_RECURSE HeaderFileList "curlpp-0.8.1/include/*")
file(GLOB_RECURSE SourceFileList "curlpp-0.8.1/src/*")
add_library(${PROJECT_NAME}_lib SHARED ${HeaderFileList} ${SourceFileList})
target_link_libraries(${PROJECT_NAME}_lib ${CURL_LIBRARIES} ${CONAN_LIBS})
set_target_properties(${PROJECT_NAME}_lib PROPERTIES SOVERSION 1 VERSION 1.0.0)

add_library(${PROJECT_NAME}_static_lib STATIC ${HeaderFileList} ${SourceFileList})

# Make sure that on unix-platforms shared and static libraries have
# the same root name, but different suffixes.
#
#  (solution taken from https://cmake.org/Wiki/CMake_FAQ#How_do_I_make_my_shared_and_static_libraries_have_the_same_root_name.2C_but_different_suffixes.3F)
#
# Making shared and static libraries have the same root name, but different suffixes
SET_TARGET_PROPERTIES(${PROJECT_NAME}_static_lib PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_static_lib)
# Now the library target "curlpp_static" will be named "curlpp.lib" with MS tools.
# This conflicts with the "curlpp.lib" import library corresponding to "curlpp.dll",
# so we add a "lib" prefix (which is default on other platforms anyway):
SET_TARGET_PROPERTIES(${PROJECT_NAME}_static_lib PROPERTIES PREFIX "lib")
target_link_libraries(${PROJECT_NAME}_static_lib ${CURL_LIBRARIES} ${CONAN_LIBS})
# install headers
install(DIRECTORY include/utilspp/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utilspp")
install(DIRECTORY include/curlpp/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/curlpp")

install(TARGETS ${PROJECT_NAME}_lib ${PROJECT_NAME}_static_lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})


target_link_libraries(qtcreatorTest PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${PROJECT_NAME}_lib)