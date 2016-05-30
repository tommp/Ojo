#include "utility.h"

const char* gl_error_string(GLenum err){
    switch(err) {
        case GL_INVALID_ENUM: return "Invalid Enum";
        case GL_INVALID_VALUE: return "Invalid Value";
        case GL_INVALID_OPERATION: return "Invalid Operation";
        case GL_OUT_OF_MEMORY: return "Out of Memory";
        default: return "Unknown Error";
    }
}

GLint check_ogl_error(){
    GLenum gl_error;
    GLint retCode = 0;

    gl_error = glGetError();

    while (gl_error != GL_NO_ERROR){
        errorlogger(gl_error_string(gl_error));
        printf("ERROR: glError: %s", gl_error_string(gl_error));
        gl_error = glGetError();
        retCode = -1;
    }

    return retCode;
}

GLint xioctl(int fd, int request, void *arg){
    int result;

    do {
        result = ioctl (fd, request, arg);
    } while (result == -1 && EINTR == errno);

    return result;
}
