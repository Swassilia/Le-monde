#version 330

#ifdef VERTEX_SHADER
layout(location= 0) in vec3 position;

uniform mat4 mvpMatrix;

void main( )
{
    gl_Position= mvpMatrix * vec4(position, 1);
}

#endif

#ifdef FRAGMENT_SHADER
out vec4 fragment_color;
uniform vec3 iResolution;

vec3 couleur(){
    return vec3(0.0, 120.0 / 255.0, 120.0 / 255.0);
  }

void main()
{
   fragment_color = vec4(couleur(), 1.0);


}

#endif