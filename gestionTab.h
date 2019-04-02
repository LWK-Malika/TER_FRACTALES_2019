#ifndef GestionTab_h
#define GestionTab_h


#include "Point.h"
#include "rectangle.h"
#include <vector>

extern rectangle cadre;
extern std::vector< std::vector<int> > tab;
extern int tabOcc[100];
extern int couleur;

class gestionTab{

 public:

  static double modulo(double itineraire, double occurance);

  static double distance(int i, int j, int occ);
  
  static void dessine();
  static void remplirTab();

  
  static void completeTab( rectangle aRemplir);
  static void newTab(int move, int dir);


  static void occuranceDiv();
  
  static void Rafraichir(void);
};



#endif
