#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "program.h"
#include "uniforms.h"
#include "draw.h"        // pour dessiner du point de vue d'une camera
#include "Viewer_etudiant.h"

using namespace std;

static int CreatShader(const string & vertexShader , const string & fragment );




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

void ViewerEtudiant::init_cube()
{
    std::cout<<"init_cube"<<std::endl;

    
    //       4---5
    //      /|  /|
    //     7---6 |
    //     | 0-|-1
    //     |/  |/
    //     3---2
    
    
    // Sommets                     0           1           2       3           4           5       6           7
    static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };
    
    // Faces                    0         1           2           3          4         5
    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
    
    // Normales
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
    
    int i;

    m_cube = Mesh(GL_TRIANGLE_STRIP);
    m_cube.color( Color(1, 1, 1) );
    
    // Parcours des 6 faces
    for (i=0;i<6;i++)
    {
        m_cube.normal(n[i][0], n[i][1], n[i][2]);

        m_cube.texcoord(0,0);
        m_cube.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

        m_cube.texcoord(1,0);
        m_cube.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

        m_cube.texcoord(0,1);
        m_cube.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );
        
        m_cube.texcoord(1,1);
        m_cube.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );
        m_cube.restart_strip();
    }
    
}

void ViewerEtudiant::init_terrain(const Image& im){
    m_terrain = Mesh(GL_TRIANGLE_STRIP);

    for(int i=1;i<im.width()-2;++i){ // Boucle sur les i
        for(int j=1;j<im.height()-1;++j){ // Boucle sur les j
            m_terrain.normal( terrainNormal(im, i+1, j) );
            m_terrain.texcoord(float(i+1)/float(im.width()),float(j)/float(im.height()));
            m_terrain.vertex( Point(i+1, 2.f*im(i+1, j).r, j) );

            m_terrain.normal( terrainNormal(im, i, j) );
            m_terrain.texcoord(float(i)/float(im.width()),float(j)/float(im.height()));
            m_terrain.vertex( Point(i, 2.f*im(i, j).r, j) );
        }
        m_terrain.restart_strip(); // Affichage en triangle_strip par bande
    }
}


void ViewerEtudiant:: init_cubeN()
{

}

/*
 * Fonction dans laquelle les initialisations sont faites.
 */
int ViewerEtudiant::init()
{
    Viewer::init();
    Point pmin, pmax;
    m_cube.bounds(pmin, pmax);
      m_camera.lookat(pmin, pmax);
    
    //m_camera.lookat( Point(0,0,0), 150 );
    
    m_program= read_program("data/shaders/gradient.glsl");

     program_print_errors(m_program);
        
        // etat openGL par defaut
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);        // couleur par defaut de la fenetre
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glClearDepth(1.f);                          // profondeur par defaut
        glDepthFunc(GL_LESS);                       // ztest, conserver l'intersection la plus proche de la camera
        glEnable(GL_DEPTH_TEST);   

    
    /// Chargement des textures
    m_terrainAlti = read_image("data/terrain/Clipboard01.png");
    m_terrain_texture = read_texture(0, smart_path("data/terrain/Clipboard01_texture.png"));
    
    
    /// Appel des fonctions init_votreObjet pour creer les Mesh
      //ViewerEtudiant:: init_terrain(m_terrainAlti);
      ViewerEtudiant::init_cube();
    
    
    
    return 0;
}
//----------------------------------------------------Fonction draw-------------------------------------------------//
void ViewerEtudiant::draw_terrain(const Transform &T){

    gl.model(T*Translation(5,0.5,5));
    gl.draw(m_terrain);
    gl.texture(m_terrain_texture);
}

void ViewerEtudiant::draw_cube(const Transform& T)
{
    // gl.model(T*Scale(0.5,0.5,0.5));
    gl.model(T);
   // gl.texture(tex);
    //gl.lighting(false);
    gl.draw(m_cube);
    //gl.lighting(true);
}
int ViewerEtudiant:: quit( )
    {
        // etape 3 : detruire le shader program
        release_program(m_program);

        m_cube.release();
        glDeleteTextures(1, &m_texture);
        
        return 0;
    }

int ViewerEtudiant::render()
{
  
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    manageCameraLight();

    gl.camera(m_camera);
    
    // /// Transform
    Transform T_terrain;
    T_terrain=Translation(-12,0,-12)*Scale(0.5/4,4,0.5/4);
    
        // etape 2 : dessiner m_objet avec le shader program
        // configurer le pipeline 
        glUseProgram(m_program);

        // configurer le shader program
        // . recuperer les transformations
        // Transform model= RotationX(global_time() / 20);
        //
        Transform model=  Scale(2,2,2);
        Transform view= m_camera.view();
        Transform projection= m_camera.projection(window_width(), window_height(), 45);
        
        // . composer les transformations : model, view et projection
        Transform mvp= projection * view * model;
        
        // . parametrer le shader program :
        //   . transformation : la matrice declaree dans le vertex shader s'appelle mvpMatrix
        program_uniform(m_program, "mvpMatrix", mvp);
        program_uniform(m_program,"time" , float(global_time()));
        
        // . parametres "supplementaires" :
        //   . couleur des pixels, cf la declaration 'uniform vec4 color;' dans le fragment shader
        //  program_uniform(m_program, "color", vec4(1, 1, 0, 1));
        // ou program_uniform(m_program, "color", Color(1, 1, 0, 1));
        
        // go !
        //m_cube.color(vec4(1, 1, 0, 1));
        m_cube.draw(m_program, /* use position */ true, /* use texcoord */ true, /* use normal */ true, /* use color */ true, /* use material index*/ false);

    
    return 1;
    
}


/*
 * Fonction dans laquelle les mises a jours sont effectuees.
 */
int ViewerEtudiant::update( const float time, const float delta )
{
    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.
    
    
    
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
