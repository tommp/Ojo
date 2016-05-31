#include "HAL_window.h"

EGLint init_window(HAL_Window* window){
#if WINDOW_SYSTEM == DISPMANX
	bcm_host_init();
	printf("Initializing Dispmanx window...\n\n");
	int32_t success = 0;
	success = graphics_get_display_size(0 /* LCD */, &window->screen_width, &window->screen_height);
	if (success < 0 ){
	      errorlogger("Failed to get display size!");
	      printf("Failed to get display size %d!", window->window_width);
	      return ERROR_INIT_WINDOW;
	}

	printf("Max screen size read: %dx%d\n\n", window->screen_width, window->screen_height);

	window->window_width = SAMPLE_WIDTH;
	window->window_height = SAMPLE_HEIGHT;

	window->dst_rect.x = 0;
	window->dst_rect.y = 0;
	window->dst_rect.width = window->window_width;
	window->dst_rect.height = window->window_height;

	window->src_rect.x = 0;
	window->src_rect.y = 0;
	window->src_rect.width = window->window_width;
	window->src_rect.height = window->window_height;

	window->dispman_display = vc_dispmanx_display_open(0 /* LCD */);
	window->dispman_update = vc_dispmanx_update_start(0);
	 
	window->dispman_element = vc_dispmanx_element_add(window->dispman_update, window->dispman_display,
				0/*layer*/, &window->dst_rect, 0/*src*/,
				&window->src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, 0/*transform*/);

	window->dispmanx_window.element = window->dispman_element;
	window->dispmanx_window.width = window->window_width;
	window->dispmanx_window.height = window->window_height;

	window->native_window = &window->dispmanx_window;
	vc_dispmanx_update_submit_sync(window->dispman_update);
	printf("Dispmanx window initialized!\n\n");
#endif

	return 0;
}
