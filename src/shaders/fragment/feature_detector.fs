varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;
uniform highp sampler2D sample_texture_2;

const float THRESHOLD = 0.1;

void main(){
        vec2 median = texture2D(sample_texture_2, frag_tex_coord).xy;
        vec2 variance = texture2D(sample_texture, frag_tex_coord).xy;


        if (variance.x > THRESHOLD && variance.y > THRESHOLD){
            gl_FragColor = vec4(variance, 0.0, 1.0);
        }
        else{
            gl_FragColor = vec4(0.0,0.0,0.0,1.0);

        }
}
