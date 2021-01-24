file(GLOB_RECURSE imgui_files
	"imgui/*.cpp"
)

add_executable(movement 
	"main.cpp" "shaders/fragmentShader.frag" "shaders/vertexShader.vert"
	${imgui_files}
)

find_package(glfw3 REQUIRED)

target_include_directories(movement PRIVATE 
	glfw
)

target_link_libraries(movement PRIVATE 
	"$<TARGET_FILE_DIR:openglu>/$<TARGET_FILE_BASE_NAME:openglu>.lib"
	glfw
)

add_custom_command(TARGET movement POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:openglu> $<TARGET_FILE:glfw> $<TARGET_FILE_DIR:movement>
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:movement>/shaders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:movement>/assets
)