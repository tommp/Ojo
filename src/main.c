#include "main.h"


int main(int argc, char* argv[]) {
    EGLint return_val = 0;

    printf("Initializing renderer...\n\n");
    Renderer renderer;
    return_val = init_renderer(&renderer);
    if (return_val < 0){
        errorlogger("Failed to initialize renderer!");
        return ERROR_INIT_RENDERER;
    }
    printf("Renderer initialized!\n\n");

    printf("Initializing image sampler...\n\n");
    HAL_image_sampler sampler;
    return_val = init_image_sampler(&sampler);
    if (return_val < 0){
        errorlogger("Failed to initialize image sampler!");
        return ERROR_INIT_SAMPLER;
    }
    printf("Image sampler initialized!\n\n");

    //Main Loop
    capture_image(&sampler);
    GLuint running = 1;
    while(running){
        break;
    }

    printf("Cleaning up...\n\n");
    return_val = destroy_renderer(&renderer);
    if (return_val < 0){
        errorlogger("Failed to destroy renderer!");
        return ERROR_DESTROY_RENDERER;
    }

    return_val = destroy_image_sampler(&sampler);
    if (return_val < 0){
        errorlogger("Failed to destroy image sampler!");
        return ERROR_DESTROY_SAMPLER;
    }
    printf("Cleanup complete, exiting!\n\n");

    return 0;
}
