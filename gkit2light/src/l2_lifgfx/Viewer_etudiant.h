
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
    GLuint vao;
    GLuint  sampler;
    vec3 lightCol;//couleur de la lumiere
    

     
     
    
    /// Declaration des Textures
    //Eau 
    Mesh m_surface_Eau;
    Image m_surface_Alti;
    GLuint m_surface_texture;
    GLuint m_program_Eau;


    //terrain
    void init_terrain(const Image& im,Mesh &m_terrain);
    Image m_terrainAlti;
    GLuint m_terrain_texture;
    GLuint m_program_Terrain;
    GLuint m_texture;
    Mesh m_terrain;


    //decor
    void init_cube_map_Decor();
    Mesh m_cube_map_decor;
    Image m_Decor;
    GLuint m_texture_Decor;
    GLuint m_program_decor;


    
    
    /// Declaration des fonction de creation de Mesh du type init_votreObjet()
    

    
    /// Declaration des fonctions draw_votreObjet(const Transform& T)
    void update_Nuage(float time);

    
};



#endif
