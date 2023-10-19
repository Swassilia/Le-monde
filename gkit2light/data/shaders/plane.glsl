#version 330    core

#ifdef VERTEX_SHADER
layout(location = 0) in vec3 position;
uniform mat4 mvpMatrix;
attribute vec2 aTexCoord;
varying vec2 pos;
uniform float u_time;

void main()
{
    pos= aTexCoord;
     vec3 positions;
    if (positions[gl_VertexID]==0)
      {  positions= vec4(position.x+u_time,position.y,position.z, 1.0);
    }
    gl_Position= mvpMatrix*vec4(positions);

    

}

#endif

#ifdef FRAGMENT_SHADER
uniform vec2 u_resolution;
uniform float u_time;
out vec4 fragment_color;

void main()
{
    vec2 coord=gl_FragCoord.xy/u_resolution;

    vec3 color= vec3(0.5 *sin(coord.x)+0.5,0.5 *sin(coord.y)+0.5, 0.5 *sin(coord.x+coord.y));
    fragment_color=vec4(coord,0.0, 1.0);
}
#endif
