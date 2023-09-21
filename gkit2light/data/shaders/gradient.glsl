#version 330

#ifdef VERTEX_SHADER
layout(location= 0) in vec3 position;

uniform mat4 mvpMatrix;
varying float h;
void main( )
{
    
    h = position.y;
    gl_Position=  mvpMatrix*vec4(position, 1.0);
}

#endif
#ifdef FRAGMENT_SHADER

out vec4 fragment_color;

varying float h;

void main()
{
     float f = (h + 100.) / 200.;
    f = clamp(f, 0., 1.);
    gl_FragColor = vec4(mix(vec3(0.0, 0, 0), vec3( 255.0, 0.0, 120.0 / 255.0), f), 1.0);


}

#endif