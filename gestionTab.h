#ifndef GestionTab_h
#define GestionTab_h


#include "Point.h"
#include "rectangle.h"
#include <vector>

extern rectangle cadre;
extern rectangle zoom;
extern rectangle zoomTmp;

//extern rectangle cadreSuite;

extern std::vector< std::vector<int> > tab;
extern int tabOcc[100];
extern int couleur;
extern std::vector< std::vector<point> > tabC;

class gestionTab{

 public:

  static double modulo(double itineraire, double occurance);

  static double distance(int i, int j, int occ);
  static double distance(double i, double j);
  
  static void dessine();
  static void remplirTab();

  static void remplirTabDernierPoint();
  
  static void completeTab( rectangle aRemplir);
  static void newTab(int move, int dir);


  static void occuranceDiv();
  
  static void Rafraichir(void);

  static void clavier(unsigned char key, int x, int y);

  static void touche(int key, int x, int y);


  static void clique(int button, int state, int x, int y);

  static void carre( int x, int y);

};



#endif
