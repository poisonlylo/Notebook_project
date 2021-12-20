cmake_minimum_required(VERSION 3.20)
project(notebook_project_using_C C)

#include directories
include_directories(/usr/local/mysql-connector-c-6.1.11-macos10.12-x86_64/include) #include folder location
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})

#link directories
link_directories(/usr/local/mysql-connector-c-6.1.11-macos10.12-x86_64/lib) #lib folder location
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

add_executable(notebook_project_using_C main.c)
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

set (Cmake_c_standard one)
#link to library (TARGET_LINK_LIBRARIES)
TARGET_LINK_LIBRARIES(notebook_project_using_C ${GTK3_LIBRARIES})
target_link_libraries(notebook_project_using_C /usr/local/mysql-8.0.27-macos11-x86_64/lib/libmysqlclient.dylib)





set(CMAKE_C_STANDARD 99)

