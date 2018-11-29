#pragma once

// OpenGL states/caps
// This breaks strict opengl context ownership
extern int g_max_texture_size;
extern bool g_has_texture_npot;
extern int g_texture_filter;

void ProbeOpenGL();