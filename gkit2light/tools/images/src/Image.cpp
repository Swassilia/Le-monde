#include "Image.h"
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

Image::Image() {
  dimx = 0;
  dimy = 0;
  tab = nullptr;
}

Image::Image(const unsigned int dimensionX, const unsigned int dimensionY) {
  dimx = dimensionX;
  dimy = dimensionY;
  tab = new Pixel[dimensionX * dimensionY];
}

Image::~Image() {
  dimx = 0;
  dimy = 0;
  if (tab != nullptr) {
    delete[] tab;
    tab = nullptr;
  }
}


const Pixel Image::getPixel(float x, float y) const {
    assert( x>=0.f);
    assert( y>=0.f);
    assert( x<=1.f);
    assert( y<=1.f);
    float x_R = x*(dimx-1); // convertie le pourcentage en une case (0.92% x d'une image taille 16 est la "case" 13.8)
    float y_R = y*(dimy-1); //same (0.5 y d'une image 7.5)
    //std::cout<<endl<<"x_R = "<<x_R<<"   y_R = "<<y_R<<endl;
    int x_partie_entiere = (int) x_R; // va recuperer la partie entière de l'image (13.8 -> 13)
    int y_partie_entiere = (int) y_R;

    float point_A, point_B, point_C, point_D;
    point_A=getPix(x_partie_entiere,y_partie_entiere).getBleu(); //recupere les vrais pixels autours

    if (y_partie_entiere>=dimy-1) 
      point_B = point_A;
    else
      point_B=getPix(x_partie_entiere,y_partie_entiere+1).getBleu();


    if (x_partie_entiere>=dimx-1 || y_partie_entiere>=dimy-1) 
      point_C = point_A;
    else
      point_C=getPix(x_partie_entiere+1,y_partie_entiere+1).getBleu();


    if (x_partie_entiere>=dimx-1) 
      point_D = point_A;
    else
      point_D=getPix(x_partie_entiere+1,y_partie_entiere).getBleu();

    
    float x_partie_quotien = x_R - (float) x_partie_entiere; //on recupere la virgule pour faire les futures interpolations
    float y_partie_quotien = y_R - (float) y_partie_entiere; // par ex (13.8 -> 0.8) et 0.5

    //cout<<"x_R="<<x_R<<" x_I="<<x_partie_entiere<<"    Pixel=";
    //cout<<point_A<<" "<<point_B<<" "<<point_C<<" "<<point_D<<endl;

    float point_E = point_D*x_partie_quotien + point_A*(1-x_partie_quotien);//interpolation vertical
    float point_F = point_C*x_partie_quotien + point_B*(1-x_partie_quotien); // 50% C 50% B 

    float valeur_inter = point_F*y_partie_quotien + point_E*(1-y_partie_quotien); // 80% de F et 20 de E 
    return Pixel((unsigned char)valeur_inter,(unsigned char)valeur_inter,(unsigned char)valeur_inter);
}



void Image::aggrandissement(const Image& im){
  Image copier(dimx,dimy);
  int i,j;
  for(i=0;i<dimx;i=i+1){
        //std::cout<<endl;
    for(j=0;j<dimy;j=j+1){
        //std::cout<<i<<" : "<<j<<"   :"<<(int)im.getPixel(i/(float)dimx,j/(float)dimy).getBleu()<<endl;
        
        //setPix(i,j,im.getPixel(i/(float)dimx,j/(float)dimy));
        copier.setPix(i,j,im.getPixel( float(i)/(dimx-1),  float(j)/(dimy-1)) );
    }
  }
  for(i=0;i<dimx;i=i+1){
    for(j=0;j<dimy;j=j+1){
        //std::cout<<i<<" : "<<j<<"   :"<<im.getPixel(i/(float)dimx,j/(float)dimy).getBleu()<<endl;
        
        //setPix(i,j,im.getPixel(i/(float)dimx,j/(float)dimy));
        setPix(i,j,copier.getPix(i,j));
    }
  }
  
}

