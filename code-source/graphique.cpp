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


  //initialisation de opengl
  glutInit(&argc, argv); 
  glutInitWindowSize(800, 800); // taille fenetre
  glutInitDisplayMode(GLUT_RGB); // On travaille en RGB

  //créastion de la fenetre
  int win = glutCreateWindow("Fractale de Mandelbrot"); // nomme la fenêtre
  
  glutIgnoreKeyRepeat(1); // ignore la répétition d'évênement clavier (touche enfoncé)

  //appelle de la fonction resetRepere qui met le repère par défaut
  cadre.resetRepere();

  // evenement de modification de fenetrage, appelle Rafraichir
  glutDisplayFunc(Rafraichir);

  //evenement clique souris/mollette, appelle la fonction clique
  glutMouseFunc(clique);

  //evenement tirer-glisser, appelle la fonction carre
  glutMotionFunc(carre);

  //evenement clavier
  glutKeyboardUpFunc(clavier);
  //evenement clavier (touche special: touche directionnelle)
  glutSpecialFunc(touche);

  stop = clock();
  //permet d'avoir une estime du temps d'execution du programme
  cout << "Durée de l'affichage de la fractale : " << difftime(stop, start) << " millisecondes"
    << endl << " soit " << difftime(stop, start) / 10000 << " secondes." << endl << endl;

  //initialise la deuxieme fenetre
  //les fonction evenement qui suivent concernerons uniquement cette fenetre
  int suite = glutCreateWindow("suite de Mandelbrot"); // nomme la fenêtre

  //initialise la fenetre
  initialise();

  //evenement touche clavier
  glutKeyboardUpFunc(clavierS);
  //evenement souris
  glutMouseFunc(cliqueS);
  
  glutMainLoop(); // Permet un "arret sur image"
}
