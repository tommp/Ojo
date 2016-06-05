varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp vec2 inv_buffer_size;

const float THRESHOLD = 0.00001;
const float ALPHA = 0.06;


void main(){
    float var_sample = texture2D(sample_texture, frag_tex_coord).x;

    var_sample *= 2.0;
    var_sample -= 1.0;

    float comp_sample;

    for (int i = -1; i < 2; ++i){
        for(int j = -1; j < 2; ++j){
            if ( i == 0 && j == 0){
                continue;
            }
            float comp_sample = texture2D(sample_texture, frag_tex_coord + (vec2(i,  j) * inv_buffer_size)).r;
            comp_sample *= 2.0;
            comp_sample -= 1.0;

            if (var_sample < comp_sample) {
                var_sample = 0.0;
                break;
            }
        }
    }


    gl_FragColor = vec4(var_sample * 1000.0, 0.0, 0.0, 1.0);
}
