Eikon Crafters
P2100663 Wassila SAID KARIM 'projet Manager'
P2004503 Nessim MECHICHE 'Executer'


--RESULTAT--

Le projet Le monde (AM5) sert à faire une modélisation 3d dans une fenêtre d'ile(s) au millieu d'un ocean, généré à partir d'image 2d de bruit de Perlin. On peut se déplacer pour visualiser cette modélisation.

--COMMANDE POUR LA CAMERA--

Pour se déplacer nous pouvons utilisé les flèches du clavier et la souris.
Nous pouvons également n'afficher que les vertex sans les faces en utilisant "w".

--COMMENT COMPILER LE PROJET--

Le code est écrit en C++/C et en version 3.30 du language GLSL.
Il se compile sous Linux. 
Utilise GLSL comme librairie graphique.

Generer les images : 

( être dans eikon-crafters/gkit2light/tools/images )

mkdir -p obj
mkdir -p bin

make bruit
bin/bruit


Compilation du projet : 

( être dans eikon-crafters/gkit2light/build )

make

(être dans eikon-crafters/gkit2light )

bin/l2_lifgfx


--ORGANISATION DES FICHIERS-- 

Le répertoire src contient les fichier important de .cpp et .h pour la modélisation et la mise en place du programme.

Le répertoire bin contient les reccources pour l'exécution ainsi que les exécutables du projet.

Le répertoire data contient les objets, images et shaders utilisé par le programme.

Le répertoire tools contient un sous programme utilitaire permettant de généré les images de Perlin.

Le répertoire build contient le makefile pour compiler le projet.

Le répertoire premake qui permet la compilation.

--CODE--
La classe Viewer_etudiant dans Viewer_etudiant.cpp sert à la modélisation de l'objet et l'initialisation des uniformes (variable utilisé dans le programme shader) . 
Dans un premier temps nous écrivons une fonction qui paramètre le Mesh: normal , vertex et coordonnées de texture. Cette fonction sera appelée dans ```init();``` dans la quelle on préparera également les images, la texture et les programmes shader que nous utiliserons. 
Par la suite nous irons dans ```Draw();```  pour paramètrer les uniformes ainsi que le nombre de vertex et le dessine avec ```Nom_Mesh.draw(m_nom_programme, bool position, bool texcoo, bool normal, bool couleur) ;``` . Nous déciderons ici si nous utiliserons la position, la texture...

Le Shader Surface_Eau.glsl dans data/shaders sert a l'affichage de notre objet dans le monde.
Dans le bloc vertex shader nous utilisons la position et la Matrice Modele \* vue \* projection qui nous permet l'affichage en fonction de la fenetre et de la camera. C'est dans ce bloc que nous pouvons mettre en movement les vertex.
Dans le bloc fragment shader, nous gerons la reaction a la lumiere, la couleur et la texture de notre objet. 
