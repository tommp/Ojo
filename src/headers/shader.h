#ifndef SHADER_H
#define SHADER_H

#include "CONFIG.h"
#include "HAL_DEFINES.h"
#include "errorlogger.h"
#include "utility.h"

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

#include <stdio.h>
#include <string.h>


typedef struct Shader{
    GLuint program;

    GLint uniforms[MAX_UNIFORMS];
    char* uniform_names[MAX_UNIFORMS];


}Shader;

GLint init_shader(Shader* shader, char* vertex_shader_name, char* fragment_shader_name);
GLint init_uniforms(Shader* shader);
GLuint create_shader(const char* filename, GLenum type);
GLint use_shader(Shader* shader);
GLint load_uniform_location(Shader* shader, GLuint uniform_index);
GLint print_log(GLuint object);
GLint load_shader_from_file(Shader* shader, char* vertex_shader, char* fragment_shader);


#endif
