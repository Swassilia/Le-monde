#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "program.h"
#include "uniforms.h"
#include "draw.h"        // pour dessiner du point de vue d'une camera
#include "Viewer_etudiant.h"

using namespace std;
int vertex_count;

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


void ViewerEtudiant::init_sphere(){
    const int divBeta = 16;
    const int divAlpha = 20;
    int i,j;
    float beta,alpha,alpha2;

    m_sphere = Mesh(GL_TRIANGLE_STRIP);

    for(int i=0; i<=divAlpha;i++){
        alpha = -0.5f * M_PI +float (i)*M_PI/divAlpha;
        alpha2 = -0.5f * M_PI +float (i+1)*M_PI/divAlpha;

        for(int j=0;j<=divBeta;j++){
        beta = float(j) * 2.f*M_PI/(divBeta);
    

        m_sphere.normal(Vector(cos(alpha)*cos(beta), sin(alpha), cos(alpha)*sin(beta)));
        m_sphere.texcoord(float(beta)/float(2.f*M_PI), float(0.5+alpha)/float(M_PI));
        m_sphere.vertex(Point(cos(alpha)*cos(beta), sin(alpha), cos(alpha)*sin(beta)));

        m_sphere.normal(Vector(cos(alpha2)*cos(beta), sin(alpha2), cos(alpha2)*sin(beta)));
        m_sphere.texcoord(float(beta)/float(2.f*M_PI), float(0.5+alpha2)/float(M_PI));
        m_sphere.vertex(Point(cos(alpha2)*cos(beta), sin(alpha2), cos(alpha2)*sin(beta)));
        }
        m_sphere.restart_strip();
    }
    
}
void ViewerEtudiant::init_cylindre(){
    int i;
    const int div = 25;
    float alpha;
    float step = 2.0*M_PI/(div);

    m_cylindre = Mesh(GL_TRIANGLE_STRIP);
    //m_cylindre.color(Color(0,0,0));
    for(int i=0;i<= div; ++i){
        alpha = i*step;

        m_cylindre.normal(Vector(cos(alpha),0,sin(alpha)));
        m_cylindre.vertex(Point(cos(alpha),-1,sin(alpha)));
        m_cylindre.texcoord(float(i)/div,0);

        m_cylindre.normal(Vector(cos(alpha),0,sin(alpha)));
        m_cylindre.vertex(Point(cos(alpha),1,sin(alpha)));
        m_cylindre.texcoord(float(i)/div,1);
    }
}


/*
 * Fonction dans laquelle les initialisations sont faites.
 */
int ViewerEtudiant::init()
{
    Viewer::init();
     //ViewerEtudiant::init_cube();

    Point pmin, pmax;
    m_terrain.bounds(pmin, pmax);
    m_camera.lookat(pmin, pmax);
    m_terrainAlti = read_image("data/terrain/image_originel.png");

     ViewerEtudiant:: init_terrain(m_terrainAlti);
    
    m_camera.lookat( Point(0,0,0), 15 );
    //  m_program= read_program("data/shaders/gradient.glsl");
    // m_program= read_program("tutos/tuto4GL.glsl");
    m_program= read_program("data/shaders/trac2.glsl");

    vertex_count=m_terrain.vertex_count();
    cout<<endl;
    cout<<"vertex count : "<<vertex_count<<endl;
    vec3 positions [vertex_count];

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,
        /* length */    sizeof(positions),
        /* data */      positions,
        /* usage */     GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

     program_print_errors(m_program);
    
    GLint attribute= glGetAttribLocation(m_program, "position");
    if(attribute < 0)
       { // gros probleme...
       cout<< "oh non"<<endl;
        return -1;}

        glVertexAttribPointer(attribute, 3, GL_FLOAT,       // l'attribut est un vec3,
        /* not normalized */    GL_FALSE,               // les valeurs ne sont pas normalisees entre 0, et 1
        /* stride */            0,                      // les vec3 sont ranges les uns a la suite des autres
        /* offset */            0);                     // et se trouvent au debut du buffer

    glEnableVertexAttribArray(attribute);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

         // texcoord buffer
     glGenBuffers(1, &texcoord_buffer);
     glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer);
     glBufferData(GL_ARRAY_BUFFER, m_terrain.texcoord_buffer_size(), m_terrain.texcoord_buffer(), GL_STATIC_DRAW);
  
     // configurer l'attribut texcoord
     GLint texcoord= glGetAttribLocation(m_program, "texcoord");
     if(texcoord < 0)
         return -1;
     glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
     glEnableVertexAttribArray(texcoord);
  
    glGenSamplers(1, &sampler);
  
     glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
     glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
     m_terrain_texture = read_texture(0, smart_path("data/terrain/Clipboard01_texture.png"));
     glBindTexture(GL_TEXTURE_2D, 0);
     glUseProgram(0);


        
        // etat openGL par defaut
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);        // couleur par defaut de la fenetre
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glClearDepth(1.f);                          // profondeur par defaut
        glDepthFunc(GL_LESS);                       // ztest, conserver l'intersection la plus proche de la camera
        glEnable(GL_DEPTH_TEST);   

    
    /// Chargement des textures
     
    
    
    /// Appel des fonctions init_votreObjet pour creer les Mesh
    //   ViewerEtudiant::init_cylindre();
    
    
    
    return 0;

}
//----------------------------------------------------Fonction draw-------------------------------------------------//

