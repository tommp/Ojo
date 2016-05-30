#include "texture.h"


GLint init_texture(Texture* texture, HAL_image_sampler* sampler){
    glGenTextures(1, &texture->texture);
    glBindTexture(GL_TEXTURE_2D, texture->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sampler->buffer_width, sampler->buffer_height, 0, GL_RGB, GL_UNSIGNED_BYTE, &(sampler->buffer));
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLint error = check_ogl_error();
    if (error < 0){
        errorlogger("Failed to generate texture!");
        return ERROR_GENERATE_TEXTURE;
    }
    return 0;
}

GLint destroy_texture(Texture* texture){
    glDeleteTextures(1, &(texture->texture));

    GLint error = check_ogl_error();
    if (error < 0){
        errorlogger("Failed to destroy texture!");
        return ERROR_DESTROY_TEXTURE;
    }

    return 0;
}

GLint use_texture(Texture* texture, GLuint texture_unit, Shader* shader, Char* uniform_name){
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture->texture);
    glUniform1i(load_uniform_location(shader, uniform_name), texture_unit);

    GLint error = check_ogl_error();
    if (error < 0){
        errorlogger("Failed to use texture!");
        return ERROR_USE_TEXTURE;
    }

    return 0;
}


