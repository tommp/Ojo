varying highp vec2 frag_tex_coord;
uniform highp sampler2D sample_texture;

void main(){
	gl_FragColor = texture2D(sample_texture, frag_tex_coord);
}
