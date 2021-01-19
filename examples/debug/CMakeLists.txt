add_executable(debug "main.cpp")

find_package(glfw3 REQUIRED)

target_include_directories(debug PRIVATE 
	glfw
)

target_link_libraries(debug PRIVATE 
	"$<TARGET_FILE_DIR:openglu>/$<TARGET_FILE_BASE_NAME:openglu>.lib"
	glfw
)

add_custom_command(TARGET debug POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:openglu> $<TARGET_FILE:glfw> $<TARGET_FILE_DIR:debug>
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:debug>/shaders
)