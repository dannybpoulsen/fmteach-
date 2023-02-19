add_library (exer3 OBJECT exer.cpp solution.cpp)
target_link_libraries (exer3 PUBLIC ir cgraph execstate)
target_include_directories (exer3 PRIVATE ${PROJECT_SOURCE_DIR})
