#ifndef GPU_SAMPLE_PROCESSORS_H
#define GPU_SAMPLE_PROCESSORS_H

#include "CONFIG.h"
#include "renderer.h"

#include <GLES2/gl2.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct GPU_data{
    char* keypoint_image;
    char* gradient_image;
}GPU_data;

GLint init_gpu_data(GPU_data* data){
    data->keypoint_image = malloc(sizeof(char) * 4 * SAMPLE_WIDTH * SAMPLE_HEIGHT);
    data->gradient_image = malloc(sizeof(char) * 4 * SAMPLE_WIDTH * SAMPLE_HEIGHT);
    return 0;
}

GLint destroy_gpu_data(GPU_data* data){
    free(data->keypoint_image);
    free(data->gradient_image);
    return 0;
}

GLint sample_gpu_data(GPU_data* data, Renderer* renderer, GLuint keypoint_buffer_index, GLuint  gradient_buffer_index){

    return 0;
}

#endif
