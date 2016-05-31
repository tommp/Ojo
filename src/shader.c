#include "shader.h"

GLint init_shader(Shader* shader){
    GLint result;

    result = init_uniforms(shader);
    if (result < 0){
        errorlogger("Failed to initialize uniforms!");
        return ERROR_UNIFORM_INIT;
    }

    return 0;
}

GLint init_uniforms(Shader* shader){
    GLuint i;
    for (i = 0; i < MAX_UNIFORMS; ++i){
        shader->uniforms[i] = -1;
    }

    //Sample texture uniform
    char name[] = "sampler_texture";
    shader->uniform_names[SAMPLE_TEXTURE] = (char*)malloc(sizeof(name));
    strcpy(shader->uniform_names[SAMPLE_TEXTURE], name);

    return 0;
}

GLint create_shader(const char* filename, GLenum type){
    char* source = read_data_from_file(filename);
    if (source == NULL) {
        errorlogger("Could not open shader source file!");
        return ERROR_LOAD_SHADER_FILE;
    }

    GLuint res = glCreateShader(type);
    const GLchar* sources[] = {OPENGL_VERSION, source};
    glShaderSource(res, 2, sources, NULL);

    free((void*)source);

    GLint compile_ok = GL_FALSE;
    glCompileShader(res);

    glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE) {
        print_log(res);
        glDeleteShader(res);
        return 0;
    }

    return res;
}

GLint load_shader_from_file(Shader* shader, char* vertex_shader_name, char* fragment_shader_name){
    char* vertex_shader_path = concat(VERTEX_SHADER_PATH, vertex_shader_name);
    char* fragment_shader_path = concat(FRAGMENT_SHADER_PATH, fragment_shader_name);

    /* create the shaders */
    GLuint vertex_shader = create_shader(vertex_shader_path, GL_VERTEX_SHADER);
    if(vertex_shader == 0) {
        errorlogger("Failed to create vertex shader!");
        return ERROR_VERTEX_SHADER_CREATE;
    }

    GLuint fragment_shader = create_shader(fragment_shader_path, GL_FRAGMENT_SHADER);
    if(fragment_shader == 0) {
        errorlogger("Failed to create fragment_shader!");
        return ERROR_FRAGMENT_SHADER_CREATE;
    }

    free(vertex_shader_path);
    free(fragment_shader_path);

    /* Create program */
    shader->program = glCreateProgram();

    /* Attach the shaders */
    glAttachShader(shader->program, vertex_shader);
    glAttachShader(shader->program, fragment_shader);

    /* Link the program */
    GLint success;
    glLinkProgram(shader->program);
    glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
    if(!success){
        print_log(shader->program);
        return ERROR_SHADER_LINK;
    }

    /* Delete the linked shaders */
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    if(check_ogl_error()){
        errorlogger("Failed to delete bound shaders!");
        return ERROR_DELETE_SHADER;
    }

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

GLint print_log(GLuint object){
    GLint log_length = 0;
    if (glIsShader(object)) {
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
    } else if (glIsProgram(object)) {
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
    } else {
        errorlogger("Argument to print_log(GLuint object), not a shader or a program!");
        return ERROR_SHADER_LOG;
    }

    char* logger= (char*)malloc(log_length);

    if (glIsShader(object)){
        glGetShaderInfoLog(object, log_length, NULL, logger);
    }
    else if (glIsProgram(object)){
        glGetProgramInfoLog(object, log_length, NULL, logger);
    }

    errorlogger("Shader compilation failed!");
    printf("Shader error: %s\n\n", logger);
    free(logger);

    return 0;
}
