add_executable(debug "main.cpp" "shaders/fragmentShader.frag" "shaders/vertexShader.vert")

find_package(glfw3 REQUIRED)

target_include_directories(debug PRIVATE 
	glfw
)

target_link_libraries(debug PRIVATE 
	glfw
)

if(WIN32)
	target_link_libraries(debug PRIVATE
		"$<TARGET_FILE_DIR:openglu>/$<TARGET_FILE_BASE_NAME:openglu>.lib"
	)
else()
	target_link_libraries(debug PRIVATE
		$<TARGET_FILE:openglu>
	)
endif()

add_custom_command(TARGET debug POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:debug>/shaders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:debug>/assets
)

if(WIN32)
	add_custom_command(TARGET debug POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:openglu> $<TARGET_FILE:glfw> $<TARGET_FILE_DIR:debug>
	)
endif()