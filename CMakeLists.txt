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
    ${APP_SRC_DIR}/experimentHandler.cpp
)
set(thirdPary_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/")


find_package (Threads REQUIRED)
find_package(OpenSSL REQUIRED) 
# find_package(nlohmann_json 3.10.2 REQUIRED)


include_directories(${thirdPary_DIR})

# cJSON
set(CJSON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cJSON")
set(cJSON_INCLUDE_DIR "${CJSON_PATH}")
set(cJSON_LINK_DIRECTORIES "${CJSON_PATH}/build_x86/")
include_directories(${cJSON_INCLUDE_DIR})
link_directories(${cJSON_LINK_DIRECTORIES})

add_executable (${PROJ_NAME}   ${APP_SOURCES}  )

TARGET_LINK_LIBRARIES(${PROJ_NAME} Threads::Threads)
TARGET_LINK_LIBRARIES(${PROJ_NAME} libcivetweb.a -ldl)
# TARGET_LINK_LIBRARIES(${PROJ_NAME} PRIVATE nlohmann_json::nlohmann_json)
TARGET_LINK_LIBRARIES(${PROJ_NAME} libcJSON.a)
