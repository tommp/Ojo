#ifndef RENDERER_H
#define RENDERER_H

#include "HAL_DEFINES.h"
#include "HAL_window.h"

#include "errorlogger.h"
#include "utility.h"
#include "shader.h"

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
        uint32_t buffer_width;
        uint32_t buffer_height;

        EGLint num_configs;
        EGLConfig* configs;
        EGLConfig config;

   	HAL_Window window;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;

	GLuint quad_VBO;
	GLuint* framebuffers;
}Renderer;

EGLint init_renderer(Renderer* renderer);
EGLint destroy_renderer(Renderer* renderer);

EGLint init_display(Renderer* renderer);
EGLint bind_api();
EGLint init_context(Renderer* renderer);
EGLint init_surface(Renderer* renderer);

GLint init_ogl(Renderer* renderer);
GLint init_framebuffers(Renderer* renderer);
GLint init_quad(Renderer* renderer);

GLint print_configs(Renderer* renderer, EGLint num_configs);
GLint upload_buffer_size(Renderer* renderer, Shader* shader);

GLint render_quad(Renderer* renderer);

#endif
