add_library (exer1 OBJECT exer.cpp solution.cpp)
target_link_libraries (exer1 PUBLIC ir)
target_include_directories (exer1 PRIVATE ${PROJECT_SOURCE_DIR})