void Image::bruit() {
  int val_al;
  Pixel blanc(255, 255, 255);
  Pixel gris(169, 169, 169);
  Pixel noir(1, 1, 1);
  for (unsigned int i = 0; i < dimx; i++) {
    for (unsigned int j = 0; j < dimy; j++) {
      val_al = rand() % 254 + 1;
      if (val_al < 50) {
        setPix(i, j, blanc);
      }
      if ((val_al > 100) && (val_al < 150)) {
        setPix(i, j, gris);
      } else {
        setPix(i, j, Pixel(val_al, val_al, val_al));
    }
    }
  }
}
/*

void Image::interpolation_ligne(Pixel tabl[], const int mult) {
  float point_A;
  float point_B;
  float alpha;
  for (unsigned int i = 0; i < dimx; i = i + mult) {
    for (unsigned int j = 0; j < dimy; j = j + mult) {
      point_A = tabl[i * dimx + j].getRouge();
      if (i * dimx + j + mult > dimx * dimx) {
        point_B = tabl[i * dimx + 0].getRouge();
      } else {
        point_B = tabl[i * dimx + j + mult].getRouge();
      }
      for (unsigned int z = 1; z < mult; z++) {
        alpha = point_A * (1.f - (float)z / (float)mult) +
                point_B * (((float)z / (float)mult));
        setPix(i, j + z, Pixel(alpha, alpha, alpha));
      }
    }
  }
}

void Image::interpolation_colonne(Pixel tabl[], const int mult) {
  float point_A;
  float point_B;
  float alpha;
  for (unsigned int i = 0; i < dimx; i = i + mult) {
    for (unsigned int j = 0; j < dimy; j = j + mult) {
      point_A = tabl[i * dimx + j].getRouge();
      if ((i + mult) * dimx + j > dimx * dimx) {
        point_B = tabl[0 + j].getRouge();
      } else {
        point_B = tabl[(i + mult) * dimx + j].getRouge();
      }
      for (unsigned int z = 1; z < mult; z++) {
        alpha = point_A * (1.f - (float)z / (float)mult) +
                point_B * (((float)z / (float)mult));
        setPix(i + z, j, Pixel(alpha, alpha, alpha));
      }
    }
  }
}

void Image::interpolation_centre(const int mult) {
  float point_A;
  float point_B;
  float point_C;
  float point_D;
  float alpha;
  float beta;
  for (unsigned int i = 0; i < dimx; i = i + mult) {
    for (unsigned int j = 0; j < dimy; j = j + mult) {
      for (unsigned int z = 1; z < mult; z++) {
        point_A = tab[i * dimx + j + z].getRouge();
        if ((i + mult) * dimx + j + z > dimx) {
          point_B = tab[j + z].getRouge();
        } else {
          point_B = tab[(i + mult) * dimx + j + z].getRouge();
        }
        for (unsigned int y = 1; y < mult; y++) {
          point_C = tab[(i + y) * dimx + j].getRouge();
          if ((i + y) * dimx + j + mult > dimx) {
            point_D = tab[y * dimx].getRouge();
          } else {
            point_D = tab[(i + y) * dimx + j + mult].getRouge();
          }
          alpha = (point_A * (1.f - ((float)y / (float)mult)) +
                   point_B * ((float)y / (float)mult)) /
                  2.f;
          beta = (point_C * (1.f - ((float)z / (float)mult)) +
                 point_D * ((float)z / (float)mult) )/ 2.f;
          setPix(i + y, j + z,
                 Pixel(((char)alpha + (char)beta), ((char)alpha + (char)beta),
                       ((char)alpha + (char)beta)));
        }
      }
    }
  }
}

void Image::interpolation(const int mult, const unsigned int taille_base) {
  Pixel tabl[dimx * dimy];
  for (unsigned int i = 0; i < dimx; i++) {
    for (unsigned int j = 0; j < dimy; j++) {
      tabl[i * dimx + j] = getPix(i, j);
    }
  }
  interpolation_ligne(tabl, mult);
  interpolation_colonne(tabl, mult);
  interpolation_centre(mult);
  /*Pixel tab[dimx*dimy];
  for(unsigned int i=0;i<dimx;i++){
      for(unsigned int j=0; j<dimy;j++){
          tab[i*dimx + j]=getPix(i,j);
      }
  }
  int moyenne_de_rouge =0;
  int moyenne_de_bleu = 0;
  int moyenne_de_vert =0;
  int compteur=0;
  for(unsigned int x=0;x<dimx;x++){
      for(unsigned int y=0;y<dimy;y++){
          if((x%mult!=0)&&(y%mult!=0)){
              moyenne_de_rouge =0;
              moyenne_de_bleu = 0;
              moyenne_de_vert =0;
              compteur=0;
              for(int u=x-mult;u<(int) x+mult;u++){
                  for(int v=y-mult;v<(int) y+mult;v++){
                      if((u>0)&&(v>0)&&(u<(int) dimx)&&(v<(int)
  dimy)&&(tab[u*dimx+v].getRouge()!=0)){
                          moyenne_de_rouge=moyenne_de_rouge+(int)tab[u*dimx+v].getRouge();
                          moyenne_de_bleu=moyenne_de_bleu+(int)tab[u*dimx+v].getBleu();
                          moyenne_de_vert=moyenne_de_vert+(int)tab[u*dimx+v].getVert();
                          compteur++;
                      }
                  }
              }
              setPix(x,y,Pixel((unsigned
  char)(moyenne_de_rouge/compteur),(unsigned
  char)(moyenne_de_vert/compteur),(unsigned char)(moyenne_de_bleu/compteur)));
          }
      }
  }
}
  


void Image::format(const Image im, const unsigned int taille) {
  int multiple = dimx / taille;
  for (unsigned int i = 0; i < taille; i++) {
    for (unsigned int j = 0; j < taille; j++) {
      setPix(i * multiple, j * multiple, im.getPix(i, j));
    }
  }
  interpolation(multiple, taille);
}
*/
void Image::concat(const Image& im1, const Image& im2, const Image& im3,
                   const Image& im4) {
  for (unsigned int i = 0; i < dimx; i++) {
    for (unsigned int j = 0; j < dimy; j++) {
      unsigned char rouge =
          (unsigned char)(((int)im4.getPix(i, j).getRouge() * 0.50 +
                           (int)im1.getPix(i, j).getRouge() * 0.10 +
                           (int)im2.getPix(i, j).getRouge() * 0.15 +
                           (int)im3.getPix(i, j).getRouge() * 0.25));
      // unsigned char bleu = (unsigned
      // char)(((int)im4.getPix(i,j).getBleu()+(int)im1.getPix(i,j).getBleu()+(int)im2.getPix(i,j).getBleu()+(int)im3.getPix(i,j).getBleu())/4);
      // unsigned char vert = (unsigned
      // char)(((int)im4.getPix(i,j).getVert()+(int)im1.getPix(i,j).getVert()+(int)im2.getPix(i,j).getVert()+(int)im3.getPix(i,j).getVert())/4);
      setPix(i, j, Pixel(rouge, rouge, rouge));
    }
  }
}

