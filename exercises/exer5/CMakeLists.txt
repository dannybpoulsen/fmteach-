add_library (exer5 OBJECT exer.cpp solution.cpp)
target_link_libraries (exer5 PUBLIC ir cgraph execstate)

target_include_directories (exer5 PRIVATE ${PROJECT_SOURCE_DIR})
