#version 330

#ifdef VERTEX_SHADER
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
uniform mat4 mvpMatrix; 
out  vec2 intexcoord;

void main()
{
    gl_Position= mvpMatrix * vec4(position, 1);
    intexcoord = texcoord;

}

#endif


#ifdef FRAGMENT_SHADER
uniform sampler2D cube;
in vec2 intexcoord;
out vec4 fragment_color;

void main()
{
    fragment_color=texture(cube, intexcoord);
}

#endif