Pixel &Image::getPix(const unsigned int x, const unsigned int y) const {
  assert(x < dimx);
  assert(y < dimy);
  return tab[x * dimx + y];
}

void Image::setPix(const unsigned int x, const unsigned int y,
                   const Pixel &couleur) const {
  assert(x >= 0 && y >= 0);
  assert(x < dimx && y < dimy);
  tab[x * dimx + y] = couleur;
}
// erreur de depassement de tableau a corriger + opérateur = couleur a crée
void Image::dessinerRectangle(const unsigned int Xmin, const unsigned int Ymin,
                              const unsigned int Xmax, const unsigned int Ymax,
                              const Pixel couleur) {
  assert(Xmin < dimx);
  assert(Xmin >= 0);
  assert(Xmax < dimx);
  // assert(Xmax>Xmin);
  // assert(Ymin<dimy);
  assert(Ymin >= 0);
  // assert(Ymax<dimy);
  // assert(Ymax<Ymin);
  for (unsigned int i = Xmin; i <= Xmax; ++i) {
    for (unsigned int j = Ymin; j <= Ymax; ++j) {
      setPix(i, j, couleur);
    }
  }
}

void Image::effacer(const Pixel couleur) {
  dessinerRectangle(0, 0, dimx - 1, dimy - 1, couleur);
}

