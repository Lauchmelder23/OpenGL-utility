/*****************************************************************//**
 * \file   core.hpp
 * \brief  Core includes and defines
 * 
 * \author Robert
 * \date   January 2021
 *********************************************************************/

#ifndef CORE_HPP
#define CORE_HPP

#pragma warning(disable : 4251)

#include <memory>
#include <stdexcept>
#include <string>

#include <glad/glad.h>


#ifdef OGLU_WIN32
	#ifdef OGLU_BUILD_DLL
		#define OGLU_API __declspec(dllexport)
	#else
		#define OGLU_API __declspec(dllimport)
	#endif //OGLU_BUILD_DLL
#else
	#define OGLU_API
#endif //OGLU_WIN32

#endif
