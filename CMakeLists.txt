cmake_minimum_required(VERSION 2.8)

project(BarrenLands)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${GLU_INCLUDE_DIR} glimac/include third-party/include glcustom/include)

if(UNIX)
    set(ALL_LIBRARIES glimac glcustom ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLUT_LIBRARY} ${GLU_LIBRARY} fastnoise)
endif(UNIX)

if(WIN32)
    set(ALL_LIBRARIES mingw32 glcustom glimac fastnoise SDL2main SDL2 glew32s opengl32 freeglut glu32)
endif(WIN32)

add_subdirectory(glimac)
add_subdirectory(glcustom)
add_subdirectory(fastnoise)
add_subdirectory(barrenLands)
add_subdirectory(tests)

#if all files grey in CLion and red cross on build (or debug not found) -> build, click "build" in error popup, click ok -> let it do its thing -> try to build again
#if findXXX.cmake not included error -> look up a def of said file on the internet and include in CMake folder
#if lib not found through findXXX.cmake -> install said lib
#if '% error -> delete build files in cmake-build-debug folder