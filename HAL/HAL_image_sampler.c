#include "HAL_image_sampler.h"


GLint init_image_sampler(HAL_image_sampler* sampler){
    GLint result;

    sampler->driver_file_descriptor = open("/dev/video0", O_RDWR);
    if (sampler->driver_file_descriptor == -1){
        errorlogger("Could not open video device!");
        return ERROR_OPENING_VIDEO_DEVICE;
    }

#if QUERY_CAPABILITIES
    query_capabilities(sampler);
#endif

    result = configure_settings(sampler);
    if (result < 0){
        errorlogger("Failed to configure initial settings!");
        return ERROR_CONFIGURE_SETTINGS;
    }

    result = init_mmap(sampler);
    if (result < 0){
        errorlogger("Failed to initialize memory map to image buffer!");
        return ERROR_MEMORY_MAP;
    }

    sampler->current_sample = 0;

    printf("Sampling initial test image...\n\n");
    result = capture_image(sampler);
    if (result < 0){
        errorlogger("Failed to sample test image!");
        return ERROR_MEMORY_MAP;
    }
    printf("Sampling successful!\n\n");

    return 0;
}

GLint destroy_image_sampler(HAL_image_sampler* sampler){
    GLint result = close(sampler->driver_file_descriptor);
    if (result < 0){
        errorlogger("Failed to close driver descriptor!");
        return ERROR_DESTROY_SAMPLER;
    }
    return 0;
}

EGLint sample_grayscale_image(HAL_image_sampler* sampler){

    return 0;
}

