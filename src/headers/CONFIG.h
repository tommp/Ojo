#ifndef CONFIG_H
#define CONFIG_H

#include "HAL_DEFINES.h"

//Configure these for the current platform
#define IMAGE_SAMPLER               RBP_CSI
#define WINDOW_SYSTEM               DISPMANX
#define STORE_SAMPLE_IMAGE          0
#define MAX_NUM_SAMPLES             50
#define SELECT_TIMEOUT_TIME         7000
#define QUERY_CAPABILITIES          1
#define MAX_UNIFORMS                10
#define WINDOW_SCALE                2
#define USE_INTEGRAL_IMAGE          0
#define DESCRIPTOR_MATCH_THRESHOLD  10.0

#define SAMPLE_WIDTH                720
#define SAMPLE_HEIGHT               512

#define OPENGL_VERSION              "#version 100\n"
#define PRINT_EGL_CONFIGS           0

#define FOLDER_PATH                 "/home/pi/Ojo/"
#define VERTEX_SHADER_PATH          "/home/pi/Ojo/src/shaders/vertex/"
#define FRAGMENT_SHADER_PATH        "/home/pi/Ojo/src/shaders/fragment/"
#define IMAGE_SAMPLE_FOLDER         "samples/"
#define IMAGE_SAMPLE_NAME           "sample.jpeg"
#define ERROR_FILE_NAME             "errorlog.txt"

#define INPUT_QUITTING          'q'
#define INPUT_FREEZE            'w'
#define INPUT_RUNNING           'e'
#define INPUT_DISPLAY_RAW       'a'
#define INPUT_DISPLAY_HARRIS    's'
#define INPUT_DISPLAY_FEATURES  'd'

#define RENDERER_RED_SIZE       8
#define RENDERER_GREEN_SIZE     8
#define RENDERER_BLUE_SIZE      8
#define RENDERER_ALPHA_SIZE     8


#endif
