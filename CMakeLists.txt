CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

ADD_LIBRARY(luna_compiler_options INTERFACE)
ADD_LIBRARY(luna_compiler_features INTERFACE)

PROJECT(Luna
        VERSION 0.1.0.0
        DESCRIPTION "A physics simulation playground"
        LANGUAGES CXX
)

TARGET_COMPILE_FEATURES(luna_compiler_features INTERFACE cxx_std_20)

IF (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    TARGET_COMPILE_OPTIONS(luna_compiler_options INTERFACE /W4 /WX /permissive-)
ELSE ()
    TARGET_COMPILE_OPTIONS(luna_compiler_options INTERFACE -Wall -Wextra -pedantic -Werror)
ENDIF ()

ADD_EXECUTABLE(${PROJECT_NAME}
        src/main.cpp
        src/logging/Logging.cpp
        include/luna/logging/Logging.hpp)

ADD_SUBDIRECTORY(external/rupe)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC luna_compiler_options luna_compiler_features Rupe)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# GLFW3
FIND_PACKAGE(glfw3 CONFIG REQUIRED)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE glfw)

# IMGUI
FIND_PACKAGE(imgui CONFIG REQUIRED)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE imgui::imgui)

# Log4Cplus
FIND_PACKAGE(log4cplus CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE log4cplus::log4cplus)