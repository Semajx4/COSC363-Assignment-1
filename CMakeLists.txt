cmake_minimum_required(VERSION 2.8)

project(assignment1)


add_executable(ass1.out ass1.cpp spaceModels.cpp) 
add_executable(ass.out ass.cpp ) 

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries( ass1.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( ass.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

