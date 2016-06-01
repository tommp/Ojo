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

    printf("Initializing shaders...\n\n");
    Shader raw_shader;
    return_val = init_shader(&raw_shader, BASE_VS, RAW_FS);
    if (return_val < 0){
        errorlogger("Failed to initialize raw shader!");
        return ERROR_INIT_SHADER;
    }
    printf("Shaders initialized!\n\n");

    Shader hg_shader;
    return_val = init_shader(&hg_shader, BASE_VS, HARRIS_GRADIENT);
    if (return_val < 0){
        errorlogger("Failed to initialize vertical harris gradient shader!");
        return ERROR_INIT_SHADER;
    }

    Shader* current_shader = &raw_shader;

    Texture sample_texture;
    return_val = init_texture(&sample_texture, &sampler);
    if (return_val < 0){
        errorlogger("Failed to initialize sample texture!");
        return ERROR_INIT_TEXTURE;
    }

    printf("Initializing input controller...\n\n");
    Input_controller controller;
    return_val = init_controller(&controller);
    if (return_val < 0){
        errorlogger("Failed to initialize input controller!");
        return ERROR_INIT_CONTROLLER;
    }
    printf("Input controller initialized!\n\n");

    printf("Initializing timers...\n\n");
    Timer looptimer;
    unsigned long sample_time;
    unsigned long rendering_time;
    printf("Timers initialized!\n\n");

    //Main Loop
    /* ================================================ */
    printf("Main loop running!\n\n");

    GLchar state = INPUT_DISPLAY_RAW;
    while(state != INPUT_QUITTING){
        read_state(&controller, &state);
        switch(state){
            case INPUT_DISPLAY_RAW:{
                current_shader = &raw_shader;
                use_shader(current_shader);
                use_texture(&sample_texture, 0, current_shader, 0);
                break;
            }
            case INPUT_DISPLAY_HARRIS:{
                current_shader = &hg_shader;
                use_shader(current_shader);
                upload_buffer_size(&renderer, current_shader);
                use_texture(&sample_texture, 0, current_shader, 0);
                break;
            }
            default:{
                continue;
            }
        }

        restart_timer(&looptimer);
        capture_image(&sampler);
        sample_time = return_timediff(&looptimer);
        restart_timer(&looptimer);

        update_texture(&sample_texture, &sampler);
        render_quad(&renderer);
        rendering_time = return_timediff(&looptimer);

        printf("Image sampled in: %.3ld ms, Rendered in: %.3ld ms, Total loop time: %.3ld ms  \r", sample_time, rendering_time, sample_time + rendering_time);
    }

    printf("Exiting main loop!\n\n");
    /* ================================================ */

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

    return_val = destroy_controller(&controller);
    if (return_val < 0){
        errorlogger("Failed to destroy input controller!");
        return ERROR_DESTROY_SAMPLER;
    }
    printf("Cleanup complete, exiting!\n\n");

    return 0;
}
