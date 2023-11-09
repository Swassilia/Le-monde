
#version 330
#pragma debug(on)
#ifdef VERTEX_SHADER
layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;



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

    vec4 pos=vec4(position, 1);
    intexcoord=texcoord;
        //vec4 dis = vec4(3.3*scale,positions[gl_VertexID].y +frequency/ 10.0,0.8, 1.0);
	    pos = pos+vec4(cos(texcoord.x*frequency)/time,cos(texcoord.y*frequency)/frequency,0,0);

    
	
	gl_Position =mvpMatrix*pos;
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
    color.a=1;
    
    return color;
}
void main()
{
    vec3 lightPos = vec3 (0,1000,0);
    vec3 norm =normalize(inormal);
    vec3 objectColor=vec3 (1,1,1);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightCol ;
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightCol;
    vec3 result = (ambient + diffuse)*objectColor;

    fragment_color=colorOpacity(terrain)*vec4(result, 1.0);
    
}
#endif
