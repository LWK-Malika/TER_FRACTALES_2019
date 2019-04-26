#include "Point.h"
#include "rectangle.h"
#include "gestionTab.h"
#include "suite.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <ctime> // Pour faire des calculs temporels
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

// Classes et variables globales
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

  // Initialisation de Opengl
  glutInit(&argc, argv); 
  glutInitWindowSize(800, 800); // taille fenetre
  glutInitDisplayMode(GLUT_RGB); // On travaille en RGB

  // Création de la fenêtre
  int win = glutCreateWindow("Fractale de Mandelbrot"); // Nomme la fenêtre
  
  glutIgnoreKeyRepeat(1); // Ignore la répétition d'évènement clavier (touche enfoncée)

  cadre.resetRepere(); // Appelle de la fonction resetRepere qui met le repère par défaut

  glutDisplayFunc(Rafraichir);  // Evènement de modification de fenêtrage, appelle Rafraichir

  glutMouseFunc(clique);  // Evènement clique souris/mollette, appelle la fonction clique

  glutMotionFunc(carre);  // Evènement tirer-glisser, appelle la fonction carre

  glutKeyboardUpFunc(clavier);  // Evènement clavier

  glutSpecialFunc(touche);  // Evènement clavier (touche special: touche directionnelle)

  // Estimation du temps d'execution du programme
  stop = clock();  
  cout << "Durée de l'affichage de la fractale : " << difftime(stop, start) << " millisecondes"
    << endl << " soit " << difftime(stop, start) / 10000 << " secondes." << endl << endl;

  // Initialise la deuxième fenêtre
  // (Les fonctions évènement qui suive concernerons uniquement cette fenêtre)
  int suite = glutCreateWindow("suite de Mandelbrot"); // Nomme la fenêtre

  initialise(); // Initialise la fenêtre

  glutKeyboardUpFunc(clavierS); // Evènement touche clavier

  glutMouseFunc(cliqueS);  // Evènement souris
  
  glutMainLoop(); // Permet un "arret sur image"
}