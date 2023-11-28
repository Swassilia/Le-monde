
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
    Image m_terrainAlti;
    Mesh m_terrain;
    

    
    /// Declaration des Mesh
     
     
    
    /// Declaration des Textures
    //Eau 
    Mesh m_surface_Eau;
    GLuint m_terrain_texture;
    GLuint m_program_Eau;


    //terrain
    void init_terrain(const Image& im);
    GLuint m_program_Terrain;
    GLuint m_texture;
    GLuint vertex_buffer;
    GLuint texcoord_buffer;
    GLuint  sampler;
    GLuint Sampler_decor;
    GLuint Sampler_eau;
    //decor
    void init_cube_map_Decor();
    Mesh m_cube_map_decor;
    Image m_Decor;
    Image m_texture_Decor;
    GLuint m_program_decor;


    
    
    /// Declaration des fonction de creation de Mesh du type init_votreObjet()
    

    
    /// Declaration des fonctions draw_votreObjet(const Transform& T)
    void update_Nuage(float time);

    
};



#endif
