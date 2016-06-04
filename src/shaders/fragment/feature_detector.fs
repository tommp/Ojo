varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;
uniform highp sampler2D sample_texture_2;

const float THRESHOLD = 0.1;

void main(){
        vec3 median = texture2D(sample_texture_2, frag_tex_coord).xyz;
        vec3 variance = texture2D(sample_texture, frag_tex_coord).xyz;

        gl_FragColor = vec4(variance, 1.0);
        /*if (variance.x > THRESHOLD && variance.y > THRESHOLD){
            gl_FragColor = vec4(variance * 20.0, 0.0, 1.0);
        }
        else{
            gl_FragColor = vec4(0.0,0.0,0.0,1.0);

        }*/
}
