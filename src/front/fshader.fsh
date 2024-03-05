uniform vec4 color;
//uniform sampler2D sampler;

//varying float v_space_size;
//varying float v_line_size;

void main(void)
{
//    if (fract(10000 / (v_line_size + v_space_size)) > v_line_size/(v_line_size + v_space_size)) {
//        discard;
//    }
    gl_FragColor = color;
}
