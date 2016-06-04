//The attribute qualifier specifies that this is an attribute to be read as input from the currently bound buffer object.
//In this case, it represents the position of a vertex, simply a point in 3D space.

attribute vec4 position;

//The varying qualifier, when used in the vertex shader, specifies that this is an output variable to be used as input to the next shader stage.

varying vec2 frag_tex_coord;

void main(){
        //This variable will be linearly interpolated in order to produce coordinates for
        //sampling textures at positions matching the coordinates of the corresponding fragment in the fragment shader.

	frag_tex_coord = position.xy * 0.5 + 0.5;

        //gl_position is an inbuilt vertex shader variable that is used to interpolate the position of fragments in the fragment shader.
        //This variable must be written to or undefined behavior will occur.

	gl_Position = position;
}
