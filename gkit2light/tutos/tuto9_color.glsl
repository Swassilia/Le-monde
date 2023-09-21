#version 330

#ifdef VERTEX_SHADER
layout(location= 0) in vec3 position;

uniform mat4 mvpMatrix;

void main( )
{
    gl_Position= mvpMatrix * vec4(position, 1);
}

#endif





#ifdef FRAGMENT_SHADER
 in vec3 position;
out vec4 fragment_color;
vec3 couleur(float t){
    vec3 a = vec3(0.5 , 0.5 , 0.5);
    vec3 b= vec3(0.5,0.8,0.5);
    vec3 c= vec3(1.1, 1.1 , 1.1);
    vec3 d= vec3(0.886,0.875,0.655);
    //palette de couleur pour la formule
    vec3 result = a+ b*cos(6.4513*(c*t + d));
    return result;
  }
uniform vec4 color;
uniform vec3 iResolution;

void main( )
{
    //uv (resolution) ramener a une taille 1*1 (2d) , recentrer par -0.5 puis 
    vec2 uv = ((gl_FragCoord.xy/iResolution.xy) -0.5 ); 
    uv.x *= position.x / position.y;
    //sauvegarde de l'etat de uv 
    vec2 folie = uv;
    //preparation de la couleur final a 0,0,0,0
    vec3 couleur_final = vec3(0.0);
    //boucle pour alleger la boucle
    for (float j=0.0; j<4.0; j++){
        
        // + on est eloigne du centre plus la valeur de d est grande
         float d =length(uv) + exp(-length(folie)); 
        //choix de couleur a un instant T
        vec3 col = couleur(length(folie));
        //boucle sur sin
        d=sin(d*8.0 + 10.0)/8.0;
        //rend visible les valeurs negative de d (celle qui s'annule au centre)
        d=abs(d);
        //va fluidifier les couleurs
        d= pow(0.02 / d, 1.2);
        //va ajouter les 2 mouvements de couleurs
        couleur_final+=col*d;
    }

    fragment_color= vec4(couleur_final,1.0);
// // vec2 startPoint = vec2(0.0, 0.0);  // Point de départ
// // vec2 endPoint = vec2(1.0, 1.0);    // Point de fin
// // float interpolationFactor = 0.5;    // Facteur d'interpolation entre 0.0 et 1.0 (0.0 = départ, 1.0 = fin)

// // vec2 interpolatedPoint = startPoint + (endPoint - startPoint) * interpolationFactor;

// // fragment_color=vec4(color,1.0);

}

#endif
