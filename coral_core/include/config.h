#pragma once

namespace coral
{
namespace config
{

/* Config file that is generated from cmake */

#define CORAL_VERSION_MAJOR 0
#define CORAL_VERSION_MINOR 0
#define CORAL_VERSION_PATCH 1
#define CORAL_VERSION_TWEAK 
#define CORAL_VERSION "0.0.1"

/* if cmake is configered to build shared or static libs */
#if defined(CORAL_DLL_EXPORT)
	#define CORAL_DLL __declspec(dllexport)
#elif defined(CORAL_DLL_IMPORT)
	#define CORAL_DLL __declspec(dllimport)
#else
	#define CORAL_DLL 
#endif

}; // config
}; // coral
