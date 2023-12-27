CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

ADD_LIBRARY(compiler_options INTERFACE)
ADD_LIBRARY(compiler_features INTERFACE)

PROJECT(Luna
        VERSION 0.1.0.0
        DESCRIPTION "A physics simulation playground"
        LANGUAGES CXX
)

TARGET_COMPILE_FEATURES(compiler_features INTERFACE cxx_std_20)

IF (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    TARGET_COMPILE_OPTIONS(compiler_options INTERFACE /W4 /WX /permissive-)
ELSE ()
    TARGET_COMPILE_OPTIONS(compiler_options INTERFACE -Wall -Wextra -pedantic -Werror)
ENDIF ()

ADD_EXECUTABLE(${PROJECT_NAME}
        src/main.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE compiler_options compiler_features)

