varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp vec2 inv_buffer_size;

float normalize_range(float target){
    return (target * 2.0) - 1.0;
}


float calc_xx(){
    float xx = 2.0 * normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(1 ,  0) * inv_buffer_size)).r);
    xx -=  2.0 * normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(-1 ,  0) * inv_buffer_size)).r);

    xx += normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(1,  1) * inv_buffer_size)).r);
    xx -= normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  1) * inv_buffer_size)).r);

    xx += normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(1,  -1) * inv_buffer_size)).r);
    xx -= normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(-1 ,  -1) * inv_buffer_size)).r);

    return xx / 8.0;
}


float calc_yy(){
    float yy = 2.0 * normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(0 ,  1) * inv_buffer_size)).g);
    yy -=  2.0 * normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(0 ,  -1) * inv_buffer_size)).g);

    yy += normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(1,  1) * inv_buffer_size)).g);
    yy -= normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(1,  -1) * inv_buffer_size)).g);

    yy += normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  1) * inv_buffer_size)).g);
    yy -= normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  -1) * inv_buffer_size)).g);

    return yy / 8.0;
}

float calc_xy(){
    float xy = 2.0 * normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(0 ,  1) * inv_buffer_size)).r);
    xy -=  2.0 * normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(0 ,  -1) * inv_buffer_size)).r);

    xy += normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(1,  1) * inv_buffer_size)).r);
    xy -= normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(1,  -1) * inv_buffer_size)).r);

    xy += normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  1) * inv_buffer_size)).r);
    xy -= normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  -1) * inv_buffer_size)).r);

    return xy / 8.0;
}


float calc_yx(){
    float yx = 2.0 * normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(1 ,  0) * inv_buffer_size)).g);
    yx -=  2.0 * normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(-1 ,  0) * inv_buffer_size)).g);

    yx += normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(1,  1) * inv_buffer_size)).g);
    yx -= normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(-1,  1) * inv_buffer_size)).g);

    yx += normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(1,  -1) * inv_buffer_size)).g);
    yx -= normalize_range(texture2D(sample_texture, frag_tex_coord + (vec2(-1 ,  -1) * inv_buffer_size)).g);

    return yx / 8.0;
}

void main(){
        vec4 grad = vec4(calc_xx(), calc_yy(), calc_xy(), 1.0);

        grad += vec4(1.0);
        grad *= 0.5;

        gl_FragColor = grad;
}

