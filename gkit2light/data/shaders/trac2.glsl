
#version 330
#pragma debug(on)
#ifdef VERTEX_SHADER
layout(location = 0) in vec3 position;

uniform float scale;      // Ajout de l'uniforme de scale

 //uniform int  nbvert;
 uniform vec3 positions[2000];
 uniform mat4 mvpMatrix;
uniform float frequency;
uniform float time;
out vec2 intexcoord;
in vec2 texcoord;
void main( )
{

    intexcoord=texcoord;
    
    vec4 pos=vec4(position,0.0);
    if (positions[gl_VertexID].y<2)
    {
        //vec4 dis = vec4(3.3*scale,positions[gl_VertexID].y +frequency/ 10.0,0.8, 1.0);
	    pos = vec4(3.3*scale,positions[gl_VertexID].y +frequency,0.8, 1.0);
    }
    else
    {
        //vec4 dis = vec4(3.3*scale,positions[gl_VertexID].y-frequency,0.8, 1.0);
	    pos = vec4(3.3*scale,positions[gl_VertexID].y-frequency,0.8, 1.0);
    }
	
	gl_Position = mvpMatrix * pos;
 
}
#endif

#ifdef FRAGMENT_SHADER

uniform float time;
uniform vec3 motion;    // x, y, button > 0
uniform vec3 mouse;     // x, y, button > 0
uniform vec2 viewport;


/*
catalogue de fonctions sur les spheres :
http://www.iquilezles.org/www/articles/spherefunctions/spherefunctions.htm
*/

#define inf 999999.0


float plane( const in vec3 o, const in vec3 d, const in vec3 anchor, const in vec3 normal )
{
    float t= dot(anchor - o, normal) / dot(d, normal);
    if(t < 0.0) return inf;
    return t;
}



uniform mat4 mvpInvMatrix;
uniform mat4 mvMatrix;

in vec2 intexcoord;
out vec4 fragment_color;

void main( )
{
    
    fragment_color=vec4(intexcoord.x, intexcoord.y, 1.0, 1.0);
    
}
#endif
