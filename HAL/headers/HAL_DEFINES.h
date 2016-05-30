#ifndef HAL_DEFINES_H
#define HAL_DEFINES_H

//Window systems
#define DISPMANX 1001

//Image samplers
#define RBP_CSI 2001


//General vars
#define CLEARCOLOR 							0.0, 0.0, 0.0, 1.0

#define ERROR_INIT_RENDERER					-1

#define ERROR_GET_DISPLAY  					-101
#define ERROR_INIT_DISPLAY  				-102
#define ERROR_CHOOSE_CONFIG 				-103
#define ERROR_INIT_WINDOW 					-104
#define ERROR_CREATE_CONTEXT 				-105
#define ERROR_CREATE_WINDOW_SURFACE		 	-106
#define ERROR_MAKE_CURRENT					-107
#define ERROR_MACRO_INIT                    -108
#define ERROR_WINDOW_SYSTEM_INIT            -109
#define ERROR_IMAGE_SAMPLER_INIT            -110

#endif
