#ifndef RENDERER_H
#define RENDERER_H

#include "HAL_DEFINES.h"
#include "HAL_window.h"

#include "errorlogger.h"
#include "utility.h"

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

typedef struct Renderer{
	uint32_t screen_width;
   	uint32_t screen_height;

   	HAL_Window window;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;

	EGLint num_config;
	EGLConfig config;

	GLuint* framebuffers;
}Renderer;

EGLint init_renderer(Renderer* renderer);
EGLint destroy_renderer(Renderer* renderer);

EGLint init_display(Renderer* renderer);
EGLint init_context(Renderer* renderer);
EGLint init_surface(Renderer* renderer);

GLint init_ogl();
GLint init_framebuffers(Renderer* renderer);

#endif
