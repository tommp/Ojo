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

    Shader test_shader;
    return_val = init_shader(&test_shader, BASE_VS, TEST_FS);
    if (return_val < 0){
        errorlogger("Failed to initialize blur shader!");
        return ERROR_INIT_SHADER;
    }

    Texture sample_texture;
    return_val = init_texture(&sample_texture, &sampler);
    if (return_val < 0){
        errorlogger("Failed to initialize sample texture!");
        return ERROR_INIT_TEXTURE;
    }

    //Main Loop
    /* ================================================ */
    printf("Main loop running!\n\n");
    use_shader(&test_shader);
    use_texture(&sample_texture, 0, &test_shader, 0);
    int i;
    for(i = 0; i < 40; ++i){
        capture_image(&sampler);
        update_texture(&sample_texture, &sampler);
        render_quad(&renderer);
    }

    printf("Exiting main loop!\n\n");
    /* ================================================ */

    wait_for_keypress();

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
