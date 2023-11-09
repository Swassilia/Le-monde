/**
* @brief Module gerant un pixel 
* @file Pixel.h
* @date 2023/02/13
 */

#include <iostream>

using namespace std;


/** 
 * @brief un Pixel est composé de 3 entiers compris entre 0 et 255.
*/
//	un Pixel est composé de 3 entiers compris entre 0 et 255.
class Pixel
{
	private :
		unsigned char r,g,b; // des entiers

	public :
	
	/**
	 * @brief Constructeur par défaut de la classe : initialise le pixel à la couleur noire
	*/
	//	Constructeur par défaut de la classe : initialise le pixel à la couleur noire
	Pixel ();

	/**
	@brief 
	Constructeur de la classe: initialise r,g,b avec les paramètres
	 * @param[in] nb : la quantité de couleur rouge
	 * @param[in] ng : la quantité de couleur verte
	 * @param[in] nb : la quantité de couleur bleue 
	*/
	//	Constructeur de la classe: initialise r,g,b avec les paramètres
	Pixel (const unsigned char nr,const unsigned char ng,const unsigned char nb);


	/**
	 * @brief
	 Accesseur : récupère la composante rouge du pixel
	 * @return : retourne la valeur rouge du pixel
	 */
	//	Accesseur : récupère la composante rouge du pixel
    const unsigned char getRouge()const;



   	/**
   	 * @brief 
   	Accesseur : récupère la composante verte du pixel
   	 * @return : retourne la valeur verte du pixel
   	*/
    //	Accesseur : récupère la composante verte du pixel
    const unsigned char getVert()const;


	/**
	 * @brief 
	Accesseur : récupère la composante bleue du pixel
	 * @return : retourne la valeur bleue du pixel
	*/
	//	Accesseur : récupère la composante bleue du pixel
    const unsigned char getBleu()const;

	/**
	 * @brief
	Mutateur : modifie la composante rouge du pixel
	 * @param[in] : nr une valeur pour le rouge
	*/
	//	Mutateur : modifie la composante rouge du pixel
	void setRouge(const unsigned char nr);

	/**
	 * @brief
	Mutateur : modifie la composante verte du pixel
	 * @param[in] : ng une valeur pour le vert
	*/
	// 	Mutateur : modifie la composante verte du pixel
	void setVert(const unsigned char ng);

	/** 
	 * @brief
	Mutateur : modifie la composante bleue du pixel
	 * @param[in] : nb une valeur pour le bleu
	*/
	//	Mutateur : modifie la composante bleue du pixel
	void setBleu(const unsigned char nb);

};


/** @mainpage
 * 
 * 
 * Module_Image pour LIFAPCD 

 * Le module image sert à génerer des images et à les afficher dans une fenêtre SDL2. Il permet aussi à inclure des 
 images et à les afficher. Grâce à la librairie SDL2 on peut effectuer des actions sur l'image, on peut zoomer en appuyant sur la touche G et dézoomer en appuyant sur 
 la touche T. 
 * 
 * Le code est écrit en C++.
 * Il peut se compiler sous Linux.
 * La librairie graphique utilisée est SDL2.


 * -----> L'organisation des fichiers 

 * Le répertoire src sert à mettre tous les fichiers .cpp et .h
 * Fichiers contenus dans le répertoire src : 
 * Image.cpp Image.h Pixel.cpp Pixel.h mainAffichage.cpp mainExemple.cpp mainTest.cpp

 * Le répertoire obj sert à mettre tous les fichiers .o. Le Makefile permet de supprimer son contenu. 

 * Le répertoire doc sert à mettre notre répertoire html et le fichier image.doxy, pour générer notre documentation, génerer avec doxygen.

 * Le répertoire bin sert à mettre les executables affichage, exemple et test.


 * -----> Le code

 * La classe Pixel dans Pixel.cpp sert à créer un pixel de couleur (RGB).

 * La classe Image dans Image.cpp sert à créer une image de pixel. 
 
 * Le fichier mainAffichage.cpp sert à afficher dans une fenêtre SDL2 une image :
 * 
 * Appuyer sur G pour zoomer.
 * 
 * Appuyer sur T pour dézoomer.
 * 
 * Appuyer sur Escape ou la croix pour fermer la fenêtre.

 * Le fichier mainTest.cpp sert à effectuer le test de regresssion de toutes les fonctions de Image.cpp.
 
 * Le fichier mainExemple.cpp sert à générer deux images image1.ppm image2.ppm.

 * -----> Commandes Linux

 * make all : permet de compiler l'ensemble des fichiers

 * make clean : permet de supprimer les fichiers indiqués dans le makefile
 * 
 * ./bin/affichage : permet d'exécuter le mainAffichage.cpp
 * 
 * ./bin/test : permet d'exécuter le mainTest.cpp
 * 
 * ./bin/exemple : permet d'exécuter le mainExemple.cpp


 * 
*/