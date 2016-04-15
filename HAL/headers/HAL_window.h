#ifndef WINDOW_H
#define WINDOW_H

#include "HAL_DEFINES.h"

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"	

#if RBP2
#include "bcm_host.h"
#endif

typedef struct HAL_Window{
	uint32_t window_width;
	uint32_t window_height;
	
#if SDL2
	EGLNativeWindowType native_window;
#endif

#if RBP2
	static EGL_DISPMANX_WINDOW_T native_window;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
   	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_UPDATE_HANDLE_T dispman_update;
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;
#endif

}HAL_Window;

EGLint init_window(HAL_Window* window);

#endif