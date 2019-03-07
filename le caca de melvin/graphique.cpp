
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
/*
  float xmin = -0.7;
  float xmax = -0.5;
  float ymin = -0.7;
  float ymax = -0.5;
*/
double xmin1=0;
double ymin1=0;
double xmax1=0;
double ymax1=0;

void Rafraichir(void) {
  glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique

  // ----------------- Tableaux de pixels (entier correspondant à la couleur) ------------------
  // vector<vector<int>> tab(glutGet(GLUT_WINDOW_WIDTH)); // créer le tableau avec la taille de la fenêtre
 
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
  /*
  float xmin = -0.7;
  float xmax = -0.5;
  float ymin = -0.7;
  float ymax = -0.5;

  */ 


  double tailleX=abs(xmax-xmin);
  double tailleY=abs(ymax-ymin);

  
  cout << "xmin: " << xmin << ", ymin " << ymin << endl;
  cout << "xmax: " << xmax << ", ymax " << ymax << endl;

  
  int tab[800][800];

  for (int i=0 ; i<800 ; i++) {
    for (int j=0 ; j<800 ; j++) {
      tab[i][j] = point::diverge((tailleX / 800) * i + xmin,-((tailleY / 800) * j + ymin));	
    }
  }

  //--------------------- début fonction affiche --------------------
  
  glBegin(GL_POINTS); 	//mode affichage de points


  for(int i=0;i<800;i++){ //double boucle pour parcourir les points étudier
    for(int  j=0;j<800;j++){

      if (tab[i][j]==-1)
	{	
	  glColor3f(0.2, 0.2, 0.2);
	  glVertex2f((tailleX/800)*i+xmin,-((tailleY/800)*j+ymin));
	}
      else
	//glColor3f((1-0.01*tab[i][j]), -pow((0.01*tab[i][j])-0.5,2)+1,(1-0.01*tab[i][j]));
      //glColor3f(-pow((0.01*tab[i][j])+0.25,2)+1, -0.9*pow((0.01*tab[i][j])-0.5,2)+0.5, pow((0.01*tab[i][j])-0.4,2));
      glColor3f(cos(exp(5*(0.01*tab[i][j]))+4),
		cos(exp(5*(0.01*tab[i][j]))+2),
		cos(exp(5*(0.01*tab[i][j]))));
	
      glVertex2f((tailleX/800)*i+xmin,-((tailleY/800)*j+ymin));

    }
  }
  glEnd(); 		       	// Fermer le polygone
  glFlush(); 
  // -----------------------------------------------------------------
}


void inverse(double &min, double &max) {
  if (max < min) {
    double a = min;
    min = max;
    max = a;

  }
}

void testud( int x, int y) {
  double tailleX = abs(xmax - xmin);
  double tailleY = abs(ymax - ymin);

  cout << "la souris bouge avec un bouton appuyer" << endl;
  glBegin(GL_LINES);
  glColor3f(1,1,1);
  glVertex2f(xmin1,ymin1);
  //affiche le point de la position de la souris:
  glVertex2f((tailleX / 800) * x + xmin,-((tailleY/ 800) * y+ ymin));
  glEnd();  	       	// Fermer le polygone
  glFlush();
  cout << "coordonnées en pixel:" << x << ", " << y << endl
       << "coordonnée en par rapport a l'axe "
       << (tailleX / 800) * x + xmin<< "; "
       << -((tailleY / 800) * y + ymin) << endl;
}

void clique (int button, int state, int x, int y){

  switch (button) {
    case GLUT_LEFT_BUTTON:
      double tailleX =abs( xmax - xmin);
      double tailleY = abs(ymax - ymin);
      if(state == GLUT_DOWN) {
	      cout << "coordonnées en pixel:" << x << ", " << y << endl
	        << "coordonnée en par rapport a l'axe "
		   << (tailleX / 800) * x + xmin
		   << "; " << -((tailleY / 800) * y + ymin) << endl;

	      xmin1=(tailleX/800)*x+xmin;
	      ymin1=-((tailleY/800)*y+ymin);
      }
      

      
       if(state == GLUT_UP)	  {

       	cout<<"coordonnées en pixel:"<<x<<", "<<y<<endl
       	    <<"coordonnée par rapport à l'axe "
	    <<(tailleX/800)*x+xmin<<"; "
	    <<-((tailleY/800)*y+ymin)<<endl;
	
       	xmax1=(tailleX/800)*x+xmin;
       	ymax1=-((tailleY/800)*y+ymin);
	
       	inverse(xmin1,xmax1);
       	inverse(ymin1,ymax1);
	
       	xmin=xmin1;
       	ymin=ymin1;
	//	xmax=xmin1+(abs(xmax1-xmin1)+abs(ymax1-ymin1))/2;
	//	ymax=ymin1+(abs(xmax1-xmin1)+abs(ymax1-ymin1))/2;
	ymax=ymax1;
	xmax=xmax1;
       	cout<<endl<<"xmin= "<<xmin<<" xmax= "<<xmax<<" ymin= "<<ymin<<" ymax= "<<ymax<<endl<<endl;

	//glMatrixMode( GL_MODELVIEW );
       	glLoadIdentity();
       	gluOrtho2D(xmin,xmax,ymin,ymax);	      	//zoom du repère

       	Rafraichir(); 		// Callback de la fenêtre


       }
	  break;  
  }
}

int main(int argc, char* argv[]) {
  time_t start, stop;
  start = clock();
  
  glutInit(&argc, argv); 
  glutInitWindowSize(800, 800); // taille fenetre
  glutInitDisplayMode(GLUT_RGB); // On travaille en RGB
  int win = glutCreateWindow("Fractale de Mandelbrot"); // nomme la fenêtre

  gluOrtho2D(xmin, xmax, ymin, ymax);	// zoom du repère  
  glutDisplayFunc(Rafraichir); // Callback de la fenêtre

  //glPointSize(2); //changer taille point

   glutMouseFunc(clique);
  glutMotionFunc(testud);
  
  stop = clock();

  cout << "durer du programme: " << difftime(stop, start) << " milliseconde" << endl;

  glutMainLoop(); //permet un "arret sur image"
}
