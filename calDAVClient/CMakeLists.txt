cmake_minimum_required(VERSION 3.20)

project(calDAVClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 1)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)


# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

set(CMAKE_PREFIX_PATH "/Users/leonardoperugini/Qt/5.15.2/clang_64")
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        Sources/mainwindow.cpp
        Headers/mainwindow.h
        Headers/mainwindow.ui
        Sources/Date.cpp Headers/Date.h Sources/Vcalendar.cpp Headers/Vcalendar.h Sources/Vevent.cpp Headers/Vevent.h Sources/Vtodo.cpp Headers/Vtodo.h Sources/loginwindow.cpp Headers/loginwindow.h Headers/loginwindow.ui Sources/API.cpp Headers/API.h Sources/createcalendarform.cpp Headers/createcalendarform.h Headers/createcalendarform.ui Sources/IcsParser.cpp Headers/IcsParser.h Sources/todo_information.cpp Headers/todo_information.h Headers/todo_information.ui Sources/event_information.cpp Headers/event_information.h Headers/event_information.ui Sources/createevent.cpp Headers/createevent.h Headers/createevent.ui Sources/createtodo.cpp Headers/createtodo.h Headers/createtodo.ui Sources/updatetodo.cpp Headers/updatetodo.h Headers/updatetodo.ui Sources/sharecalendarform.cpp Headers/sharecalendarform.h Headers/sharecalendarform.ui Sources/ipaddressform.cpp Headers/ipaddressform.h Headers/ipaddressform.ui)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(calDAVClient
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
else()
    if(ANDROID)
        add_library(calDAVClient SHARED
                ${PROJECT_SOURCES}
                )
    else()
        add_executable(calDAVClient
                ${PROJECT_SOURCES}
                )
    endif()
endif()


set_target_properties(calDAVClient PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calDAVClient)
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


####################################### CURL ###########################################



# All following targets should search these directories for headers
include_directories(
        curlpp-0.8.1/include

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
if(CMAKE_SYSTEM MATCHES "Windows")
    include_directories(C:/Users/lorep/Desktop/curl/builds/libcurl-vc-x64-release-dll-ipv6-sspi-schannel/include) #change the path
    target_link_libraries(${PROJECT_NAME}_lib
            "C:/Users/lorep/Desktop/curl/builds/libcurl-vc-x64-release-dll-ipv6-sspi-schannel-obj-lib/libcurl.lib"
            )
else()
    message(STATUS "Looking for CURL")
    include(FindCURL)
    find_package(CURL REQUIRED)

    if(CURL_FOUND)
        message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
        message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
        message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
        target_link_libraries(${PROJECT_NAME}_lib ${CURL_LIBRARIES})
    else()
        message(FATAL_ERROR "Could not find CURL")
    endif()

    # All following targets should search these directories for headers
    include_directories(
            ${CURL_INCLUDE_DIRS}
    )
endif()

install(DIRECTORY include/utilspp/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utilspp")
install(DIRECTORY include/curlpp/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/curlpp")

install(TARGETS ${PROJECT_NAME}_lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})


target_link_libraries(calDAVClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${PROJECT_NAME}_lib)