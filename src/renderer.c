#include "renderer.h"

EGLint init_renderer(Renderer* renderer){
        EGLint return_val = 0;

        return_val = init_display(renderer);
        if (return_val < 0){
            errorlogger("Failed to initialize system display!");
            return ERROR_INIT_DISPLAY;
        }

        return_val = bind_api();
        if (return_val < 0){
            errorlogger("Failed to bind API!");
            return ERROR_BIND_API;
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

        renderer->buffer_width = renderer->window.window_width;
        renderer->buffer_height = renderer->window.window_height;

        return_val = init_surface(renderer);
        if (return_val < 0){
            errorlogger("Failed to initialize system surface!");
            return ERROR_INIT_SURFACE;
        }

        return_val = init_framebuffers(renderer);
        if (return_val < 0){
            errorlogger("Failed to initialize framebuffers!");
            return ERROR_INIT_SURFACE;
        }

        init_ogl(renderer);

        return_val = init_quad(renderer);
        if(return_val < 0){
            errorlogger("Failed to initialize quad!");
            return ERROR_INIT_QUAD;
        }

	return 0;
}

EGLint destroy_renderer(Renderer* renderer){
    free(renderer->framebuffers);
    free(renderer->configs);
    return 0;
}

EGLint init_display(Renderer* renderer){
    EGLBoolean result;
    renderer->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (renderer->display == EGL_NO_DISPLAY){
        errorlogger("Failed to get EGL display!");
        return ERROR_GET_DISPLAY;
    }

    EGLint major;
    EGLint minor;
    result = eglInitialize(renderer->display, &major, &minor);
    if (result == EGL_FALSE){
        errorlogger("Failed to initialize EGL display!");
        return ERROR_INIT_DISPLAY;
    }
    printf("EGL initialized with major version: %d and minor version: %d\n\n", major, minor);


    result = eglGetConfigs(renderer->display, NULL, 0, &renderer->num_configs);
    if (result == EGL_FALSE){
        errorlogger("Failed to get EGL configs!");
        return ERROR_INIT_DISPLAY;
    }
    printf("Number of configs found: %d \n\n", renderer->num_configs);

    renderer->configs = (EGLConfig*)malloc(sizeof(EGLConfig) * renderer->num_configs);

    result = eglGetConfigs(renderer->display, renderer->configs, renderer->num_configs, &renderer->num_configs);
    result = eglGetConfigs(renderer->display, NULL, 0, &renderer->num_configs);
    if (result == EGL_FALSE){
        errorlogger("Failed to get EGL configs!");
        return ERROR_INIT_DISPLAY;
    }

#if PRINT_EGL_CONFIGS
    print_configs(renderer, renderer->num_configs);
#endif

    static const EGLint attribute_list[] ={
            EGL_RED_SIZE, RENDERER_RED_SIZE,
            EGL_GREEN_SIZE, RENDERER_GREEN_SIZE,
            EGL_BLUE_SIZE, RENDERER_BLUE_SIZE,
            EGL_ALPHA_SIZE, RENDERER_ALPHA_SIZE,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_NONE
    };

    // get an appropriate EGL frame buffer configuration
    // this uses a BRCM extension that gets the closest match, rather than standard which returns anything that matches
    result = eglSaneChooseConfigBRCM(renderer->display, attribute_list, &renderer->config, 1, &renderer->num_configs);

    //result = eglChooseConfig(renderer->display, attribute_list, renderer->config, 1, &renderer->num_config);
    if (result == EGL_FALSE){
        errorlogger("Failed to choose EGL config!");
        return ERROR_CHOOSE_CONFIG;
    }

    return 0;
}

EGLint bind_api(){
    EGLint result = eglBindAPI(EGL_OPENGL_ES_API);
    if (result == EGL_FALSE){
        errorlogger("Failed to bind OpenglES API!");
        return ERROR_BIND_API;
    }
    return 0;
}

EGLint init_context(Renderer* renderer){
    static const EGLint context_attributes[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    renderer->context = eglCreateContext(renderer->display, renderer->config, EGL_NO_CONTEXT, context_attributes);
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

GLint init_ogl(Renderer* renderer){
    glClearColor(CLEARCOLOR);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    eglSwapBuffers(renderer->display, renderer->surface);

    //glViewport(0, 0, (GLsizei)renderer->buffer_width, (GLsizei)renderer->buffer_height);
    glDisable(GL_CULL_FACE);
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

GLint init_quad(Renderer* renderer){
	GLfloat quad_vertices[] = {
		-1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f,
	};

	glGenBuffers(1, &(renderer->quad_VBO));
	glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_VBO);
	if(check_ogl_error()){
		errorlogger("Failed to bind quad VBO in renderer!");
		glDeleteBuffers(1, &(renderer->quad_VBO));
		return ERROR_INIT_QUAD;
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), &(quad_vertices[0]), GL_STATIC_DRAW);
	if(check_ogl_error()){
		errorlogger("Failed to buffer vertex data for quad VBO in renderer!");
		glDeleteBuffers(1, &(renderer->quad_VBO));
		return ERROR_INIT_QUAD;
	}


	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	if(check_ogl_error()){
		errorlogger("Failed to set vertex attributes for quad VBO in renderer!");
		glDeleteBuffers(1, &(renderer->quad_VBO));
		return ERROR_INIT_QUAD;
	}

	return 0;
}

GLint render_quad(Renderer* renderer){
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_VBO);
    glEnableVertexAttribArray(0);

    glFlush();

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    eglSwapBuffers(renderer->display, renderer->surface);

    if(check_ogl_error()){
        errorlogger("Failed to draw quad");
        return ERROR_DRAW_QUAD;
    }
    return 0;
}

GLint print_configs(Renderer* renderer, EGLint num_configs){
    EGLint value;
    EGLint i;
    for(i = 0; i<num_configs; ++i){
         printf("\n\n\n============================================");
         printf("Config number: %d\n", i);
         eglGetConfigAttrib(renderer->display, renderer->configs[i],EGL_BUFFER_SIZE, &value);
         printf("Buffer Size: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_RED_SIZE, &value);
         printf("Red Size: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_GREEN_SIZE, &value);
         printf("Green Size: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_BLUE_SIZE, &value);
         printf("Blue Size: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_ALPHA_SIZE, &value);
         printf("Alpha Size: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_CONFIG_CAVEAT, &value);
         switch(value){
              case  EGL_NONE :
                 printf("EGL_CONFIG_CAVEAT EGL_NONE\n");
                 break;
              case  EGL_SLOW_CONFIG :
                 printf("EGL_CONFIG_CAVEAT EGL_SLOW_CONFIG\n");
                 break;
         }
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_CONFIG_ID, &value);
         printf("Config ID: %d\n ", value);

         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_DEPTH_SIZE, &value);
         printf("Depth size: %d\n ", value);

         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_MAX_PBUFFER_WIDTH, &value);
         printf("Max pbuffer width: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_MAX_PBUFFER_HEIGHT, &value);
         printf("Max pbuffer height: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_MAX_PBUFFER_PIXELS, &value);
         printf("Max pbuffer pixels: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_NATIVE_RENDERABLE, &value);
         printf("Native renderable: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_NATIVE_VISUAL_ID, &value);
         printf("Native visual ID: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_NATIVE_VISUAL_TYPE, &value);
         printf("Native visual type: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_SAMPLE_BUFFERS, &value);
         printf("Sample Buffers: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_SAMPLES, &value);
         printf("Samples: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_SURFACE_TYPE, &value);
         printf("Surface type: %d\n ", value);
         eglGetConfigAttrib(renderer->display, renderer->configs[i], EGL_TRANSPARENT_TYPE, &value);
         printf("============================================\n\n\n");
    }
    return 0;
}

GLint upload_buffer_size(Renderer* renderer, Shader* shader){
    //glUniform1i(load_uniform_location(shader, INV_BUFFER_WIDTH), 1.0 / renderer->buffer_width);
    //glUniform1i(load_uniform_location(shader, INV_BUFFER_HEIGHT), 1.0 / renderer->buffer_height);

    glUniform2f(load_uniform_location(shader, INV_BUFFER_SIZE), 1.0 / renderer->buffer_width, 1.0 / renderer->buffer_height);
    GLint error = check_ogl_error();
    if (error < 0){
        errorlogger("Failed to upload screen size!");
        return ERROR_UPLOAD_SCREEN_SIZE;
    }
    return 0;
}
