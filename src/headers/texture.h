#ifndef TEXTURE_H
#define TEXTURE_H

#include "CONFIG.h"
#include "HAL_image_sampler.h"
#include "utility.h"
#include "shader.h"

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

typedef struct Texture{
    GLuint texture;
    GLuint width;
    GLuint height;
}Texture;

GLint init_texture(Texture* texture, HAL_image_sampler* sampler);
GLint destroy_texture(Texture* texture);
GLint use_texture(Texture* texture, GLuint texture_unit, Shader* shader, GLuint uniform_index);
GLint update_texture(Texture* texture, HAL_image_sampler* sampler);

#endif
