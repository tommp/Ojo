#ifndef WINDOW_H
#define WINDOW_H

#include "HAL_DEFINES.h"
#include "CONFIG.h"

#include "errorlogger.h"

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

#include <stdio.h>
#include <stdlib.h>

#if WINDOW_SYSTEM == DISPMANX
#include "bcm_host.h"
#endif

typedef struct HAL_Window{
	uint32_t window_width;
	uint32_t window_height;
	uint32_t screen_width;
	uint32_t screen_height;
	EGLNativeWindowType native_window;

#if WINDOW_SYSTEM == DISPMANX
	EGL_DISPMANX_WINDOW_T dispmanx_window;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
   	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_UPDATE_HANDLE_T dispman_update;
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;
#endif

}HAL_Window;

EGLint init_window(HAL_Window* window);

#endif
