#pragma once

#ifdef PE_PLATFORM_WINDOWS
	#ifdef PE_BUILD_DLL
		#define PRINCESS_API __declspec(dllexport)
	#else
		#define PRINCESS_API __declspec(dllimport)
	#endif
#else
	#error Princess only supports Windows!
#endif
