#include "input_controller.h"

GLint init_controller(Input_controller* controller){
    pthread_mutex_init(&controller->state_mutex, NULL);
    update_state(controller, INPUT_DISPLAY_RAW);
    pthread_create(&controller->controller_thread, NULL, handle_input, (void*)controller);

    printf("Input controller commands:\n        Quit application: %c\n        Display gradients: %c\n        Display raw samples: %c\n\n",
           INPUT_QUITTING,
           INPUT_DISPLAY_HARRIS,
           INPUT_DISPLAY_RAW);

    return 0;
}

GLint destroy_controller(Input_controller* controller){
    pthread_mutex_destroy(&controller->state_mutex);

    return 0;
}


GLint update_state(Input_controller* controller, char new_val){
    pthread_mutex_lock(&controller->state_mutex);
    controller->state = new_val;
    pthread_mutex_unlock(&controller->state_mutex);

    return 0;
}

GLint read_state(Input_controller* controller, GLchar* read_val){
    pthread_mutex_lock(&controller->state_mutex);
    *read_val = controller->state;
    pthread_mutex_unlock(&controller->state_mutex);

    return 0;
}

void* handle_input(void* controller){
    Input_controller* target = (Input_controller*)controller;
    GLchar input;
    read_state(target, &input);
    while(input != INPUT_QUITTING){
        GLchar input = getchar();
        if (input != '\n'){
            update_state(target, input);
            printf("Read input, new state: %c\n\n", input);
        }
    }

    update_state(target, INPUT_QUITTING);
    pthread_exit((void*)0);
}

