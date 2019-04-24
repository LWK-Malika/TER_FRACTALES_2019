//compiler avec g++ graphique.cpp -o graphique -lglut -lGLU -lGL
#include "Point.h"
#include "rectangle.h"
#include "gestionTab.h"
#include "suite.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <ctime> //pour calculer le temps du programme
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;


rectangle cadre(-2.15,-1.3,0.55,1.3);  //contient les dimension du repère
rectangle zoom(-2.15,-1.3,0.55,1.3);   //contient les futur dimension lors du zoom "tirer-glisser"
rectangle zoomTmp(0,0,0,0);            //contient les dimension de zoom a l'instant T-1 

rectangle cadreSuite(-2,-2,2,2);


vector< vector<int> > tab;
vector<vector<point> > tabC;



int tabOcc[100]={0};
int couleur=0;

bool Fjulia=false;



int main(int argc, char* argv[]) {
  time_t start, stop;
  start = clock();
  
  glutInit(&argc, argv); 
  

  glutInitWindowSize(800, 800); // taille fenetre
  glutInitDisplayMode(GLUT_RGB); // On travaille en RGB


  

  int win = glutCreateWindow("Fractale de Mandelbrot"); // nomme la fenêtre

 
  

  
  glutIgnoreKeyRepeat(1); // ignore la répétition d'évênement clavier (touche enfoncé)

  
  //gluOrtho2D(xmin, xmax, ymax,ymin);	// zoom du repère
  cadre.resetRepere();
  // glScalef(1,-1,1);
  glutDisplayFunc(Rafraichir); // Callback de la fenêtre

  //glutDisplayFunc(gestionTab::Rafraichir);
  
  //glPointSize(2); //changer taille point

  
  //glutMouseFunc(clique);
  glutMouseFunc(clique);
  
  //glutMotionFunc(carre);
  glutMotionFunc(carre);
 
  
  //evenement clavier basique
  //glutKeyboardFunc(clavier);

  glutKeyboardUpFunc(clavier);

  //evenement touche clavier "spécial"
  //glutSpecialFunc(touche);
	// if (difftime(clock(), t) >= 80000){
  	glutSpecialFunc(touche);
	// }

//glutKeyboardUpFunc(...);
//glutSpecialUpFunc(...);

	
  stop = clock(); 
  cout << "durer de l'affichage de la fractale: " << difftime(stop, start) << " milliseconde"
       <<endl<<" soit "<< difftime(stop, start)/10000<<" seconde"<<endl<<endl; ;


  
  
   int suite = glutCreateWindow("suite de Mandelbrot"); // nomme la fenêtre

   initialise();
  
   glutKeyboardUpFunc(clavierS);
   glutMouseFunc(cliqueS);

   
  glutMainLoop(); //permet un "arret sur image"
}
