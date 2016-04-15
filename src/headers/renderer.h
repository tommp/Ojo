#ifndef RENDERER_H
#define RENDERER_H

/* Project includes */
#include "DEFINES.h"
#include "HAL_window.h"
/* ================ */

/* System includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"	
/* =============== */

typedef struct Renderer{
	uint32_t screen_width;
   	uint32_t screen_height;

   	HAL_Window window;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;

	EGLint num_config;
	EGLConfig config;
}Renderer;

EGLint init_renderer(Renderer* renderer);

#endif