#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "program.h"
#include "uniforms.h"
#include "draw.h"        // pour dessiner du point de vue d'une camera
#include "Viewer_etudiant.h"

using namespace std;
int vertex_count_eau;
int vertex_count_ter, vertex_count_decor;

static int CreatShader(const string & vertexShader , const string & fragment );



// Calcul les normals de chaque vertices d'un image
Vector terrainNormal(const Image& im, const int i, const int j){
    // Calcul de la normale au point (i,j) de l’image
    int ip = i-1;
    int in = i+1;
    int jp = j-1;
    int jn = j+1;
    
    Vector a( ip, 25.f*im(ip, j).r, j );
    Vector b( in, 25.f*im(in, j).r, j );
    Vector c( i, 25.f*im(i, jp).r, jp );
    Vector d( i, 25.f*im(i, jn).r, jn );

    Vector ab = normalize(a - b);
    Vector cd = normalize(d - c);

    Vector n = cross(ab,cd);
    return n;
}


/*-------------------------------------------fonction Init-------------------------------------*/

// Initialise un terrain a partir d'une image pour un mesh en particulier
void ViewerEtudiant::init_terrain(const Image& im, Mesh& m_Objet){
    m_Objet = Mesh(GL_TRIANGLE_STRIP);

    for(int i=1;i<im.width()-2;++i){ // Boucle sur les i
        for(int j=1;j<im.height()-1;++j){ // Boucle sur les j
            m_Objet.normal( terrainNormal(im, i+1, j) );
            m_Objet.texcoord(float(i+1)/float(im.width()),float(j)/float(im.height()));
            m_Objet.vertex( Point(i+1, 2.f*im(i+1, j).r, j) );
            
            m_Objet.normal( terrainNormal(im, i, j) );
            m_Objet.texcoord(float(i)/float(im.width()),float(j)/float(im.height()));
            m_Objet.vertex( Point(i, 2.f*im(i, j).r, j) );
        }
        m_Objet.restart_strip(); // Affichage en triangle_strip par bande
    }
}

void ViewerEtudiant::init_cube_map_Decor()
{
     m_cube_map_decor = Mesh(GL_TRIANGLE_STRIP); 

    float pt2[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} }; /// Tableau des coordonnées des 8 sommets

    int f2[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} }; /// Tableau des coordonnées des 6 faces

    float n2[6][3] = { {0,1,0}, {0,-1,0}, {-1,0,0}, {1,0,0}, {0,0,-1}, {0,0,1} }; /// Tableau des 6 normales pour chaque faces

    float tex[6][4] = {{0.25,0.5,0.33,0},{0.5,0.25,1,0.66}, {0.75,0.5,0.66,0.33}, {0.25,0,0.66,0.33}, {0.75,1,0.66,0.33},{0.5,0.25,0.66,0.33} };

    for(int i=0; i<6; i++) /// Parcours des 6 faces
    {
            m_cube_map_decor.normal(n2[i][0], n2[i][1], n2[i][2]); 

            m_cube_map_decor.texcoord(tex[i][0], tex[i][3]); // Coordonnées de la texture pour le sommet 0
            m_cube_map_decor.vertex( pt2[ f2[i][0]][0], pt2[ f2[i][0]][1], pt2[ f2[i][0]][2] ); // Coordonnées en x,y,z du sommet 0 de la face i

            m_cube_map_decor.texcoord(tex[i][0], tex[i][2]); // Coordonnées de la texture pour le sommet 3
            m_cube_map_decor.vertex( pt2[ f2[i][3] ][0], pt2[ f2[i][3] ][1], pt2[ f2[i][3] ][2] ); // Coordonnées en x,y,z du sommet 3 de la face i

            m_cube_map_decor.texcoord(tex[i][1], tex[i][3]); // Coordonnées de la texture pour le sommet 1
            m_cube_map_decor.vertex( pt2[ f2[i][1] ][0], pt2[ f2[i][1] ][1], pt2[ f2[i][1] ][2] ); // Coordonnées en x,y,z du sommet 1 de la face i

            m_cube_map_decor.texcoord(tex[i][1], tex[i][2]); // Coordonnées de la texture pour le sommet 2
            m_cube_map_decor.vertex( pt2[ f2[i][2] ][0], pt2[ f2[i][2] ][1], pt2[ f2[i][2] ][2] ); // Coordonnées en x,y,z du sommet 2 de la face i

            m_cube_map_decor.restart_strip();// Demande un nouveau strip
        }

}



/*
 * Fonction dans laquelle les initialisations sont faites.
 */
