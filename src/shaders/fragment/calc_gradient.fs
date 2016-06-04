varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp vec2 inv_buffer_size;

const vec3 LUM_COEFF = vec3(0.22, 0.707, 0.071);

float calc_luminance(vec3 color){
    return dot(color, LUM_COEFF);
}

float calc_horizontal(){
    float sum = 2.0 * calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(1 ,  0) * inv_buffer_size)).rgb);
    sum -=  2.0 * calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(-1 ,  0) * inv_buffer_size)).rgb);

    sum += calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(1,  1) * inv_buffer_size)).rgb);
    sum -= calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  1) * inv_buffer_size)).rgb);

    sum += calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(1,  -1) * inv_buffer_size)).rgb);
    sum -= calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(-1 ,  -1) * inv_buffer_size)).rgb);

    return sum / 8.0;
}


float calc_vertical(){
    float sum = 2.0 * calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(0 ,  1) * inv_buffer_size)).rgb);
    sum -=  2.0 * calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(0 ,  -1) * inv_buffer_size)).rgb);

    sum += calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(1,  1) * inv_buffer_size)).rgb);
    sum -= calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(1,  -1) * inv_buffer_size)).rgb);

    sum += calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  1) * inv_buffer_size)).rgb);
    sum -= calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  -1) * inv_buffer_size)).rgb);

    return sum / 8.0;
}

void main(){
        vec2 grad = vec2(calc_horizontal(), calc_vertical());

        grad += vec2(1.0);
        grad *= 0.5;

        gl_FragColor = vec4(grad, 0.0, 1.0);
}

