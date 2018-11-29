#pragma once

//=============================================================================
// Pre Header
//=============================================================================
#include "Base.h"
#include "Define.h"

//=============================================================================
// STL and 3rdparty Header
//=============================================================================
#if COMPILER_MSVC
#	pragma warning(push, 1)
#endif

#include <cstdint>
#include <cctype>

#include <memory>
#include <functional>
#include <chrono>
#include <algorithm>
#include <mutex>
#include <thread>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#if PLATFORM_EMSCRIPTEN
#	include <emscripten.h>
#endif

#undef LoadBitmap // There is a function with same name in WinAPI
// OpenGL 1.2+
#define GL_BGRA 0x80E1

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



