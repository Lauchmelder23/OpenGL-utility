add_executable(model 
	"main.cpp"
)

find_package(glfw3 REQUIRED)

target_include_directories(model PRIVATE 
	glfw
)

target_link_libraries(model PRIVATE 
	glfw
)

if(WIN32)
	target_link_libraries(model PRIVATE
		"$<TARGET_FILE_DIR:openglu>/$<TARGET_FILE_BASE_NAME:openglu>.lib"
	)
else()
	target_link_libraries(model PRIVATE
		$<TARGET_FILE:openglu>
	)
endif()

add_custom_command(TARGET model POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:model>/shaders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:model>/assets
)

if(WIN32)
	add_custom_command(TARGET model POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:openglu> $<TARGET_FILE:glfw> $<TARGET_FILE_DIR:model>
	)
endif()