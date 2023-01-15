add_library (ir STATIC instructions.cpp)
target_include_directories (ir PUBLIC ${PROJECT_SOURCE_DIR}/include)