GLint capture_image(HAL_image_sampler* sampler){
    struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if(xioctl(sampler->driver_file_descriptor, VIDIOC_QBUF, &buf) == -1){
        errorlogger("Failed to query buffer!");
        return ERROR_VIDEO_DRIVER_QUERY;
    }

    if(xioctl(sampler->driver_file_descriptor, VIDIOC_STREAMON, &buf.type) == -1){
        errorlogger("Failed to capture image!");
        return ERROR_VIDEO_DRIVER_CAPTURE;
    }

    //For some reason this bugs out
   /* fd_set fds;
    FD_ZERO(&fds);
    FD_SET(sampler->driver_file_descriptor, &fds);
    struct timeval tv = {0};
    tv.tv_sec = SELECT_TIMEOUT_TIME;
    GLint result = select(sampler->driver_file_descriptor+1, &fds, NULL, NULL, &tv);
    if(result == -1){
        errorlogger("No frame availiable...");
        return ERROR_VIDEO_DRIVER_REQUEST;
    }*/

    if(xioctl(sampler->driver_file_descriptor, VIDIOC_DQBUF, &buf) == -1){
        errorlogger("Currently retrieving frame!");
        return ERROR_CURRENTLY_RETIRIEVING_FRAME;
    }

#if STORE_SAMPLE_IMAGE
    char filenumber[4];
    sprintf(filenumber, "%d", sampler->current_sample);
    char* concat_1 = concat(IMAGE_SAMPLE_FOLDER, filenumber);
    char* final_name = concat(concat_1, IMAGE_SAMPLE_NAME);
    GLint outfd = open(final_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (outfd == -1){
        errorlogger("Failed to open image sample file!");
        printf("Filename: %s\n", final_name);
        free(concat_1);
        free(final_name);
        return ERROR_SAMPLE_IMAGE_OPENING;
    }
    write(outfd, sampler->buffer, buf.bytesused);
    close(outfd);

    free(concat_1);
    free(final_name);

    ++sampler->current_sample;
    if(sampler->current_sample > MAX_NUM_SAMPLES){
        sampler->current_sample = 0;
    }
#endif

    return 0;
}

GLint init_mmap(HAL_image_sampler* sampler){
    struct v4l2_requestbuffers req = {0};
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (xioctl(sampler->driver_file_descriptor, VIDIOC_REQBUFS, &req) == -1){
        errorlogger("Requesting Buffer");
        return ERROR_VIDEO_DRIVER_REQUEST;
    }

    struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;

    if(xioctl(sampler->driver_file_descriptor, VIDIOC_QUERYBUF, &buf) == -1){
        errorlogger("Failed to query buffer!");
        return ERROR_VIDEO_DRIVER_QUERY;
    }

    sampler->buffer= mmap (NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, sampler->driver_file_descriptor, buf.m.offset);
    printf("Sample buffer size: %d bytes\nAddress: %p\n", buf.length, sampler->buffer);
    printf("Buffer memory used: %d bytes ( %f %%)\n", buf.bytesused, ( (float)buf.bytesused / (float)buf.length ) * 100.0);

    return 0;
}

GLint query_capabilities(HAL_image_sampler* sampler){
    struct v4l2_capability caps = {};
    if (xioctl(sampler->driver_file_descriptor, VIDIOC_QUERYCAP, &caps) == -1){
        errorlogger("Failed to query capabilities!");
        return ERROR_VIDEO_DRIVER_QUERY;
    }

    printf( "Driver Caps:\n"
            "  Driver: \"%s\"\n"
            "  Card: \"%s\"\n"
            "  Bus: \"%s\"\n"
            "  Version: %d.%d\n"
            "  Capabilities: %08x\n\n",
            caps.driver,
            caps.card,
            caps.bus_info,
            (caps.version>>16)&&0xff,
            (caps.version>>24)&&0xff,
            caps.capabilities);


    struct v4l2_cropcap cropcap = {0};
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (xioctl(sampler->driver_file_descriptor, VIDIOC_CROPCAP, &cropcap) == -1){
        errorlogger("Failed to query cropping capabilities");
        //return ERROR_VIDEO_DRIVER_QUERY;
    }

    printf( "Camera Cropping:\n"
            "  Bounds: %dx%d+%d+%d\n"
            "  Default: %dx%d+%d+%d\n"
            "  Aspect: %d/%d\n\n",
            cropcap.bounds.width, cropcap.bounds.height, cropcap.bounds.left, cropcap.bounds.top,
            cropcap.defrect.width, cropcap.defrect.height, cropcap.defrect.left, cropcap.defrect.top,
            cropcap.pixelaspect.numerator, cropcap.pixelaspect.denominator);
    return 0;
}

GLint configure_settings(HAL_image_sampler* sampler){
        int support_grbg10 = 0;

        struct v4l2_fmtdesc fmtdesc = {0};
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        char fourcc[5] = {0};
        char c, e;
        printf("  FMT : CE Desc\n--------------------\n");
        while (xioctl(sampler->driver_file_descriptor, VIDIOC_ENUM_FMT, &fmtdesc) == 0){
                strncpy(fourcc, (char *)&fmtdesc.pixelformat, 4);
                if (fmtdesc.pixelformat == V4L2_PIX_FMT_SGRBG10)
                    support_grbg10 = 1;
                c = fmtdesc.flags & 1? 'C' : ' ';
                e = fmtdesc.flags & 2? 'E' : ' ';
                printf("  %s: %c%c %s\n\n", fourcc, c, e, fmtdesc.description);
                fmtdesc.index++;
        }

        if (!support_grbg10){
            printf("Doesn't support GRBG10.\n\n");
            //return 1;
        }

        struct v4l2_format fmt = {0};
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width = SAMPLE_WIDTH;
        fmt.fmt.pix.height = SAMPLE_HEIGHT;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
        fmt.fmt.pix.field = V4L2_FIELD_NONE;

        if (xioctl(sampler->driver_file_descriptor, VIDIOC_S_FMT, &fmt) == -1){
            errorlogger("Failed to set pixel format!");
            //return ERROR_VIDEO_DRIVER_QUERY;
        }

        strncpy(fourcc, (char *)&fmt.fmt.pix.pixelformat, 4);
        printf( "Selected Camera Mode:\n"
                "  Width: %d\n"
                "  Height: %d\n"
                "  PixFmt: %s\n"
                "  Field: %d\n\n",
                fmt.fmt.pix.width,
                fmt.fmt.pix.height,
                fourcc,
                fmt.fmt.pix.field);

        sampler->buffer_width = fmt.fmt.pix.width;
        sampler->buffer_height = fmt.fmt.pix.height;

        printf("Final sampler resolution set to: %dx%d\n\n", sampler->buffer_width, sampler->buffer_height);

        return 0;
}

