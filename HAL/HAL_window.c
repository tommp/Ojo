#include "HAL_window.h"

EGLint init_window(HAL_Window* window){
#if RBP2
	int32_t success = 0;
	success = graphics_get_display_size(0 /* LCD */, &window->window_width, &window->window_height);
	if (success < 0 ){
		return ERROR_WINDOW_INIT;
	}

	window->dst_rect.x = 0;
	window->dst_rect.y = 0;
	window->dst_rect.width = window->window_width;
	window->dst_rect.height = window->window_height;

	window->src_rect.x = 0;
	window->src_rect.y = 0;
	window->src_rect.width = window->window_width << 16;
	window->src_rect.height = window->window_height << 16;        

	window->dispman_display = vc_dispmanx_display_open(0 /* LCD */);
	window->dispman_update = vc_dispmanx_update_start(0);
	 
	window->dispman_element = vc_dispmanx_element_add(window->dispman_update, window->dispman_display,
				0/*layer*/, &window->dst_rect, 0/*src*/,
				&window->src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, 0/*transform*/);

	window->dispmax_window.element = window->dispman_element;
	window->dispmax_window.width = window->window_width;
	window->dispmax_window.height = window->window_height;

	native_window = &dispmax_window;
	vc_dispmanx_update_submit_sync(window->dispman_update);
#endif

	return 0;
}