project(exercises)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


add_subdirectory (exer1)
add_subdirectory (exer2)
add_subdirectory (exer3)
add_subdirectory (exer4)


add_library (exercise SHARED exercices_plug.cpp)
target_link_libraries (exercise PUBLIC ir exer1
		      		       	  exer2
					  exer3
					  exer4
					  
PRIVATE fmt)

target_include_directories  (exercise PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 

