varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp vec2 inv_buffer_size;

highp vec2 harris_kernel = vec2(1.0, 2.0);

const highp float NORM_FACTOR  = 0.16666666;

const vec3 LUM_COEFF = vec3(0.22, 0.707, 0.071);

float calc_luminance(vec3 color){
    return dot(color, LUM_COEFF);
}

float calc_haar_horizontal(){
    float sum = calc_luminance(texture2D(sample_texture, frag_tex_coord).rgb) * -2.0;
    sum +=  calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(1,  0) * inv_buffer_size)).rgb);
    sum +=  calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  0) * inv_buffer_size)).rgb);

    return sum / 4.0;
}

float calc_haar_diagonal(){
    float sum =  calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(1,  1) * inv_buffer_size)).rgb) * -1.0;
    sum +=  calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  -1) * inv_buffer_size)).rgb) * -1.0;
    sum +=  calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(1,  0) * inv_buffer_size)).rgb);
    sum +=  calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(0,  -1) * inv_buffer_size)).rgb);

    return sum / 4.0;

}

float calc_haar_vertical(){
    float sum = calc_luminance(texture2D(sample_texture, frag_tex_coord).rgb) * -2.0;
    sum +=  calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(0,  1) * inv_buffer_size)).rgb);
    sum +=  calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(0,  -1) * inv_buffer_size)).rgb);

    return sum / 4.0;
}

void main(){

        vec3 grad = vec3(calc_haar_diagonal(), calc_haar_vertical() * 0.0, 0.0);

        grad += vec3(1.0);
        grad *= 0.5;

        gl_FragColor = vec4(grad, 1.0);
}

