cmake_minimum_required(VERSION 3.10)

project(OpenGLUtility)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# set(CMAKE_CXX_STANDARD 17)

set(BUILD_EXAMPLES ON CACHE BOOL "Build examples")
set(BUILD_DOCUMENTATION ON CACHE BOOL "Generate documentation")

if(WIN32)
	set(EXPOSE_OPENGL OFF CACHE BOOL "If you want to use raw OpenGL functions in your app (e.g. to use ImGui) check this")
endif()

if(${BUILD_DOCUMENTATION})
	find_package(Doxygen REQUIRED)
endif()

if(WIN32)
	add_compile_definitions(OGLU_WIN32)
	if(${EXPOSE_OPENGL})
		add_compile_definitions(GLAD_GLAPI_EXPORT)
	endif()
endif()

file(GLOB_RECURSE include_files 
	"include/*.hpp"
)

file(GLOB_RECURSE source_files 
	"src/*.cpp"
	"vendor/src/*.c"
)

message(STATUS ${source_files})

add_library(openglu SHARED 
	${include_files}
	${source_files}
	"cpp.hint"
)

target_compile_definitions(openglu PRIVATE OGLU_BUILD_DLL)

include_directories(
	include
	vendor/include
)

target_include_directories(openglu PUBLIC
	include
	vendor/include
)

if(${BUILD_DOCUMENTATION})
	configure_file(doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
    add_custom_target(openglu_doc ALL
		COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Building documentation..."
    )
endif()

if(${BUILD_EXAMPLES})
	macro(subdirlist result curdir)
		file(GLOB children RELATIVE ${curdir} ${curdir}/*)
		set(dirlist "")
		foreach(child ${children})
			if(IS_DIRECTORY ${curdir}/${child})
				list(APPEND dirlist ${child})
			endif()
		endforeach()
		set(${result} ${dirlist})
	endmacro()

	subdirlist(samples ${CMAKE_SOURCE_DIR}/examples)
	foreach(sample ${samples})
		add_subdirectory(examples/${sample})
	endforeach()
endif()

install(
	TARGETS openglu
	LIBRARY DESTINATION lib
)