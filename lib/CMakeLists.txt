project(${LIB_NAME})


set_source_files_properties(module.cpp PROPERTIES CXX_SCAN_FOR_MODULES ON)
add_library(${PROJECT_NAME} STATIC module.cpp)
target_sources(${PROJECT_NAME} PUBLIC
        FILE_SET magis_modules TYPE CXX_MODULES FILES
        FILES
        module.cppm
)

if(USE_PCH)
    target_precompile_headers(${PROJECT_NAME} PRIVATE "stable.h")
endif()