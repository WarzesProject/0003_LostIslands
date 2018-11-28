#pragma once

//=============================================================================
// Pre Header
//=============================================================================
#include "Base.h"

//=============================================================================
// STL and 3rdparty Header
//=============================================================================
#if COMPILER_MSVC
#	pragma warning(push, 1)
#endif

#include <memory>
#include <functional>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#if PLATFORM_EMSCRIPTEN
#	include <emscripten.h>
#endif

#if COMPILER_MSVC
#	pragma warning(pop)
#endif

//=============================================================================
// Post Header
//=============================================================================
#if COMPILER_MSVC
TODO("временно, про выравнивание");
#	pragma warning(disable: 4820) 
#endif

#include "Event.h"

