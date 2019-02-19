
//compiler avec g++ graphique.cpp -o graphique -lglut -lGLU -lGL
#include "Point.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <ctime> //pour calculer le temps du programme
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

void Rafraichir(void) {
  glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique

  // ----------------- Tableaux de pixels (entier correspondant a la couleur) ------------------
  // vector<vector<int>> tab(glutGet(GLUT_WINDOW_WIDTH)); // creer le tableau avec la taille de la fenetre
  //cout<<"taille fenetre :"<<glutGet(GLUT_WINDOW_WIDTH)<<glutGet(GLUT_WINDOW_HEIGHT)<<endl;
  //innitiallisation du tableau:
  /*
    int** tab=new int*[glutGet(GLUT_WINDOW_WIDTH)];
    for
    tab[i]=new int
    int x=glutGet(GLUT_WINDOW_WIDTH);
    int y=glutGet(GLUT_WINDOW_HEIGHT);
    cout<<x<<"miaou"<<y<<endl;
  */

  // float xmin = -2.15;
  // float xmax = 0.55;
  // float ymin = -1.3;
  // float ymax = 1.3;

  float xmin = -0.7;
  float xmax = -0.5;
  float ymin = -0.7;
  float ymax = -0.5;

  float tailleX = xmax - xmin;
  float tailleY = ymax - ymin;
  
  gluOrtho2D(xmin, xmax, ymin, ymax);	      	//zoom du repere
  
  int tab[800][800];

  for (int i=0 ; i<800 ; i++) {
    for (int j=0 ; j<800 ; j++)
      {
	tab[i][j] = point::diverge((tailleX / 800) * i + xmin, (tailleY / 800) * j + ymin);	
      }
  }

  //--------------------- debut fonction affiche --------------------
  
  glBegin(GL_POINTS); 	//mode affichage de points

  for (int i=0 ; i<800 ; i++) { //double boucle pour parcourir les points etudier
    for (int j=0 ; j<800 ; j++) {
      if (tab[i][j] == -1)
	{	
	  glColor3f(0.2, 0.2, 0.2);
	  glVertex2f((tailleX / 800) * i + xmin, (tailleY / 800) * j + ymin);
	}
      else
	glColor3f(pow((0.001 * tab[i][j]), 1), // Red
		  pow((0.001 * tab[i][j]), 1), // Green
		  pow((0.0001 * tab[i][j]), 1)); // Blue

      	// glColor3f((0.1 * tab[i][j]), // Red
	// 	  1 - (0.01 * tab[i][j]), // Green
	// 	  (0.001 * tab[i][j])); // Blue

	// glColor3f(1 - (0.01 * tab[i][j]), // Red
	// 	  1 - (0.01 * tab[i][j]), // Green
	// 	  1 - (0.01 * tab[i][j])); // Blue
      
      	// glColor3f((0.1 * tab[i][j]), // Red
	// 	  - pow((0.1 * tab[i][j]) - 0.5, 2) + 1, // Green
	// 	  (1 - 0.1 * tab[i][j])); // Blue
	
      glVertex2f((tailleX / 800) * i + xmin, (tailleY / 800) * j + ymin);
    }

    /*    
	  if(point::diverge(a,b))
	  { glColor3f(2.0, 0, 4.0);
	  glVertex2f(a, b);
	  }
	  else
	  {
	  glColor3f(0.2, 0.2, 0.2);
	  glVertex2f(a, b);
	  }
    */
  }
  glEnd(); 		       	// Fermer le polygone
  glFlush(); 
  // -----------------------------------------------------------------

}

int main(int argc, char* argv[]) {
  time_t start, stop;
  start = clock();
  
  glutInit(&argc, argv); 
  glutInitWindowSize(800, 800); //taille fenetre
  glutInitDisplayMode(GLUT_RGB); // On travaille en RGB
  int win = glutCreateWindow("Fractale de Mandelbrot"); //nomme la fenetre
  
  // glClearColor(1, 1, 4, 0); 
  // gluOrtho2D(-2,2,-2,2);	      	// On garde ces coordonnées
  
  glutDisplayFunc(Rafraichir); 		// Callback de la fenêtre

  // glPointSize(2); // changer taille point
  // glColor3f(1.0, 1.0, 1.0);

  /*
  
  // Dessiner des points
  glBegin(GL_POINTS); 	//mode affichage de points

  for(double a=-2;a<2;a=a+0.01){ //double boucle pour parcourir les points étudier
  for(double  b=-2;b<2;b=b+0.01){
  if(point::diverge(a,b))
  { glColor3f(2.0, 0, 4.0);
  glVertex2f(a, b);
  }
  else
  {
  glColor3f(0.2, 0.2, 0.2);
  glVertex2f(a, b);
  }
  }
  }
  // glVertex2i(100, 100); // Coordonnées des trois points
  // glVertex2i(400, 100);
  // glVertex2i(250, 400);

  glEnd(); 		       	// Fermer le polygone
  glFlush(); 			// Dessiner le polygone

  */
  
  stop = clock();

  cout << "durer du programme: " << difftime(stop, start) << " milliseconde" << endl;

  glutMainLoop(); // permet un "arret sur image"
}
