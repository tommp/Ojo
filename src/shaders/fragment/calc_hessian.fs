varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp vec2 inv_buffer_size;


void main(){
        vec2 grad = vec2(calc_horizontal(), calc_vertical());

        grad += vec2(1.0);
        grad *= 0.5;

        gl_FragColor = vec4(grad, 0.0, 1.0);
}

