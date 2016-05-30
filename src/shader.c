#include "shader.h"

GLint init_shader(Shader* shader){
return 0;
}

GLint use_shader(Shader* shader){
    glUseProgram(shader->program);
    GLint error = check_ogl_error();
    if (error < 0){
        errorlogger("Failed to use shader!");
        return ERROR_USE_SHADER;
    }
    return 0;
}

GLint load_uniform_location(Shader* shader, GLuint uniform_index){
    GLint result = shader->uniforms[uniform_index];
    if (result == -1){
        result = glGetUniformLocation(shader->program, shader->uniform_names[uniform_index]);
        shader->uniforms[uniform_index] = result;
    }

    return result;
}

GLint init_uniforms(Shader* shader){
    return 0;
}
