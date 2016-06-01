varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp vec2 inv_buffer_size;

highp vec2 harris_kernel = vec2(1.0, 2.0);

const highp float NORM_FACTOR  = 0.16666666;

const vec3 LUM_COEFF = vec3(0.33, 0.33, 0.33);//vec3(0.22, 0.707, 0.071);

float calc_luminance(vec3 color){
    return dot(color, LUM_COEFF);
}

void main(){

        float v_sum_1 = calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(0,  1) * inv_buffer_size)).rgb * harris_kernel[0]) +
                        calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(0,  2) * inv_buffer_size)).rgb * harris_kernel[1]);

        float v_sum_2 = calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(0, -1) * inv_buffer_size)).rgb * harris_kernel[0]) +
                        calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(0, -2) * inv_buffer_size)).rgb * harris_kernel[1]);

        float h_sum_1 = calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2( 1, 0) * inv_buffer_size)).rgb * harris_kernel[0]) +
                        calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2( 2, 0) * inv_buffer_size)).rgb * harris_kernel[1]);

        float h_sum_2 = calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(-1, 0) * inv_buffer_size)).rgb * harris_kernel[0]) +
                        calc_luminance(texture2D(sample_texture, frag_tex_coord + (vec2(-2, 0) * inv_buffer_size)).rgb * harris_kernel[1]);

        vec2 grad = vec2(h_sum_1 - h_sum_2, v_sum_1 - v_sum_2) * NORM_FACTOR;

        float grad_length = length(grad);

        grad += 1.0;
        grad *= 0.5;

        gl_FragColor = vec4(grad, grad_length, 1.0);
}
