#ifndef GestionTab_h
#define GestionTab_h


#include "Point.h"
#include "rectangle.h"
#include <vector>

extern rectangle cadre;
extern rectangle zoom;
extern rectangle zoomTmp;
extern bool Fjulia;
//extern rectangle cadreSuite;

extern std::vector< std::vector<int> > tab;
extern int tabOcc[100];
extern int couleur;
extern std::vector< std::vector<point> > tabC;



double modulo(double itineraire, double occurance);
double distance(int i, int j, int occ);
double distance(double i, double j);
void dessine();
void remplirTabDernierPoint();
void remplirTab();
void completeTab( rectangle aRemplir);
void newTab(int move, int dir);
void occuranceDiv();
void Rafraichir(void);
void clavier(unsigned char key, int x, int y);
void touche(int key, int x, int y);
void clique(int button, int state, int x, int y);
void carre( int x, int y);

#endif