void Image::testRegression() const {
  cout << "---------Test de regression : ------------" << endl;

  cout << "-----> Test pixel avant de passer à image..." << endl;
  // test couleur
  Pixel p1(5, 2, 3);
  cout << "Creation du pixel p1(5,2,3)" << endl;

  // verification du pixel p1
  cout << "Verification des valeurs du pixel p1" << endl;
  assert(p1.getRouge() == 5);
  assert(p1.getVert() == 2);
  assert(p1.getBleu() == 3);

  cout << "C'est ok" << endl;

  cout << endl;
  Pixel p2;
  cout << "Creation du pixel p2 par default (0,0,0)" << endl;
  // pixel p2 par default (0,0,0)
  cout << "verification des valeurs du pixel p2(0,0,0)" << endl;
  assert(p2.getRouge() == 0);
  assert(p2.getVert() == 0);
  assert(p2.getBleu() == 0);
  cout << "C'est ok" << endl;

  cout << endl;

  cout << "-----> Test de regression Image" << endl;
  Image im;
  cout << "Creation de l'image par default im" << endl;
  cout << "Verification des dimensions de im, dimx=0, dimy=0" << endl;
  assert(im.dimx == 0);
  assert(im.dimy == 0);
  cout << "C'est OK" << endl;
  cout << "Verification de im.tab==nullptr" << endl;
  assert(im.tab == nullptr);
  cout << "C'est OK" << endl;

  cout << endl;

  Image im2(64, 128);
  cout << "Creation de l'image im2(64,128)" << endl;
  cout << "Verification des dimensions de l'image im2" << endl;
  assert(im2.dimx == 64);
  assert(im2.dimy == 128);
  cout << "C'est ok" << endl;
  cout << "im2.tab n'est pas égal à nullptr" << endl;
  assert(im2.tab != nullptr);
  cout << "C'est ok" << endl;

  cout << endl;

  cout << "> Test rouge de im2 :" << endl;
  unsigned int j, i;
  cout << "Test si le rouge de im2 est à 0" << endl;
  for (i = 0; i < im2.dimx; i++)
    for (j = 0; j < im2.dimy; j++) {
      assert(
          im2.getPix(i, j).getRouge() ==
          0); // car une image en sortie du constructeur doit être toute noire
    }
  cout << "Le rouge est bien à 0 dans im2" << endl;

  cout << endl;
  cout << "> Test vert de im2 :" << endl;
  cout << "Test si le vert de im2 est à 0" << endl;
  for (i = 0; i < im2.dimx; i++)
    for (j = 0; j < im2.dimy; j++) {
      assert(
          im2.getPix(i, j).getVert() ==
          0); // car une image en sortie du constructeur doit être toute noire
    }
  cout << "Le vert est bien à 0 dans im2" << endl;

  cout << endl;
  cout << "> Test bleu de im2 :" << endl;
  cout << "Test si le bleu de im2 est à 0" << endl;
  for (i = 0; i < im2.dimx; i++)
    for (j = 0; j < im2.dimy; j++) {
      assert(
          im2.getPix(i, j).getBleu() ==
          0); // car une image en sortie du constructeur doit être toute noire
    }
  cout << "Le bleu est bien à 0 dans im2" << endl;

  cout << endl;

  // test image
  unsigned int x = 500;
  unsigned int y = 250;
  Image Im1(x, y);
  cout << "Creation de l'image im1, dimx=500, dimy=250" << endl;
  cout << "verification des dimensions de im1" << endl;
  assert(Im1.dimx == 500);
  assert(Im1.dimy == 250);
  cout << "C'est ok" << endl;

  cout << "Test dessiner rectangle avec la couleur du pixel P1" << endl;
  Im1.dessinerRectangle(40, 40, 50, 50, p1);
  cout << "Rectangle dessiné dans Im1" << endl;
  cout << "test couleur du pixel coordonnee (41,41) de Im1, comparaison avec p1"
       << endl;
  assert(Im1.getPix(41, 41).getRouge() == p1.getRouge());
  assert(Im1.getPix(41, 41).getVert() == p1.getVert());
  assert(Im1.getPix(41, 41).getBleu() == p1.getBleu());
  cout << "C'est ok" << endl;
}

