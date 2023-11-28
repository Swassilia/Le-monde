/**
* @brief module permetant de gerer une image 
* @file Image.h
* @date 2023/02/13
*/

#include "Pixel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#ifndef _PIXEL

#endif // _PIXEL
using namespace std;

/**
 *@brief Une Image est composé d'un tableau de reference vers des Pixel et d'une dimension x et y, des entier positifs
*/

class Image
{
     private:
          Pixel * tab; // le tableau de 1D de pixel
          unsigned int dimx, dimy;// les dimensions de l'image
       
     /**
      *@brief procedure permetant l'initialisation d'une fenetre sans bug
     */
          void afficherInit(SDL_Window *& fenetre, SDL_Renderer *& moteur, SDL_Surface *& m_surface , SDL_Texture *& m_texture, SDL_Rect & rectangle);

     /**
      *@brief procedure permetant le rafraichissement de la fenetre par une autre image
     */
          void afficherBoucle(SDL_Renderer * moteur, SDL_Surface * m_surface, SDL_Texture * m_texture, SDL_Rect & rec);

     /**
      *@brief procedure permetant la destruction d'une fenetre et de la bonne liberation en mémoire
     */
          void afficherDetruit(SDL_Window * fenetre,SDL_Renderer * moteur, SDL_Surface * m_surface, SDL_Texture * m_texture);

    public:
    /**
     *@brief constructeur par defaut, initialise une image de taille 0*0 avec un tableau pointant vers rien
    */
     // Constructeur par défaut de la classe: initialise dimx et dimy à 0
     // ce constructeur n'alloue pas de pixel

        Image ();
     /**
      *@brief constructeur d'une image de taille X*Y de couleur noir sur le tas
      *@param[in] dimensionX : entier positif
      *@param[in] dimensionY : entier positif
     */
   // Constructeur de la classe: initialise dimx et dimy (après vérification)
   // puis alloue le tableau de pixel dans le tas (image noire)
        Image (const unsigned int dimensionX,const unsigned int dimensionY);

     /**
      *@brief destructeur par defaut , qui va mettre a jour les dimensions de l'image a 0*0 et désallouer la mémoire du tableau
     */
   // Destructeur de la classe: déallocation de la mémoire du tableau de pixels
   // et mise à jour des champs dimx et dimy à 0
        ~ Image ();

     /**
      *@brief fonction get: pour afficher le pixel de coordonnées (x,y) du tableau 
      *@param[in] x : entier positif
      *@param[in] y : entier positif
      *@return un pixel non modifiable
     */
   // Accesseur : récupère le pixel original de coordonnées (x,y) en vérifiant leur validité
   // la formule pour passer d'un tab 2D à un tab 1D est tab[y*dimx+x]
          Pixel& getPix (const unsigned int x,const unsigned int y) const;

     

     /**
      *@brief procedure set: pour modifier un pixel de coordonnées (x,y) du tableau
      *@param[in] x : entier positif
      *@param[in] y : entier positif
      *@param[in] couleur : Un pixel
     */
   // Mutateur : modifie le pixel de coordonnées (x,y)
          void setPix (const unsigned int x,const unsigned int y,const Pixel & couleur)const ;

     /**
      *@brief procedure qui dessine un rectangle de pixel de la couleur passer en parametre sur une image
      *@param[in] Xmin : entier positif
      *@param[in] Ymin : entier positif
      *@param[in] Xmax : entier positif
      *@param[in] Ymax : entier positif
      *@param[in] couleur : Un pixel 
     */
   // Dessine un rectangle plein de la couleur dans l'image (en utilisant setPix, indices en paramètre compris)
   //Procédure dessinerRectangle (Xmin,Ymin,Xmax,Ymax : donnée entier; couleur : donnée Pixel)
          void dessinerRectangle(const unsigned int Xmin,const unsigned int Ymin,const unsigned int Xmax, const unsigned int Ymax,const Pixel couleur);

     /**
      *@brief procedure remplacant une image par la couleur passé en paramètre
      *@param[in] couleur : Un pixel 
     */
   // Efface l'image en la remplissant de la couleur en paramètre
   // (en appelant dessinerRectangle avec le bon rectangle)
   //Procédure effacer (couleur : donnée Pixel)
          void effacer(const Pixel couleur);
     /**
      *@brief procedure qui effectue une serie de test plus tordus les un que les autres pour être sur que le programme fonctionne bien 
     */
   // Effectue une série de tests vérifiant que le module fonctionne et
   // que les données membres de l'objet sont conformes
          void testRegression () const;

	/** 
	 *@brief procedure permetant de sauvegarder une image dans un fichier dans le repertoire data
      *@param[in/out] filename : chaîne de caractère represantant un chemin vers un fichier
	*/
          void sauver(const string & filename) const ;
	
     /**
      *@brief procedure permetant d'ouvrir un fichier represantant une image
      *@param[in/out] filename : chaîne de caractère represantant un chemin vers un fichier
     */
          void ouvrir(const string & filename);




     /**
     @brief procedure el no sabe  
     @bug a finir ? 
     */
          void afficherConsole()const;



     /**
      *@brief procedure permetant l'affichage, le rafraichissement et la destruction d'une fenetre composé d'une Image
     */
          void afficher();
     /**
     @brief remplissage d'une image de pixel blanc gris ou noir.
     */
          void bruit();

          const Pixel getPixel(float a, float b) const;

          void aggrandissement( const Image& image_a_aggrandir);

          void ovale();

          void ovaleInv();

          void inverser();
     /* 
     @brief permet de copier en aggrandissant une image en format 1024 
     */
     /*
     void format(const Image im_a_copier,const unsigned int taille_ima_init);

     void interpolation(const int multiple, const unsigned int taille);

     void interpolation_ligne(Pixel tab[],const int mult);

     void interpolation_colonne(Pixel tabl[], const int mult);

     void interpolation_centre(const int mult);
     /**
     @brief permet la concatenation de 3 images dans son image
     */
     void concat(const Image& im1, const Image& im2, const Image& im3, const Image& im4);
 
 };
