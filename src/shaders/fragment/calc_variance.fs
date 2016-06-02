varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;
uniform highp sampler2D sample_texture_2;

uniform highp vec2 inv_buffer_size;

const int SAMPLE_RADIUS = 2;
const float NUM_SAMPLES = (float(SAMPLE_RADIUS) * 2.0 + 1.0) * (float(SAMPLE_RADIUS) * 2.0 + 1.0);

void main(){
    vec2 variance = vec2(0.0);
    vec2 median = texture2D(sample_texture_2, frag_tex_coord).rg;
    median *= 2.0;
    median -= vec2(1.0);

    for (int i = -SAMPLE_RADIUS; i < SAMPLE_RADIUS + 1; ++i){
        for(int j = -SAMPLE_RADIUS; j < SAMPLE_RADIUS + 1; ++j){
            vec2 gradient = texture2D(sample_texture, frag_tex_coord + (vec2(i,  j) * inv_buffer_size)).rg;
            gradient *= 2.0;
            gradient -= vec2(1.0);

            vec2 diff = gradient - median;

            variance +=  vec2(diff.x * diff.x, diff.y * diff.y);
        }
    }

    variance /= NUM_SAMPLES;


    gl_FragColor = vec4(variance * 10.0, 0.0, 1.0);
}
