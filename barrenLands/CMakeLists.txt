include_directories(include)

file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)
set(MAIN main.cpp)
set(OUTPUT barrenLands)

#qt5_generate_moc(main.cpp main.moc)
add_executable(${OUTPUT} ${MAIN} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})

# Tell CMake to create the helloworld executable

#Link the helloworld executable to the Qt 5 widgets library.
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

