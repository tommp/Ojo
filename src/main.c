#include "main.h"


int main(int argc, char* argv[]) {
	EGLint return_val = 0;

	Renderer renderer;
	return_val = init_renderer(&renderer);
	if (return_val < 0){
		return ERROR_INIT_RENDERER;
	}
	
	return 0;
}