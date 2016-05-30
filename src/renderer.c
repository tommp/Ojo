#include "renderer.h"

EGLint init_renderer(Renderer* renderer){
        EGLint return_val = 0;

        return_val = init_display(renderer);
        if (return_val < 0){
            errorlogger("Failed to initialize system display!");
            return ERROR_INIT_DISPLAY;
        }

        return_val = init_context(renderer);
        if (return_val < 0){
            errorlogger("Failed to initialize system context!");
            return ERROR_INIT_CONTEXT;
        }

        /* Platform specific */
        return_val = init_window(&renderer->window);
        if (return_val < 0){
            errorlogger("Failed to initialize system window!");
            return ERROR_INIT_WINDOW;
        }
        /* ================= */

        return_val = init_surface(renderer);
        if (return_val < 0){
            errorlogger("Failed to initialize system surface!");
            return ERROR_INIT_SURFACE;
        }

        init_ogl();

	return 0;
}

EGLint destroy_renderer(Renderer* renderer){
    free(renderer->framebuffers);
    return 0;
}

EGLint init_display(Renderer* renderer){
    EGLBoolean result;
    renderer->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (renderer->display == EGL_NO_DISPLAY){
        errorlogger("Failed to get EGL display!");
        return ERROR_GET_DISPLAY;
    }

    result = eglInitialize(renderer->display, NULL, NULL);
    if (result == EGL_FALSE){
        errorlogger("Failed to initialize EGL display!");
        return ERROR_INIT_DISPLAY;
    }

    return 0;
}

EGLint init_context(Renderer* renderer){
    EGLBoolean result;
    static const EGLint attribute_list[] ={
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_NONE
    };

    // get an appropriate EGL frame buffer configuration
    // this uses a BRCM extension that gets the closest match, rather than standard which returns anything that matches
    result = eglSaneChooseConfigBRCM(renderer->display, attribute_list, &renderer->config, 1, &renderer->num_config);

    //result = eglChooseConfig(renderer->display, attribute_list, renderer->config, 1, &renderer->num_config);
    if (result == EGL_FALSE){
        errorlogger("Failed to choose EGL config!");
        return ERROR_CHOOSE_CONFIG;
    }


    renderer->context = eglCreateContext(renderer->display, renderer->config, EGL_NO_CONTEXT, NULL);
    if (renderer->context == EGL_NO_CONTEXT){
        errorlogger("Failed to create EGL context!");
        return ERROR_CREATE_CONTEXT;
    }

    return 0;
}

EGLint init_surface(Renderer* renderer){
    EGLBoolean result;
    renderer->surface = eglCreateWindowSurface(renderer->display, renderer->config, renderer->window.native_window, NULL );
    if (renderer->surface == EGL_NO_SURFACE){
        errorlogger("Failed to create EGL surface!");
        return ERROR_CREATE_WINDOW_SURFACE;
    }

    result = eglMakeCurrent(renderer->display, renderer->surface, renderer->surface, renderer->context);
    if (result == EGL_FALSE){
        errorlogger("Failed to bind EGL context to rendering surface!");
        return ERROR_MAKE_CURRENT;
    }

    return 0;
}

GLint init_ogl(){
    glClearColor(CLEARCOLOR);
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    check_ogl_error();
    return 0;
}

GLint init_framebuffers(Renderer* renderer){
    renderer->framebuffers = malloc(sizeof(GLuint) * NUM_FRAMEBUFFERS);
    glGenFramebuffers(2, renderer->framebuffers);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return 0;
}
