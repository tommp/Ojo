#include "HAL_image_sampler.h"


GLint init_image_sampler(HAL_image_sampler* sampler){
    GLint result;

    sampler->driver_file_descriptor = open("/dev/video0", O_RDWR);
    if (sampler->driver_file_descriptor == -1){
        errorlogger("Could not open video device!");
        return ERROR_OPENING_VIDEO_DEVICE;
    }

    result = init_mmap(sampler);
    if (result < 0){
        errorlogger("Failed to initialize memory map to image buffer!");
        return ERROR_MEMORY_MAP;
    }

    return 0;
}

GLint destroy_image_sampler(HAL_image_sampler* sampler){
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

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(sampler->driver_file_descriptor, &fds);
    struct timeval tv = {0};
    tv.tv_sec = 2;
    GLint result = select(sampler->driver_file_descriptor+1, &fds, NULL, NULL, &tv);
    if(result == -1){
        errorlogger("No frame availiable, waiting...");
        return ERROR_VIDEO_DRIVER_CAPTURE;
    }

    if(xioctl(sampler->driver_file_descriptor, VIDIOC_DQBUF, &buf) == -1){
        errorlogger("Currently retrieving frame!");
        return ERROR_CURRENTLY_RETIRIEVING_FRAME;
    }

    int outfd = open("out.img", O_RDWR);
    write(outfd, sampler->buffer, buf.bytesused);
    close(outfd);

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
    printf("Length: %d\nAddress: %p\n", buf.length, sampler->buffer);
    printf("Image Length: %d\n", buf.bytesused);

    return 0;
}
