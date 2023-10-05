#version 330

#ifdef VERTEX_SHADER
layout(location = 0) in vec3 position;
uniform mat4 mvpMatrix;
uniform float time;
vec3 deplace= vec3(3,7,1);

void main() {
    // Example: Modifier la position du vertex en fonction du temps
    // vec3 modifiedPosition = position + deplace*cos(time * 50.0) / 100.0;
    // gl_Position = mvpMatrix * vec4(modifiedPosition, 1.0);
      gl_Position= mvpMatrix *vec4( position  , 1.0 );
}
#endif


#ifdef FRAGMENT_SHADER
out vec4 fragment_color;
uniform float time;
vec3 couleur(float t){
    vec3 a = vec3(0.5 , 0.5 , 0.5);
    vec3 b= vec3(0.5,0.8,0.5);
    vec3 c= vec3(1.1, 1.1 , 1.1);
    vec3 d= vec3(0.886,0.875,0.655);
    //palette de couleur pour la formule
    vec3 result = a+ b*cos(6.4513*(c*t + d));
    return result;
  }
void main() {
    // if (sin(time) > 0.0) {
    //     fragment_color = vec4(1.0, 0.0, 0.0, 1.0);  // Rouge
    // } else {
        fragment_color = vec4(couleur(time), 1.0);  // Bleu
    
}
#endif