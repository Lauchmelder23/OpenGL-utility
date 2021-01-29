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
#include <iostream>
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

namespace oglu
{
	class NullBuffer : public std::streambuf
	{
	public:
		int overflow(int c) { return c; }
	};

	class NullStream : public std::ostream
	{
	public:
		NullStream() : std::ostream(&buf) {}

	private:
		NullBuffer buf;
	};

	extern OGLU_API NullStream cnull;
}

#ifndef NDEBUG
	#define OGLU_ERROR_STREAM std::cerr
#else
	#define OGLU_ERROR_STREAM oglu::cnull
#endif

#endif
