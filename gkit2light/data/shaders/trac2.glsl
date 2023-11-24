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

vec3 lightPosi()
{
    return vec3(-5, 5, -5);
}

void main()
{
    vec4 pos = vec4(position, 1);
    intexcoord = texcoord;
    // pos = pos + vec4(0, cos(texcoord.y* 2.0 * (time/(300*3.14)))/5, 0, 0);
    pos = pos + vec4(0, min(sin(texcoord.y* 2.0 * (time/(300*3.14+0.1)+0.1)/5) , cos(texcoord.y* 2.0 * (time/(300*3.14))+0.1)/5 )/5, 0, 0);

    gl_Position = mvpMatrix * pos;
    FragPos = vec3(0, 5, 0);
    inormal = normal;
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

uniform vec3 view;               // Position de la caméra
uniform vec3 specularColor = vec3(0.23, 0.73, 0.9686); // Couleur spéculaire
uniform float shininess = 10.0;     // Exposant de brillance

vec4 colorOpacity(sampler2D ni)
{
    vec4 color = texture(ni, intexcoord);
    color.a = 1;

    return color;
}

void main()
{
    vec3 lightPos = vec3(0, 6.5, 0);
    vec3 norm = normalize(inormal);
    vec3 objectColor = vec3(0.33, 0.9  , 0.90);
    float ambientStrength = 2;

    float distance = length(lightPos - FragPos)*1;

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

    fragment_color = colorOpacity(terrain) * vec4(result, 1.0);
}

#endif
