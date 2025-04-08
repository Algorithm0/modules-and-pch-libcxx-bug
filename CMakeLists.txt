cmake_minimum_required(VERSION 3.28)
project(clang_bug)

#set(USE_STD_FORMAT ON)
#set(USE_PCH ON)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BASE_NAME ${PROJECT_NAME})
set(APP_NAME ${BASE_NAME}_app)
set(LIB_NAME ${BASE_NAME}_lib)

if(USE_PCH)
    add_compile_definitions(USE_PCH)
endif()

if(USE_STD_FORMAT)
    add_compile_definitions(USE_STD_FORMAT)
endif ()

add_subdirectory(lib)
add_subdirectory(app)
