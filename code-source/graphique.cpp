#include "Point.h"
#include "rectangle.h"
#include "gestionTab.h"
#include "suite.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <ctime> // Pour faire des calcules temporels
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

rectangle cadre(-2.15, -1.3, 0.55, 1.3); // Contient les dimensions du repère pour Mandelbrot et Julia
rectangle zoom(-2.15, -1.3, 0.55, 1.3); // Contient les futurs dimensions lors du zoom "tirer-glisser"
rectangle zoomTmp(0, 0, 0, 0); // Contient les dimensions du zoom à l'instant T-1 
rectangle cadreSuite(-2,-2,2,2); // Contient les dimensions du repère pour l'animation de suites de Mandelbrot

vector<vector<int>> tab;
vector<vector<point>> tabC;

int tabOcc[100] = {0};
int couleur = 0;

bool Fjulia = false;

int main(int argc, char* argv[]) 
{
  time_t start, stop;
  start = clock();
  
  glutInit(&argc, argv); 
  glutInitWindowSize(800, 800); // taille fenetre
  glutInitDisplayMode(GLUT_RGB); // On travaille en RGB

  int win = glutCreateWindow("Fractale de Mandelbrot"); // nomme la fenêtre
  
  glutIgnoreKeyRepeat(1); // ignore la répétition d'évênement clavier (touche enfoncé)

  cadre.resetRepere();

  glutDisplayFunc(Rafraichir); // Callback de la fenêtre
  glutMouseFunc(clique);
  glutMotionFunc(carre);
  glutKeyboardUpFunc(clavier);
  glutSpecialFunc(touche);

  stop = clock(); 
  cout << "Durée de l'affichage de la fractale : " << difftime(stop, start) << " millisecondes"
    << endl << " soit " << difftime(stop, start) / 10000 << " secondes." << endl << endl;

  int suite = glutCreateWindow("suite de Mandelbrot"); // nomme la fenêtre

  initialise();
  
  glutKeyboardUpFunc(clavierS);
  glutMouseFunc(cliqueS); 
  glutMainLoop(); // Permet un "arret sur image"
}
