project(${APP_NAME})

set_source_files_properties("main.cpp" PROPERTIES CXX_SCAN_FOR_MODULES ON)
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_NAME})

if(USE_PCH)
    target_precompile_headers(${PROJECT_NAME} PRIVATE "stable.h")
endif()