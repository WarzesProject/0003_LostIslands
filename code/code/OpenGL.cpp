// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "OpenGL.h"
#include "Log.h"

//-----------------------------------------------------------------------------
int g_max_texture_size = 256;
bool g_has_texture_npot = false;
int g_texture_filter = GL_LINEAR;
//-----------------------------------------------------------------------------
void ProbeOpenGL()
{
	GLint size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
	g_max_texture_size = size;
	LOG(Info, "OpenGL: maximum texture size is " << size << "x" << size);

	std::string extensions = (const char*)glGetString(GL_EXTENSIONS);
	std::transform(extensions.begin(), extensions.end(), extensions.begin(), ::tolower);
	g_has_texture_npot = extensions.find("gl_arb_texture_non_power_of_two") != std::string::npos;
	LOG(Info, "OpenGL: GPU " << (g_has_texture_npot ? "supports" : "does not support") << " NPOTD textures");
}
//-----------------------------------------------------------------------------