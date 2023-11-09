
#version 330
#pragma debug(on)
#ifdef VERTEX_SHADER
layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;



uniform vec3 positions[2000];
uniform mat4 model;
uniform mat4 mvpMatrix;
uniform float frequency;
uniform float time;
out vec2 intexcoord;
out vec3 inormal;
out vec3 FragPos;
in vec2 texcoord;
void main()
{
vec4 p=vec4(position, 1);
    vec4 pos=vec4(0.0,0.0,0.0,1.0);
    intexcoord=texcoord;
    if (positions[gl_VertexID].y<1)
    {
        //vec4 dis = vec4(3.3*scale,positions[gl_VertexID].y +frequency/ 10.0,0.8, 1.0);
	    pos = pos+vec4(0,cos(frequency)/5,0, 0);

    }
    else
    {
        //vec4 dis = vec4(3.3*scale,positions[gl_VertexID].y-frequency,0.8, 1.0);
	    pos = pos-vec4(0,0,0,0);

    }
	
	gl_Position = mvpMatrix*vec4(position, 1.0);
    FragPos = vec3(pos);
    inormal=normal;
 
}
#endif

#ifdef FRAGMENT_SHADER

uniform float time;



uniform sampler2D terrain;
in vec2 intexcoord;
in vec3 FragPos; 
uniform vec3 lightCol;
out vec4 fragment_color;
in vec3 inormal;

// layout(location=2)in vec3 normal;    // Normale du fragment
// in vec3 position;  // Position du fragment


vec4 colorOpacity(sampler2D ni)
{
    vec4 color= texture(ni,intexcoord);
    color.a=color.r+0.5;
    
    return color;
}
void main()
{
    vec3 lightPos = vec3 (8,4,5);
    vec3 norm =normalize(inormal);
    vec3 objectColor=vec3 (0.2,0.4,0.3);
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightCol ;
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightCol;
    vec3 result = (ambient + diffuse)*objectColor;
    fragment_color=colorOpacity(terrain)*vec4(result, 1.0);
    
}
#endif
