
#ifndef VIEWER_ETUDIANT_H
#define VIEWER_ETUDIANT_H

#include "Viewer.h"



class ViewerEtudiant : public Viewer
{
public:
    ViewerEtudiant();

    int init();
    int render();
    int quit();
    int update( const float time, const float delta );

protected:

    Image m_terrainAlti;

    
    /// Declaration des Mesh
     Mesh m_terrain;
     Mesh m_l;
     Mesh cube_nuage;
     Mesh m_cube;
    
    /// Declaration des Textures
    GLuint m_terrain_texture;
    GLuint m_program;
    GLuint m_texture;
    GLuint vao;

    
    
    /// Declaration des fonction de creation de Mesh du type init_votreObjet()
    void init_terrain(const Image& im);
    void init_cube();
    void init_cubeN();

    
    /// Declaration des fonctions draw_votreObjet(const Transform& T)
    void draw_terrain(const Transform &T);
    void draw_cube(const Transform &T);
    void draw_cubeN(const Transform &T);

    
};



#endif