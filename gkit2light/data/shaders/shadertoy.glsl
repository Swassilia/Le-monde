#version 330
#pragma debug(on)
#ifdef VERTEX_SHADER
layout(location= 0) in vec3 position;
layout(location=1) in vec2 texcoord;
layout(location = 2) in vec3 normal;

uniform mat4 mvpMatrix;
out vec2 intexcoord;
out vec3 inormal;
out vec3 FragPos;


void main()
{

    gl_Position= mvpMatrix * vec4(position, 1);
    intexcoord=texcoord;
    FragPos = vec3(0, 5, 0);
    inormal=normal;
}

#endif

#ifdef FRAGMENT_SHADER
in vec2 intexcoord;
uniform sampler2D decor;
in vec3 FragPos;
uniform vec3 lightCol;
out vec4 fragment_color;
in vec3 inormal;
uniform vec3 view;               // Position de la caméra
uniform vec3 specularColor = vec3(0.23, 0.73, 0.86); // Couleur spéculaire
uniform float shininess = 10.0; 

void main()
{
    vec3 lightPos = vec3(0, 7, 0);
    vec3 norm = normalize(inormal);
    vec3 objectColor = vec3(texture(decor,intexcoord));
    float ambientStrength = 2;

    float distance = length(lightPos - FragPos)*0.75;

    float attenuation = 1.0 / (distance * distance + 0.1);

    vec3 ambient = ambientStrength * lightCol * attenuation;

    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightCol * attenuation;

    // Réflexion spéculaire
    vec3 viewDir = normalize(view - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularColor * spec;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragment_color = vec4(result, 1.0);


}

#endif