add_library (execstate INTERFACE)
target_link_libraries (execstate INTERFACE ir)
target_include_directories (execstate INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
