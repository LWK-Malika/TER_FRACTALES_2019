#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>


#include "gestionTab.h"
#include "rectangle.h"
#include "suite.h"



void suite::initialise(){
 
  glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique


  glLoadIdentity();
  gluOrtho2D(cadreSuite.getXmin(),cadreSuite.getXmax(),cadreSuite.getYmax(),cadreSuite.getYmin());
  
  glBegin(GL_LINES); // Création du repère
  glColor3f(1, 1, 1);
  // Création du repère
  glVertex2f(-2, 0);
  glVertex2f(2, 0); 
  glVertex2f(0, -2);
  glVertex2f(0, 2);

  glEnd();
  glFlush();
  
  glPointSize(2);

  // Affiche graduation 
  glRasterPos2f(1, 0.025);
  glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '1');

  glRasterPos2f(-0.05, -1);
  glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '1');
}


void suite::clavier(unsigned char key, int x, int y) // glutKeyboardFunc(clavier);
{
  std::cout << "-> clavier" << std::endl;
  printf(" Touche : %c = %d \n", key, key);
  switch (key) {
  case 13: // touche: [Entrée]
    initialise();   
    break;
  case 105: //TOUCHE INFORMATION
    std::cout<< " > [touche i]: affiche l'aide dans le terminal" << std::endl<< std::endl
	     << " > [Clique Gauche]: Affiche la suite" << std::endl 
	     << " > [Clique Droit]: Efface, puis affiche la suite " <<  std::endl 
	     << " > [Entrée]: Efface"<< std::endl
	     << " > [touche Q]: affiche suite prédéfinie" <<  std::endl<<std::endl;
    break;
  case 113:
       double tabl[9][2] = {  // Suites prédéfinies
      {0, 0.6},
      {0.3,0.5},
      {0.2, 0.5},
      {-0.8,0.156},
      {0.577,0.478},
      {-0.7436,0.661746},
      {-0.55,-0.45},
      {-0.745, 0.055},
      {-1.04,-0.245}
      };
      for (int i=0 ; i < 9 ; i++) {
	point c(tabl[i][0],tabl[i][1]);
	diverge(c, i + 1);
	
      }
      break;

  }
}


void suite::diverge(point c, int a){


  std::cout << "-> diverge" << std::endl;
  //

  float compteur = 0;
  float stop = 300; // nombre d'itération avant l'arrêt
  clock_t depart = clock();
  //

  point Zn(0,0); //suite
  point ZnMoins1(0,0); //suite au rang n-1

  
  if (a == -1) {
    a = rand()%10;
  }

  
  while ((c.module()<4) and (compteur < stop)){

    if  (difftime(clock(), depart) >= 8000) { // Vitesse d'affichage
  

      ZnMoins1=Zn;

      //partie reel
      Zn.setX(pow(ZnMoins1.getX(),2) - pow(ZnMoins1.getY(), 2) + c.getX());

      //partie imaginaire
      Zn.setY(2*ZnMoins1.getX()*ZnMoins1.getY()+c.getY());

      //si suite tend vers un point
      if( abs(Zn.module()-ZnMoins1.module())<0.001){
	std::cout << " Arrêt forcé,car la suite tend vers un point" << std::endl;
	compteur = stop;
      }
	
      compteur++;
	
	
      glColor3f(0.15 * a, 0.7, 1 - 0.15 * a);

	
      glBegin(GL_POINTS); // mode affichage de points
      glVertex2f(Zn.getX(), Zn.getY());
	
      glEnd(); 		        
      glFlush(); 
	
      depart = clock();
    }
  }
}

void suite::clique(int button, int state, int x, int y){
  if (state == GLUT_UP) {
    std:: cout << "-> clique" << std::endl;
    //double dx = pixel_to_repere(x), dy = -pixel_to_repere(y);
    point cible(cadreSuite.pixelToRepereX(x),-cadreSuite.pixelToRepereY(y));
    
    std::cout << " Pixel: " << x << ", " << y << std::endl;
    std::cout << " Repère: " << cible.getX() << ", " <<cible.getY() << std::endl;

    if (button == GLUT_RIGHT_BUTTON) { 
      initialise(); 
    }
    diverge(cible, -1);
  }
}
