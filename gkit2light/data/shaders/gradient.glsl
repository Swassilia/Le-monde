#version 330

#ifdef VERTEX_SHADER
 layout(location= 0) in vec3 position;
uniform vec3 positions[50];     // declare un uniform, un tableau de vec3
uniform float time;             // declare un uniform, time de type float
uniform mat4 mvpMatrix;
const vec3 deplace= vec3(3,7,1);  // declare une constante
uniform int ra;
void main( )
{

    gl_Position= mvpMatrix *vec4( positions[gl_VertexID] +deplace*cos(time*50)/100.0, 1.0 );
    // positions[gl_VertexID] est un vec3 + vec3 * float / float, ce qui donne bien un vec3 
    // et le vec3 est complete par une valeur pour etre affecte a un vec4 
}

#endif
#ifdef FRAGMENT_SHADER

in vec3 position;
out vec4 fragment_color;

void main()
{

    fragment_color = vec4(vec3(0.4,0.4,0.3), 1.0);


}

#endif