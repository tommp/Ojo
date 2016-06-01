#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include "CONFIG.h"

#include "GLES2/gl2.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Input_controller{
    pthread_mutex_t state_mutex;
    pthread_t controller_thread;
    GLchar state;
}Input_controller;

GLint init_controller(Input_controller* controller);
GLint destroy_controller(Input_controller* controller);
void* handle_input(void* controller);
GLint update_state(Input_controller* controller, char new_val);
GLint read_state(Input_controller* controller, GLchar* read_val);

#endif
