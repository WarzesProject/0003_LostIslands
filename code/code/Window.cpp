﻿// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Window.h"
//-----------------------------------------------------------------------------
bool Window::Init(EventHandler handler)
{
	m_eventHandler = handler;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!m_window)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context)
	{
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	if (!initGL())
		return false;

	SDL_StartTextInput(); //Enable text input

	return true;
}
//-----------------------------------------------------------------------------
void Window::Input()
{
	while (SDL_PollEvent(&m_curEvent) != 0)
	{
		if (m_curEvent.type == SDL_QUIT)
		{
			m_close = true;
			return;
		}
		//else if (m_curEvent.type == SDL_TEXTINPUT)
		//{
		//	int x = 0, y = 0;
		//	SDL_GetMouseState(&x, &y);
		//	//handleKeys(e.text.text[0], x, y);
		//}
	}
}
//-----------------------------------------------------------------------------
void Window::Swap()
{
	SDL_GL_SwapWindow(m_window);
}
//-----------------------------------------------------------------------------
void Window::Close()
{	
	SDL_StopTextInput(); //Disable text input
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
//-----------------------------------------------------------------------------
bool Window::initGL()
{
	GLenum error = GL_NO_ERROR;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf( "Error initializing OpenGL! %d\n",  error );
		return false;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf( "Error initializing OpenGL! %d\n",  error );
		return false;
	}

	glClearColor(0.f, 0.f, 0.f, 1.f);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf( "Error initializing OpenGL! %d\n", error );
		return false;
	}

	return true;
}
//-----------------------------------------------------------------------------