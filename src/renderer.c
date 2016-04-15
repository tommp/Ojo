#include "renderer.h"

EGLint init_renderer(Renderer* renderer){
	int32_t return_val = 0;
	EGLBoolean result;
	static const EGLint attribute_list[] ={
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};

	renderer->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (renderer->display == EGL_NO_DISPLAY){
		return ERROR_GET_DISPLAY;
	}

	result = eglInitialize(renderer->display, NULL, NULL);
   	if (result == EGL_FALSE){
		return ERROR_INIT_DISPLAY;
   	}

   	result = eglChooseConfig(renderer->display, attribute_list, renderer->config, 1, &renderer->num_config);
   	if (result == EGL_FALSE){
		return ERROR_CHOOSE_CONFIG;
   	}

   	/* Platform specific */

   	return_val = init_window(&renderer->window);//graphics_get_display_size(0 /* LCD */, renderer->screen_width, renderer->screen_height);
	if (return_val < 0 ){
		return ERROR_INIT_WINDOW;
	}

	/* ================= */

	renderer->context = eglCreateContext(renderer->display, renderer->config, EGL_NO_CONTEXT, NULL);
	if (renderer->context == EGL_NO_CONTEXT){
		return ERROR_CREATE_CONTEXT;
	}

	renderer->surface = eglCreateWindowSurface(renderer->display, renderer->config, renderer->window.native_window, NULL );
   	if (renderer->surface == EGL_NO_SURFACE){
   		return ERROR_CREATE_WINDOW_SURFACE;
   	}

	result = eglMakeCurrent(renderer->display, renderer->surface, renderer->surface, renderer->context);
	if (result == EGL_FALSE){
		return ERROR_MAKE_CURRENT;
   	}

	glClearColor(CLEARCOLOR);

	glEnable(GL_CULL_FACE);

	//glMatrixMode(GL_MODELVIEW);

	return 0;
}