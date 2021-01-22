add_executable(model_loading "main.cpp")

find_package(glfw3 REQUIRED)

target_include_directories(model_loading PRIVATE 
	glfw
)

target_link_libraries(model_loading PRIVATE 
	"$<TARGET_FILE_DIR:openglu>/$<TARGET_FILE_BASE_NAME:openglu>.lib"
	glfw
)

add_custom_command(TARGET model_loading POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:openglu> $<TARGET_FILE:glfw> $<TARGET_FILE_DIR:model_loading>
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:model_loading>/shaders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:model_loading>/assets
)