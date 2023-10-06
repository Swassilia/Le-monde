#version 330    core

#ifdef VERTEX_SHADER
// layout(location = 0) in vec3 position;
 uniform mat4 mvpMatrix;
// out vec2 position;
attribute vec3 aPosition;
attribute vec2 aTexCoord;
varying vec2 pos;

void main()
{
    pos= aTexCoord;
    vec4 position= vec4(aPosition, 1.0);
     position.xy*=2.-1.;
    
    gl_Position= mvpMatrix*position;

    

}

#endif

