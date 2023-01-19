add_library (exer2 OBJECT exer.cpp solution.cpp graph.cpp)
target_link_libraries (exer2 PUBLIC ir cgraph)
target_include_directories (exer2 PRIVATE ${PROJECT_SOURCE_DIR})
