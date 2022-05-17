project(kr)
add_executable(kr kr.cpp task.report.md.in.txt)
target_link_libraries(kr ${OpenCV_LIBS})

# prepare report md file
file(READ kr.cpp cpp_source)
configure_file(task.report.md.in.txt ${CMAKE_CURRENT_BINARY_DIR}/task.report.md @ONLY)
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/task.report.md" "$<TARGET_FILE_DIR:${PROJECT_NAME}>")