varying highp vec2 frag_tex_coord;

uniform highp sampler2D sample_texture;

uniform highp vec2 inv_buffer_size;

void main(){
    vec3 result = texture2D(sample_texture, frag_tex_coord).rgb * 0.227027;

    result += texture2D(sample_texture, frag_tex_coord + (vec2(1,0.0) * inv_buffer_size)).rgb * 0.1945946;
    result += texture2D(sample_texture, frag_tex_coord - (vec2(1,0.0) * inv_buffer_size)).rgb * 0.1945946;
    result += texture2D(sample_texture, frag_tex_coord + (vec2(2,0.0) * inv_buffer_size)).rgb * 0.1216216;
    result += texture2D(sample_texture, frag_tex_coord - (vec2(2,0.0) * inv_buffer_size)).rgb * 0.1216216;
    result += texture2D(sample_texture, frag_tex_coord + (vec2(3,0.0) * inv_buffer_size)).rgb * 0.054054;
    result += texture2D(sample_texture, frag_tex_coord - (vec2(3,0.0) * inv_buffer_size)).rgb * 0.054054;
    result += texture2D(sample_texture, frag_tex_coord + (vec2(4,0.0) * inv_buffer_size)).rgb * 0.016216;
    result += texture2D(sample_texture, frag_tex_coord - (vec2(4,0.0) * inv_buffer_size)).rgb * 0.016216;

    gl_FragColor = vec4(result, 1.0);
}
