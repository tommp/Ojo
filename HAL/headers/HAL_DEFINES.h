#ifndef HAL_DEFINES_H
#define HAL_DEFINES_H

//Window systems
#define DISPMANX 1001

//Image samplers
#define RBP_CSI 2001


//General vars
#define CLEARCOLOR                          0.0, 0.0, 0.0, 1.0

#define ERROR_INIT_RENDERER                 -1

#define ERROR_GET_DISPLAY                   -101
#define ERROR_INIT_DISPLAY                  -102
#define ERROR_CHOOSE_CONFIG                 -103
#define ERROR_INIT_WINDOW                   -104
#define ERROR_CREATE_CONTEXT                -105
#define ERROR_CREATE_WINDOW_SURFACE         -106
#define ERROR_MAKE_CURRENT                  -107
#define ERROR_MACRO_INIT                    -108
#define ERROR_WINDOW_SYSTEM_INIT            -109
#define ERROR_IMAGE_SAMPLER_INIT            -110
#define ERROR_INIT_CONTEXT                  -111
#define ERROR_INIT_SURFACE                  -112
#define ERROR_DESTROY_RENDERER              -113
#define ERROR_VIDEO_DRIVER                  -114
#define ERROR_VIDEO_DRIVER_CAPTURE          -115
#define ERROR_VIDEO_DRIVER_QUERY            -116
#define ERROR_VIDEO_DRIVER_REQUEST          -117
#define ERROR_OPENING_VIDEO_DEVICE          -118
#define ERROR_CURRENTLY_RETIRIEVING_FRAME   -119
#define ERROR_MEMORY_MAP                    -120
#define ERROR_DESTROY_SAMPLER               -121
#define ERROR_INIT_SAMPLER                  -122
#define ERROR_SAMPLE_IMAGE_OPENING          -123
#define ERROR_SAMPLE_IMAGE                  -124
#define ERROR_CONFIGURE_SETTINGS            -125
#define ERROR_USE_SHADER                    -126
#define ERROR_GENERATE_TEXTURE              -127
#define ERROR_DESTROY_TEXTURE               -128
#define ERROR_USE_TEXTURE                   -129
#define ERROR_UNIFORM_INIT                  -130
#define ERROR_SHADER_LOG                    -131
#define ERROR_LOAD_SHADER_FILE              -132

#define NUM_FRAMEBUFFERS                    2

//Shader uniforms
#define SAMPLE_TEXTURE                      0

//Shader programs
#define BASE_VERTEX_SHADER                  "quad.vs"
#define BLUR_FRAG_SHADER                    "blur.fs"

#endif
