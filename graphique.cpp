
//compiler avec g++ graphique.cpp -o graphique -lglut -lGLU -lGL
#include "Point.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <ctime> //pour calculer le temps du programme

#include <iostream>

int firstPass = 1; // simule le « once » d'Eiffel

void Rafraichir(void){
  glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique

  if (firstPass) {
    glColor3f(1.0, 0, 1.0);  
    firstPass = 0;
  }
  
  // Dessiner un triangle
  glBegin(GL_POLYGON); 	// Commencer un polygone

  glVertex2i(100, 100); // Coordonnées des trois points
  glVertex2i(400, 100);
  glVertex2i(250, 400);

  glEnd(); 		       	// Fermer le polygone
  glFlush(); 			// Dessiner le polygone

}

int main(int argc, char* argv[])
{

  time_t start, stop;
  start =clock();
  
  glutInit(&argc,argv); 
  glutInitWindowSize(800,800); //taille fenetre
  glutInitDisplayMode(GLUT_RGB); 	// On travaille en RGB
  int win = glutCreateWindow("Fractale de Mandelbrot"); //nomme la fenêtre


  
  //  glClearColor(1, 1, 4, 0); 
  gluOrtho2D(0,575,0,575);	      	// On garde ces coordonnées
 //glutDisplayFunc(Rafraichir); 		// Callback de la fenêtre


 //glPointSize(2); //changer taille point
 
  // glColor3f(1.0, 1.0, 1.0);

  //gluLookAt(-200,0,0,0,0,0,0,1,0); //cadrage
 
   // Dessiner des points
  glBegin(GL_POINTS); 	//mode affichage de points


    for(double a=-2.5;a<2.5;a=a+0.01){ //double boucle pour parcourir les points étudier
       for(double  b=-2.5;b<2.5;b=b+0.01){
	 if(point::diverge(a,b))
	   { glColor3f(2.0, 0, 4.0);
	     glVertex2f(a*100+300, b*100+300);
	   }
	 else
	   {
	     glColor3f(0.2, 0.2, 0.2);
	     glVertex2f(a*100+300, b*100+300);
	   }
       }
    }
    // glVertex2i(100, 100); // Coordonnées des trois points
  // glVertex2i(400, 100);
  // glVertex2i(250, 400);

  glEnd(); 		       	// Fermer le polygone
  glFlush(); 			// Dessiner le polygone

  stop =clock();

  std::cout<<"durer du programme: "<<difftime(stop,start)<<" miliseconde"<<std::endl;

  glutMainLoop(); //permet un "arret sur image"
 
}
