#include "main.h"


int main(int argc, char* argv[]) {
	EGLint return_val = 0;
    return_val = init_check();
    if (return_val < 0){
        return ERROR_MACRO_INIT;
    }

	Renderer renderer;
	return_val = init_renderer(&renderer);
	if (return_val < 0){
		return ERROR_INIT_RENDERER;
	}
	
	return 0;
}

EGLint init_check(){
    if( !WINDOW_SYSTEM ){
        return ERROR_WINDOW_SYSTEM_INIT;
    }
    if( !IMAGE_SAMPLER ){
        return ERROR_IMAGE_SAMPLER_INIT;
    }
    else{
        return 0;
    }
}
