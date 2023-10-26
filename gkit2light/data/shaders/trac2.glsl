
#version 330
#pragma debug(on)
#ifdef VERTEX_SHADER
layout(location = 0) in vec3 position;

uniform float scale;      // Ajout de l'uniforme de scale


uniform vec3 positions[2000];
uniform mat4 mvpMatrix;
uniform float frequency;
uniform float time;
out vec2 intexcoord;
in vec2 texcoord;
void main()
{

    vec4 pos=vec4(position,1.0);
    intexcoord=texcoord;
    if (positions[gl_VertexID].y<1)
    {
        //vec4 dis = vec4(3.3*scale,positions[gl_VertexID].y +frequency/ 10.0,0.8, 1.0);
	    pos = pos+vec4(0,sin(frequency),0, 0);

    }
    else
    {
        //vec4 dis = vec4(3.3*scale,positions[gl_VertexID].y-frequency,0.8, 1.0);
	    pos = pos-vec4(0,0,10,0);

    }
	
	gl_Position = mvpMatrix *vec4(position,1.0);
 
}
#endif

#ifdef FRAGMENT_SHADER

uniform float time;


#define inf 999999.0

uniform sampler2D terrain;
in vec2 intexcoord;
out vec4 fragment_color;
// layout(location=2)in vec3 normal;    // Normale du fragment
// in vec3 position;  // Position du fragment


vec4 colorOpacity(sampler2D ni)
{
    vec4 color= texture(ni,intexcoord);
    if (color.rgb == vec3(0.0))
    {
        color.a*=0.2;
    }
    return color;
}
void main()
{
    
    fragment_color=colorOpacity(terrain);
    
}
#endif

