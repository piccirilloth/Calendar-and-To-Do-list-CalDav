# Calendar and ToDo list (based on CalDAV standard)
This is a simple C++ application for managing calendar events and ToDo lists simultaneously, by leveraging QT Framework for GUI and multi-threading for the application logic (one of the focus points was also about dealing with concurrent access). This project was part of the final evaluation for the 2022 System Programming course of Computer Engineering Master's Degree in Politecnico di Torino.

## Build

You need CURL, cURLpp e QT libraries.<br/>
cURLpp is already present in the project folder

### Linux:
- run the following command to install CURL lib:
  - <code> sudo apt-get install libcurl4-openssl-dev </code>
- run the following command to install QT:
  - <code> sudo apt-get install qt5-default </code>

### MacOS
- CURL is present in the command line tools, install it by running the following command:
  - <code> xcode-select --install </code>
- install QT from [here](https://www.qt.io/download) 
- add to <code>CMakeList.txt</code> the following row: <code>set(CMAKE_PREFIX_PATH "__QTDir__/__version__/clang_64/")</code>

### Windows
- to install CURL run:
  - <code>git clone https://github.com/curl/curl.git</code>
  - <code>cd curl</code>
  - <code>buildconf.bat</code>
  - <code>“__pathForVisualStudio__\vc\Auxiliary\Build\vcvarsall.bat” x64</code>
  - <code>nmake /f Makefile.vc mode=dll MACHINE=x64</code>
  - at row 123 of <code>CMakeList.txt</code> modify the path with <code>__CURLBuildPath__/builds/libcurl-vc-x64-release-dll-ipv6-sspschannel/include</code> 
  - at row 125 of <code>CMakeList.txt</code> modify the path with <code>__CURLBuildPath__/builds/libcurl-vc-x64-release-dll-ipv6-sspi-schannel-obj-lib/libcurl.lib</code>
- install QT from [here](https://www.qt.io/download)
- set <b>VisualStudio</b> compiler on CLion
  
