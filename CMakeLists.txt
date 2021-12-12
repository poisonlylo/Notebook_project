cmake_minimum_required(VERSION 3.20)
project(notebook_project_using_C C)

add_executable(notebook_project_using_C main.c)

target_link_libraries(notebook_project_using_C /usr/local/mysql-8.0.27-macos11-x86_64/lib/libmysqlclient.dylib)
include_directories(/usr/local/mysql-connector-c-6.1.11-macos10.12-x86_64/include) #include folder location
link_directories(/usr/local/mysql-connector-c-6.1.11-macos10.12-x86_64/lib) #lib folder location




set(CMAKE_C_STANDARD 99)

