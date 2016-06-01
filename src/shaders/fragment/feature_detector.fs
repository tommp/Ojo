varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp vec2 inv_buffer_size;

const int SAMPLE_RADIUS = 2;

const float THRESHOLD = 0.6;

void main(){
        vec2 gradient_sum = vec2(0.0, 0.0);


        for (int i = -SAMPLE_RADIUS; i < SAMPLE_RADIUS; ++i){
            for(int j = -SAMPLE_RADIUS; j < SAMPLE_RADIUS; ++j){
                vec2 gradient = texture2D(sample_texture, frag_tex_coord + (vec2(i,  j) * inv_buffer_size)).rg;
                gradient -= 1.0;
                gradient *= 2.0;

                gradient_sum += gradient;
            }
        }

        vec2 median = gradient_sum / (float(SAMPLE_RADIUS) * 2.0 + 1.0);

        vec2 variance = vec2(0.0, 0.0);

        for (int i = -SAMPLE_RADIUS; i < SAMPLE_RADIUS; ++i){
            for(int j = -SAMPLE_RADIUS; j < SAMPLE_RADIUS; ++j){
                vec2 gradient = texture2D(sample_texture, frag_tex_coord + (vec2(i,  j) * inv_buffer_size)).rg;
                gradient -= 1.0;
                gradient *= 2.0;

                variance += (gradient - median) * (gradient - median);
            }
        }

        float detected = 0.0;
        if (length(variance) > THRESHOLD){
            detected = 1.0;
        }

        gl_FragColor = vec4(1.0) * detected;
}