void Image::sauver(const string &filename) const {
  ofstream fichier(filename.c_str());
  assert(fichier.is_open());
  fichier << "P3" << endl;
  fichier << dimx << " " << dimy << endl;
  fichier << "255" << endl;
  for (unsigned int y = 0; y < dimy; ++y)
    for (unsigned int x = 0; x < dimx; ++x) {
      Pixel &pix = getPix(x, y);
      fichier << +pix.getRouge() << " " << +pix.getVert() << " "
              << +pix.getBleu() << " ";
    }
  cout << "Sauvegarde de l'image " << filename << " ... OK\n";
  fichier.close();
}

void Image::ouvrir(const string &filename) {
  ifstream fichier(filename.c_str());
  assert(fichier.is_open());
  int r, g, b;
  string mot;
  // dimx = dimy = 0;
  fichier >> mot >> dimx >> dimy >> mot;
  assert(dimx > 0 && dimy > 0);
  if (tab != NULL)
    delete[] tab;
  tab = new Pixel[dimx * dimy];
  for (unsigned int y = 0; y < dimy; ++y)
    for (unsigned int x = 0; x < dimx; ++x) {
      fichier >> r >> g >> b;
      // getPix(x,y).setRouge(r);
      Pixel c(r, g, b);
      setPix(x, y, c);
      std::cout << r << " " << g << " " << b << std::endl;
      // getPix(x,y).setVert(g);
      // getPix(x,y).setBleu(b);
    }
  fichier.close();
  cout << "Lecture de l'image " << filename << " ... OK\n";
}

void Image::afficherConsole() const {
  cout << dimx << " " << dimy << endl;
  for (unsigned int y = 0; y < dimy; ++y) {
    for (unsigned int x = 0; x < dimx; ++x) {
      Pixel &pix = getPix(x, y);
      cout << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu()
           << " ";
    }
    cout << endl;
  }
}

void Image::afficherInit(SDL_Window *&fenetre, SDL_Renderer *&moteur,
                         SDL_Surface *&m_surface, SDL_Texture *&m_texture,
                         SDL_Rect &rec) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError()
         << endl;
    SDL_Quit();
    exit(1);
  }

  if (TTF_Init() != 0) {
    cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError()
         << endl;
    SDL_Quit();
    exit(1);
  }

  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    cout << "SDL_image could not initialize! SDL_image Error: "
         << IMG_GetError() << endl;
    SDL_Quit();
    exit(1);
  }
  fenetre = SDL_CreateWindow("fenetre_module_image", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 200, 200,
                             SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (fenetre == nullptr) {
    cout << "Erreur lors de l'iniatilisation de la fenetre 01";
    afficherDetruit(fenetre, moteur, m_surface, m_texture);
  }

  moteur = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
  if (moteur == nullptr) {
    cout << "Erreur lors de l'affichage de la fenetre 02";
    afficherDetruit(fenetre, moteur, m_surface, m_texture);
  }

  // SDL_RenderPresent(moteur);
  SDL_SetRenderDrawColor(moteur, 128, 128, 128, 255);
  // SDL_RenderClear(moteur);

  m_surface = IMG_Load("./data/ImageAffichage.ppm");
  if (m_surface == nullptr) {

    string nfn = string("../") + "./data/ImageAffichage.ppm";
    cout << "Error: cannot load "
         << "./data/ImageAffichage.ppm"
         << ". Trying " << nfn << endl;
    m_surface = IMG_Load(nfn.c_str());
    if (m_surface == nullptr) {

      nfn = string("../") + nfn;
      m_surface = IMG_Load(nfn.c_str());
    }
  }
  if (m_surface == nullptr) {

    cout << "Error: cannot load "
         << "./data/ImageAffichage.ppm" << endl;
    exit(1);
  }

  SDL_Surface *surfaceCorrectPixelFormat =
      SDL_ConvertSurfaceFormat(m_surface, SDL_PIXELFORMAT_ARGB8888, 0);
  SDL_FreeSurface(m_surface);
  m_surface = surfaceCorrectPixelFormat;

  m_texture = SDL_CreateTextureFromSurface(moteur, surfaceCorrectPixelFormat);
  if (m_texture == nullptr) {
    cout << "Error: problem to create the texture of "
         << "./data/ImageAffichage.ppm" << endl;
    exit(1);
  }

  if (SDL_QueryTexture(m_texture, nullptr, nullptr, &rec.w, &rec.h) != 0) {
    cout << "Error: problem to memory the texture" << endl;
    exit(1);
  }

  rec.w = 200;
  rec.h = 200;
  rec.x = (200 - rec.h) / 2;
  rec.y = (200 - rec.w) / 2;

  // if(SDL_RenderCopy(moteur,m_texture,nullptr, &rec) !=0 ){

  //     cout<<"Error: probleme lors de l'affichage de l'image dans la
  //     fenetre"<<endl; exit(1);
  // }

  // SDL_RenderPresent(moteur);
}