int ViewerEtudiant:: quit( )
    {
        // etape 3 : detruire le shader program
        release_program(m_program);
        glDeleteBuffers(1, &vertex_buffer);
        glDeleteVertexArrays(1, &vao);
        m_terrain.release();
        glDeleteTextures(1, &m_texture);
        
        return 0;
    }

int ViewerEtudiant::render()
{
  
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    manageCameraLight();

    gl.camera(m_camera);
    
    glBindVertexArray(vao);

    glUseProgram(m_program);
    // vec3 positions[]
    //  for (const auto& vertex : meshVertices) {
    //     // Ajoutez les coordonnées du vertex au tableau des positions
    //     positions.push_back(m_terrain.vertex.x);
    //     positions.push_back(vertex.y);
    //     // positions.push_back(vertex.z);
        // etape 2 : dessiner m_objet avec le shader program
        // configurer le pipeline 
        // glUseProgram(m_program);

        // configurer le shader program
        // . recuperer les transformations
        // Transform model= RotationX(global_time() / 20);
        // Transform model=  Scale(0.5/4,4,0.5/4);
        
        // Transform model=  Scale(0.5,1,0.5)*Translation(-10,-1,-10);
        Transform model=  Identity();
        Transform view= m_camera.view();
        Transform projection= m_camera.projection(window_width(), window_height(), 45);
        
        // . composer les transformations : model, view et projection
        Transform mvp= projection * view * model;
         glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, m_terrain_texture);
     glBindSampler(0, sampler);

//  

// Initialiser le tableau positions avec les positions des sommets du cube

        
        // . parametrer le shader program :
        //   . transformation : la matrice declaree dans le vertex shader s'appelle mvpMatrix
        program_uniform(m_program, "mvpMatrix", mvp);
        program_uniform(m_program,"time" , float(global_time()));
        program_uniform(m_program,"scale", 2);
        program_uniform(m_program,"frequency", float(rand()%30));
        
        //initialisation de l'uniforme position
        GLuint positionsLocation = glGetUniformLocation(m_program, "positions");
        glUniform3fv(positionsLocation, vertex_count, m_cube.vertex_buffer());
        GLint location;
        location= glGetUniformLocation(m_program, "terrain");
        glUniform1i(location, 0);
    

        
        // . parametres "supplementaires" :
        //   . couleur des pixels, cf la declaration 'uniform vec4 color;' dans le fragment shader
        //  program_uniform(m_program, "color", vec4(1, 1, 0, 1));
        
        // go !
        glDrawArrays(GL_TRIANGLES, 0, vertex_count);
        //draw_terrain(model);
        m_terrain.draw(m_program, /* use position */ true, /* use texcoord */ true, /* use normal */ true, /* use color */ true, /* use material index*/ false);
         glBindTexture(GL_TEXTURE_2D, 0);
         glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glBindSampler(0, 0);
        glUseProgram(0);
        glBindVertexArray(0);
        
    return 1;
    
}
// void ViewerEtudiant::update_ter

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
