#ifndef GestionTab_h
#define GestionTab_h


#include "Point.h"
#include "rectangle.h"
extern rectangle cadre;
extern std::vector<std::vector<int>> tab;
extern int* tabOcc;
extern int couleur;

class gestionTab{


  static void dessine();

  static void remplirTab();


  
  static void completeTab( rectangle aRemplir);
  static void newTab(int move, int dir);


  
};



#endif
