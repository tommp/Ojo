attribute vec4 position;

varying vec2 frag_tex_coord;

void main(){
	frag_tex_coord = position.xy * 0.5 + 0.5;
	gl_Position = position;
}
