cmake_minimum_required(VERSION 3.10)

project(OpenGLUtility)

# set(CMAKE_CXX_STANDARD 17)

set(build_examples ON CACHE BOOL "Build examples")
set(build_documentation ON CACHE BOOL "Generate documentation")

if(${build_documentation})
	find_package(Doxygen REQUIRED)
endif()

if(WIN32)
	add_compile_definitions(OGLU_WIN32)
endif()

file(GLOB_RECURSE include_files 
	"include/*.hpp"
)

file(GLOB_RECURSE source_files 
	"src/*.cpp"
	"vendor/src/*.c"
)

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

if(${build_documentation})
	configure_file(doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
    add_custom_target(openglu_doc ALL
		COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Building documentation..."
    )
endif()

if(${build_examples})
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