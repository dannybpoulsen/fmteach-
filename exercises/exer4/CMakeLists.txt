add_library (exer4 OBJECT exer.cpp solution.cpp)
target_link_libraries (exer4 PUBLIC ir cgraph execstate)

target_include_directories (exer4 PRIVATE ${PROJECT_SOURCE_DIR})