int ViewerEtudiant::init()
{
    Viewer::init();
    

    // Appel des images qui serviront de texture ou de modeler les objets
    m_surface_Alti = read_image("data/terrain/final5.png");
    m_surface_texture = read_texture(0, smart_path("data/terrain/final5.png"));
    m_terrainAlti= read_image("data/terrain/terrain.png");
    m_terrain_texture= read_texture(0,"data/terrain/terrain_texture.png");
    m_texture_Decor=read_texture(0,"data/decor.png");

    // Initialisations des objets 
    ViewerEtudiant:: init_cube_map_Decor();
    ViewerEtudiant:: init_terrain(m_surface_Alti, m_surface_Eau);
    ViewerEtudiant:: init_terrain(m_terrainAlti, m_terrain);
    
    // Appel des programes shaders 
    m_program_Eau= read_program("data/shaders/surface_Eau.glsl");
    m_program_Terrain= read_program("data/shaders/terrain.glsl");
    m_program_decor= read_program("data/shaders/cube_map.glsl");

    //Appel d'un shader simple qui ne fait qu'afficher l'objet en gris 
    // m_program_Eau= read_program("data/shaders/basic.glsl");
    // m_program_Terrain= read_program("data/shaders/basic.glsl");
    // m_program_decor= read_program("data/shaders/basic.glsl");
    


    vertex_count_eau=m_surface_Eau.vertex_count();
    vertex_count_ter=m_terrain.vertex_count();
    vertex_count_decor=m_cube_map_decor.vertex_count();
    
    cout<<endl;
    cout<<"vertex count : "<<vertex_count_eau<<endl;
    cout<<"vertex count : "<<vertex_count_ter<<endl;
    cout<<"vertex count : "<<vertex_count_decor<<endl;

    // Initialisation des vertices 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // affiche les erreurs du shader program
    program_print_errors(m_program_Eau);
    program_print_errors(m_program_Terrain);
    program_print_errors(m_program_decor);

    //configuration de la lumiere
    lightCol= vec3(1.0,1.0,1.0);
    
    // configurer les samplers
    glGenSamplers(1, &sampler);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glBindTexture(GL_TEXTURE_2D, 0);

    
        
    // etat openGL par defaut
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);        // couleur par defaut de la fenetre
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glClearDepth(1.f);                          // profondeur par defaut
    glDepthFunc(GL_LESS);                       // ztest, conserver l'intersection la plus proche de la camera
    glEnable(GL_DEPTH_TEST);  
    glEnable( GL_BLEND ); 

    

    
    return 0;

}
//----------------------------------------------------Fonction draw-------------------------------------------------//

int ViewerEtudiant:: quit( )
    {
        // etape 3 : detruire le shader program
        release_program(m_program_Eau);
        release_program(m_program_Terrain);
        release_program(m_program_decor);
        glDeleteVertexArrays(1, &vao);
        m_surface_Eau.release();
        m_terrain.release();
        m_cube_map_decor.release();
        glDeleteTextures(1, &m_texture_Decor);
        glDeleteTextures(1, &m_terrain_texture);        
        glDeleteTextures(1, &m_texture_Decor);

        
        return 0;
    }

int ViewerEtudiant::render()
{
  
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    manageCameraLight();

    gl.camera(m_camera);
    
    glBindVertexArray(vao);

    // configurer le shader program
    // recuperer les transformations
    Transform model=  Scale(1.2,2,1.2)*Translation(-15,-3.5,-15);
    Transform view= m_camera.view();
    Transform projection= m_camera.projection(window_width(), window_height(), 45);
    
    // composer les transformations : model, view et projection
    Transform mvp= projection * view * model;
    

    // parametrer le shader program m_program_Eau
    glUseProgram(m_program_Eau);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_surface_texture);
    glBindSampler(0, sampler);
    program_uniform(m_program_Eau, "mvpMatrix", mvp);
    program_uniform(m_program_Eau, "view", view);
    GLfloat time= glGetUniformLocation(m_program_Eau, "time");
    glUniform1f(time, float(global_time()));
    GLuint poslight=glGetUniformLocation(m_program_Eau, "lightCol");
    glUniform3f(poslight,lightCol.x,lightCol.y,lightCol.z);

    glDrawArrays(GL_TRIANGLES, 0, vertex_count_eau);
    m_surface_Eau.draw(m_program_Eau, /* use position */ true, /* use texcoord */ true, /* use normal */ true, 
    /* use color */ true, /* use material index*/ false);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBindSampler(0, 0);
    glUseProgram(0);
    glBindVertexArray(0);

    // parametrer le shader program m_program_Terrain
    glUseProgram(m_program_Terrain);
    model=Scale(0.5/3,6,0.5/3)*Translation(-100,-1.5,-100);
    view= m_camera.view();
    mvp=projection * view *model ;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_terrain_texture);
    glBindSampler(0, sampler);
    program_uniform(m_program_Terrain, "mvpMatrix", mvp);
    program_uniform(m_program_Terrain, "view", view);
    poslight=glGetUniformLocation(m_program_Terrain, "lightCol");
    glUniform3f(poslight,lightCol.x,lightCol.y,lightCol.z);

    glDrawArrays(GL_TRIANGLES, 0, vertex_count_ter);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    m_terrain.draw(m_program_Terrain, /* use position */ true, /* use texcoord */ true, /* use normal */ true, /* use color */ false, /* use material index*/ false);
    glBindSampler(0, 0);
    glUseProgram(0);
    glBindVertexArray(0);


    // parametrer le shader program m_program_decor
    glUseProgram(m_program_decor);
    model=Scale(16,16,16)*Translation(0,0.5,0);
    mvp=projection * view *model ;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture_Decor);
    glBindSampler(0, sampler);
    program_uniform(m_program_decor, "mvpMatrix", mvp);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count_decor);
    m_cube_map_decor.draw(m_program_decor, /* use position */ true, /* use texcoord */ true, /* use normal */ false, /* use color */ false, /* use material index*/ false);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBindSampler(0, 0);
    glUseProgram(0);
    glBindVertexArray(0);


    return 1;
    
}


/*
 * Fonction dans laquelle les mises a jours sont effectuees.
 */
int ViewerEtudiant::update( const float time, const float delta )
{
    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.
    // m_camera.rotation(3, 0);// rotation de la camera comme sur une sphere
    
    
    return 0;
}

/*
 * Constructeur.
 */

ViewerEtudiant::ViewerEtudiant() : Viewer()
{
    
}


/*
 * Programme principal.
 */
int main( int argc, char **argv )
{
    ViewerEtudiant v;
    v.run();
    return 0;
}
