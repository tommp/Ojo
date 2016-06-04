varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

const float THRESHOLD = 0.0001;
const float ALPHA = 0.04;


void main(){
    vec4 var_sample = texture2D(sample_texture, frag_tex_coord).xyzw;

    var_sample *= 2.0;
    var_sample -= 1.0;

    float calc_res = (var_sample.x * var_sample.y - var_sample.z * var_sample.z) - ALPHA * ((var_sample.x + var_sample.y) * (var_sample.x + var_sample.y));

    if (calc_res > THRESHOLD){
        gl_FragColor = vec4(1.0);
    }
    else{
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
