
varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp sampler2D sample_texture_2;

void main(){
    float keypoint = texture2D(sample_texture, frag_tex_coord).r;

    if (keypoint > 0.0){
        gl_FragColor = vec4(1.0 ,0.0, 0.0, 1.0);
    }
    else{
        gl_FragColor = texture2D(sample_texture_2, frag_tex_coord);
    }

}
