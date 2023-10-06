#version 330

#ifdef VERTEX_SHADER
layout(location = 0) in vec3 position;
uniform mat4 mvpMatrix;
uniform float time;
in vec2 texcoord;
vec3 deplace= vec3(3,7,1);
out vec2 intexcoord;
void main() 
{
    // Example: Modifier la position du vertex en fonction du temps
    float nexwX = sin(position.x *(time * 50.0) / 100.0) * sin(position.y *(time * 50.0) / 100.0);
     vec3 modifiedPosition = vec3(position.x, position.y+cos(time),position.z);
    // gl_Position = mvpMatrix * vec4(modifiedPosition, 1.0);
    intexcoord=texcoord;
      gl_Position=mvpMatrix*vec4(position,1);
    //gl_Position= mvpMatrix *vec4( position  , 1.0 );
}
#endif


#ifdef FRAGMENT_SHADER
out vec4 fragment_color;
uniform float time;
in vec2 intexcoord;
// vec3 couleur(float t){
//     vec3 a = vec3(0.5 , 0.5 , 0.5);
//     vec3 b= vec3(0.5,0.8,0.5);
//     vec3 c= vec3(1.1, 1.1 , 1.1);
//     vec3 d= vec3(0.886,0.875,0.655);
//     //palette de couleur pour la formule
//     vec3 result = a+ b*cos(6.4513*(c*t + d));
//     return result;
//   }
void main() 
{


    // if (sin(time) > 0.0) {
      //fragment_color = vec4(1.0, 0.0, 0.0, 1.0);  // Rouge
    // } else {
        //fragment_color = vec4(couleur(time), 1.0);  // Bleu
      //  vec4 color=texture();
        fragment_color=vec4(intexcoord.x, intexcoord.y, 0.0, 1.0);
    
}
#endif