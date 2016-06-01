varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;
uniform highp float inv_buffer_width;
uniform highp float inv_buffer_height;

uniform highp vec2 inv_buffer_size;


highp vec2 harris_kernel = vec2(1.0, 2.0);

highp float divisor = length(vec3(1.0, 1.0, 1.0));


void main(){
        vec2 inv_screen_size = inv_buffer_size;

        vec4 v_sum_1 = texture2D(sample_texture, frag_tex_coord + (vec2(0,  1) * inv_screen_size)) * harris_kernel[0] +
                       texture2D(sample_texture, frag_tex_coord + (vec2(0,  2) * inv_screen_size)) * harris_kernel[1];

        vec4 v_sum_2 = texture2D(sample_texture, frag_tex_coord + (vec2(0, -1) * inv_screen_size)) * harris_kernel[0] +
                       texture2D(sample_texture, frag_tex_coord + (vec2(0, -2) * inv_screen_size)) * harris_kernel[1];

        vec4 h_sum_1 = texture2D(sample_texture, frag_tex_coord + (vec2( 1, 0) * inv_screen_size)) * harris_kernel[0] +
                       texture2D(sample_texture, frag_tex_coord + (vec2( 2, 0) * inv_screen_size)) * harris_kernel[1];

        vec4 h_sum_2 = texture2D(sample_texture, frag_tex_coord + (vec2(-1, 0) * inv_screen_size)) * harris_kernel[0] +
                       texture2D(sample_texture, frag_tex_coord + (vec2(-2, 0) * inv_screen_size)) * harris_kernel[1];

        gl_FragColor = vec4(length(v_sum_1 - v_sum_2) / divisor, length(h_sum_1 - h_sum_2) / divisor, 0.0, 1.0);
}
