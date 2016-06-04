varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp vec2 inv_buffer_size;

const int SAMPLE_RADIUS = 1;
const float NUM_SAMPLES = (float(SAMPLE_RADIUS) * 2.0 + 1.0) * (float(SAMPLE_RADIUS) * 2.0 + 1.0);

void main(){
    vec4 gradient_sum = vec4(0.0);
    vec4 unsigned_gradient_sum = vec4(0.0);

    for (int i = -SAMPLE_RADIUS; i < SAMPLE_RADIUS + 1; ++i){
        for(int j = -SAMPLE_RADIUS; j < SAMPLE_RADIUS + 1; ++j){
            vec4 gradient = texture2D(sample_texture, frag_tex_coord + (vec2(i,  j) * inv_buffer_size)).rgba;
            gradient *= 2.0;
            gradient -= vec4(1.0);

            gradient_sum += gradient;
            unsigned_gradient_sum += abs(gradient);
        }
    }

    gradient_sum  /= NUM_SAMPLES;

    unsigned_gradient_sum /= NUM_SAMPLES;

    gradient_sum += vec4(1.0);
    gradient_sum *= 0.5;

    unsigned_gradient_sum += vec4(1.0);
    unsigned_gradient_sum *= 0.5;

    gl_FragColor = vec4(gradient_sum);
}
