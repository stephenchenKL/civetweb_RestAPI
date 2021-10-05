cmake_minimum_required(VERSION 3.16)
set(PROJ_NAME httpSvcRestApi)
project(${PROJ_NAME} C CXX)

# civetweb
set(CIVETWEB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../civetweb")

#####################################################
# Sources and headers
#####################################################
# Relative path to the project sources, i.e. right above cmake/..
set (APP_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})  
set(APP_SOURCES ${APP_SOURCES} 
    ${APP_SRC_DIR}/main.cpp
)
