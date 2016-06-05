#ifndef CPU_DESCRIPTORS_H
#define CPU_DESCRIPTORS_H

#include "gpu_sample_processors.h"

#include <#include "GLES2/gl2.h">

typedef struct Descriptor{
    float32_t descriptor_vec[64];
}Descriptor;

GLint conpare_descriptors(Descriptor* descriptor_1, Descriptor* descriptor_2){
    float32_t diff = 0;
    int i;
    for (i = 0; i < 64; ++i){
        diff += (descriptor_1->descriptor_vec[i] - descriptor_2->descriptor_vec[i]) * (descriptor_1->descriptor_vec[i] - descriptor_2->descriptor_vec[i]);
    }
    return diff;
}



#endif
