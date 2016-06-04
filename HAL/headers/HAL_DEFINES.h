#ifndef HAL_DEFINES_H
#define HAL_DEFINES_H

//Window systems
#define DISPMANX 1001

//Image samplers
#define RBP_CSI 2001


//General vars
#define CLEARCOLOR                          1.0, 0.0, 0.0, 1.0

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
#define ERROR_FRAGMENT_SHADER_CREATE        -133
#define ERROR_VERTEX_SHADER_CREATE          -134
#define ERROR_DELETE_SHADER                 -135
#define ERROR_SHADER_LINK                   -136
#define ERROR_INIT_SHADER                   -137
#define ERROR_SHADER_COMPILE                -138
#define ERROR_SHADER_CREATION               -139
#define ERROR_BIND_API                      -140
#define ERROR_INIT_QUAD                     -141
#define ERROR_DRAW_QUAD                     -142
#define ERROR_INIT_TEXTURE                  -143
#define ERROR_INIT_CONTROLLER               -144
#define ERROR_UPLOAD_SCREEN_SIZE            -145
#define ERROR_INIT_FRAMEBUFFERS             -146

#define NUM_FRAMEBUFFERS                    3

//Shader uniforms
#define SAMPLE_TEXTURE                      0
#define SAMPLE_TEXTURE_2                    1
#define INV_BUFFER_SIZE                     2

//Shader programs
#define BASE_VS                            "quad.vs"

#define RAW_FS                             "raw.fs"
#define VERTICAL_BLUR_FS                   "vertical_blur.fs"
#define HORIZONTAL_BLUR_FS                 "horizontal_blur.fs"
#define CALC_GRADIENT                      "calc_gradient.fs"
#define GRAYSCALE_CONVERTER                "grayscale_converter.fs"
#define FEATURE_DETECTOR                   "feature_detector.fs"
#define FEATURE_FILTER                     "feature_filter.fs"
#define CALC_MEDIAN                        "calc_median.fs"
#define CALC_VARIANCE                      "calc_variance.fs"
#define CALC_VERTICAL_BLUR                 "calc_vertical_blur.fs"
#define CALC_HORIZONTAL_BLUR               "calc_horizontal_blur.fs"
#define CALC_SECOND_GRADIENT               "calc_second_gradient.fs"

#endif
