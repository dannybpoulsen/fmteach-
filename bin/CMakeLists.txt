project(fmteachbin)
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)

add_subdirectory (exer1)
add_executable (fmteach main.cpp exercices_plug.cpp)
target_link_libraries (fmteach PUBLIC whiley ir exer1 ${Boost_LIBRARIES} fmt)
