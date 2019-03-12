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

double xmin=-2.15;
double xmax=0.55;
double ymin=-1.3;
double ymax=1.3;
double tailleX=abs(xmax-xmin);
double tailleY=abs(ymax-ymin);
vector< vector<int> > tab;

void Rafraichir(void){
  glClear(GL_COLOR_BUFFER_BIT);
	
  for (int i=0 ; i<800 ; i++) {
  	tab.push_back(vector<int>(0));
    for (int j=0 ; j<800 ; j++) {
	    tab[i].push_back(point::diverge((tailleX / 800) * i + xmin, (tailleY / 800) * j + ymin));	
    }
  }

  glBegin(GL_POINTS); 	//mode affichage de points


  for(int i=0;i<800;i++){ //double boucle pour parcourir les points étudier
    for(int  j=0;j<800;j++){

      if (tab[i][j]==-1)
	{	
	  glColor3f(0.2, 0.2, 0.2);	 
	}
      else{
		glColor3f(cos(exp(5*(0.01*tab[i][j]))+4),
		cos(exp(5*(0.01*tab[i][j]))+2),
		cos(exp(5*(0.01*tab[i][j]))));
	}
	glVertex2f((tailleX/800)*i+xmin,(tailleY/800)*j+ymin);
    }
  }
  glEnd(); 		       	// Fermer le polygone
  glFlush(); 

  glBegin(GL_LINES);
  glColor3f(1,1,1);
  glVertex2f(0, 0);
  glVertex2f(0, 1);
  glEnd();
  glFlush();

  glBegin(GL_LINES);
  glColor3f(1,1,1);
  glVertex2f(0, 0);
  glVertex2f(1, 0);
  glEnd();
  glFlush();
}

void clique (int button, int state, int x, int y){
	switch(button){
		case 4:		
			if (state == GLUT_DOWN){
				xmin=xmin*1.1;
    			xmax=xmax*1.1;
    			ymin=ymin*1.1;
    			ymax=ymax*1.1;
    			glLoadIdentity();
    			gluOrtho2D(xmin,xmax,ymax, ymin);	
    			Rafraichir();
    		}
    		break;
    	 case 3: //roulette vers le haut
    		if (state == GLUT_DOWN){ 
    			xmin=xmin*0.9;
    			xmax=xmax*0.9;
    			ymin=ymin*0.9;
    			ymax=ymax*0.9;
    			glLoadIdentity();
    			gluOrtho2D(xmin,xmax,ymax,ymin);	      	//zoom du repère
    			Rafraichir(); 		// Callback de la fenêtre
     }
    break;
	}
}

void carre(int x, int y){
	float tailleX = abs(xmax - xmin);
  	float tailleY = abs(ymax - ymin);
}

int main(int argc, char *argv[])
{
	time_t start, stop;
 	start = clock();

	glutInit(&argc, argv); 
	glutInitWindowSize(800, 800); // taille fenetre
	glutInitDisplayMode(GLUT_RGB); // On travaille en RGB
 	int win = glutCreateWindow("Fractale de Mandelbrot");

 	gluOrtho2D(xmin, xmax, ymin, ymax);
	/* code */
 	glutDisplayFunc(Rafraichir);
 	glutMouseFunc(clique);

	stop = clock();
	cout << "durer du programme: " << difftime(stop, start) << " milliseconde" << endl;
	glutMainLoop();

	return 0;
}