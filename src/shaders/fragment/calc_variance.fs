varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;
uniform highp sampler2D sample_texture_2;

uniform highp vec2 inv_buffer_size;

const int SAMPLE_RADIUS = 1;
const float NUM_SAMPLES = (float(SAMPLE_RADIUS) * 2.0 + 1.0) * (float(SAMPLE_RADIUS) * 2.0 + 1.0);

void main(){
    vec4 variance = vec4(0.0);
    vec4 median = texture2D(sample_texture_2, frag_tex_coord).rgba;
    median *= 2.0;
    median -= vec4(1.0);

    for (int i = -SAMPLE_RADIUS; i < SAMPLE_RADIUS + 1; ++i){
        for(int j = -SAMPLE_RADIUS; j < SAMPLE_RADIUS + 1; ++j){
            vec4 gradient = texture2D(sample_texture, frag_tex_coord + (vec2(i,  j) * inv_buffer_size)).rgba;
            gradient *= 2.0;
            gradient -= vec4(1.0);

            vec4 diff = gradient - median;

            variance += abs(diff) * 0.5;
        }
    }

    variance /= NUM_SAMPLES;

    gl_FragColor = vec4(variance);
}
