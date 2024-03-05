attribute vec4 a_position;
attribute float space_size;
attribute float line_size;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

//varying float v_space_size;
//varying float v_line_size;

void main(void)
{
    gl_Position = u_projectionMatrix * u_viewMatrix * a_position;

//    v_space_size = space_size;
//    v_line_size = line_size;
}
