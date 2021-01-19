#ifndef CORE_HPP
#define CORE_HPP

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
