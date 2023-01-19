project(fmteachbin)
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)


add_executable (fmteach main.cpp )
target_link_libraries (fmteach PUBLIC whiley exercise ${Boost_LIBRARIES})
