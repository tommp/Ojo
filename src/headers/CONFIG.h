#ifndef CONFIG_H
#define CONFIG_H

#include "HAL_DEFINES.h"

//Configure these for the current platform
#define IMAGE_SAMPLER           RBP_CSI
#define WINDOW_SYSTEM           DISPMANX
#define STORE_SAMPLE_IMAGE      1
#define MAX_NUM_SAMPLES         50
#define TV_TIME                 2
#define CONFIGURE_SETTINGS      0
#define MAX_UNIFORMS            10

#define OPENGL_VERSION          "#version 100"

#define FOLDER_PATH             "/home/pi/Ojo/"
#define VERTEX_SHADER_PATH      "/home/pi/Ojo/src/shaders/vertex/"
#define FRAGMENT_SHADER_PATH    "/home/pi/Ojo/src/shaders/fragment/"
#define IMAGE_SAMPLE_FOLDER     "samples/"
#define IMAGE_SAMPLE_NAME       "sample.jpeg"
#define ERROR_FILE_NAME         "errorlog.txt"

#endif
