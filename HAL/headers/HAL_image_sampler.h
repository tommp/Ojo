#ifndef HAL_IMAGE_SAMPLER_H
#define HAL_IMAGE_SAMPLER_H

#if IMAGE_SAMPLER == RBP_CSI
#include "bcm_host.h"
#include "ilclient.h"
#endif

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

EGLint sample_grayscale_image(char* img, EGLint* width, EGLint* height);

#endif
