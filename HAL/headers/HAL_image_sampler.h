#ifndef HAL_IMAGE_SAMPLER_H
#define HAL_IMAGE_SAMPLER_H

#if IMAGE_SAMPLER == RBP_CSI
#include "bcm_host.h"
#include "ilclient.h"

#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#endif

#include "utility.h"
#include "CONFIG.h"

#include "GLES2/gl2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct HAL_image_sampler{
    GLint driver_file_descriptor;
    unsigned char* buffer;

#if USE_INTEGRAL_IMAGE
    uint32_t* ibuffer;
#endif
    GLint buffer_width;
    GLint buffer_height;

    GLuint current_sample;
}HAL_image_sampler;

GLint init_image_sampler(HAL_image_sampler* sampler);
GLint destroy_image_sampler(HAL_image_sampler* sampler);
GLint init_mmap(HAL_image_sampler* sampler);
GLint sample_image(HAL_image_sampler* sampler);
GLint query_capabilities(HAL_image_sampler* sampler);
GLint configure_settings(HAL_image_sampler* sampler);

#if USE_INTEGRAL_IMAGE
GLint sample_grayscale_image(HAL_image_sampler* sampler);
GLint sample_integral_image(HAL_image_sampler* sampler);
GLint convert_sample_to_grayscale(HAL_image_sampler* sampler);
GLint convert_sample_to_integral_image(HAL_image_sampler* sampler);
#endif

#endif
