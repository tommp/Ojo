#ifndef SHADER_H
#define SHADER_H

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

typedef struct Shader{
    GLuint program;

    GLint uniforms[MAX_UNIFORMS];
    char* uniform_names[MAX_UNIFORMS];


}Shader;

GLint use_shader(Shader* shader);
GLint load_uniform_location(Shader* shader, char* uniform_name);

#endif
