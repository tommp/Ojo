varying highp vec2 frag_tex_coord;
uniform highp sampler2D sample_texture;

const vec3 lum_coefficient = vec3(0.22, 0.707, 0.071);

float calc_luminance(vec3 color){
    return dot(color, lum_coefficient);
}

void main(){
        gl_FragColor.r = calc_luminance(texture2D(sample_texture, frag_tex_coord));
}
