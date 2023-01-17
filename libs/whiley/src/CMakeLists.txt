find_package (BISON REQUIRED)
find_package (FLEX REQUIRED)

flex_target(flexer lexer.l "${CMAKE_CURRENT_BINARY_DIR}/lexer.cc")
bison_target(bparser parser.y "${CMAKE_CURRENT_BINARY_DIR}/parser.cc")
add_flex_bison_dependency(flexer bparser)

add_library (whiley STATIC ast.cpp wparser.cpp "${CMAKE_CURRENT_BINARY_DIR}/lexer.cc" "${CMAKE_CURRENT_BINARY_DIR}/parser.cc")
target_include_directories (whiley PUBLIC ${PROJECT_SOURCE_DIR}/include PRIVATE "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
