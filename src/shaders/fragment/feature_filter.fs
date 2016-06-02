varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp vec2 inv_buffer_size;

const int SAMPLE_RADIUS = 3;

const float THRESHOLD = 0.0;


void main(){
        vec4 value = texture2D(sample_texture, frag_tex_coord);
        float max_value = 0.0;


        for (int i = -SAMPLE_RADIUS; i < SAMPLE_RADIUS; ++i){
            for(int j = -SAMPLE_RADIUS; j < SAMPLE_RADIUS; ++j){
                vec4 descriptor_sample = texture2D(sample_texture, frag_tex_coord + (vec2(i,  j) * inv_buffer_size));

                max_value = max(length(descriptor_sample), max_value);
            }
        }

        vec3 result = value.xyz;

        if (max_value > length(value)){
            result = vec3(0.0);
        }

        gl_FragColor = vec4(result, 1.0);
}