void Image::afficherBoucle(SDL_Renderer *moteur, SDL_Surface *m_surface,
                           SDL_Texture *m_texture, SDL_Rect &rec) {
  SDL_Event events;
  bool quit = false;

  // tant que ce n'est pas la fin ...
  while (!quit) {

    SDL_RenderClear(moteur);

    // tant qu'il y a des evenements à traiter (cette boucle n'est pas
    // bloquante)
    while (SDL_PollEvent(&events)) {

      if (events.type == SDL_QUIT)
        quit = true; // Si l'utilisateur a clique sur la croix de fermeture
      else if (events.type == SDL_KEYDOWN) {
        switch (events.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
          quit = true;
          break;
        case SDL_SCANCODE_T:
          rec.w = rec.w * 2;
          rec.h = rec.h * 2;
          rec.x = (200 - rec.h) / 2;
          rec.y = (200 - rec.w) / 2;
          // pour verifier la taille du rect. cout<<endl<<"taille du rectangle :
          // "<< rec.w <<" rec.h = "<<rec.h<<endl;

          break;
        case SDL_SCANCODE_G:

          if ((rec.w > 10) && (rec.h > 2)) {
            rec.w = rec.w / 2;
            rec.h -= rec.h / 2;
            rec.x = (200 - rec.h) / 2;
            rec.y = (200 - rec.w) / 2;
          }

          break;
        default:
          break;
        }
      }
    }
    SDL_RenderCopy(moteur, m_texture, nullptr, &rec);
    SDL_RenderPresent(moteur);
  }
}

void Image::afficherDetruit(SDL_Window *fenetre, SDL_Renderer *moteur,
                            SDL_Surface *m_surface, SDL_Texture *m_texture) {
  TTF_Quit();
  SDL_DestroyTexture(m_texture);
  SDL_FreeSurface(m_surface);
  SDL_DestroyRenderer(moteur);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
  moteur = nullptr;
  fenetre = nullptr;
}

void Image::afficher() {

  sauver("./data/ImageAffichage.ppm");
  SDL_Window *m_window = nullptr;
  SDL_Renderer *m_renderer = nullptr;
  SDL_Surface *m_surface = nullptr;
  SDL_Texture *m_texture = nullptr;
  SDL_Rect rectangle;
  afficherInit(m_window, m_renderer, m_surface, m_texture, rectangle);
  afficherBoucle(m_renderer, m_surface, m_texture, rectangle);
  afficherDetruit(m_window, m_renderer, m_surface, m_texture);
}
