#ifndef UTILITY_H
#define UTILITY_H


#include "HAL_DEFINES.h"

#include "errorlogger.h"

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>

const char* gl_error_string(GLenum err);
GLint check_ogl_error();
GLint xioctl(int fd, int request, void *arg);
char* concat(char *s1, char *s2);

#endif
