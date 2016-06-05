//The varying qualifier, when used in the fragment shader, specifies that this is an input variable passed from the previous shader stages.

varying highp vec2 frag_tex_coord;

//A sampler is a handle that allows the fragment shader to read in and sample data from texture images stored in video memory.
//Here it represents a camera sample stored in vram. The highp qualifier specifies hight precision data,
//and the uniform qualifier means that the value of this handle will be specified by the program maintaining the openGL ES context.

uniform highp sampler2D sample_texture;

void main(){
        //glFragColor is an inbuilt variable at the fragment shader stage that represents the final color of a pixel in the output buffer.
        gl_FragColor = texture2D(sample_texture, frag_tex_coord);
}
