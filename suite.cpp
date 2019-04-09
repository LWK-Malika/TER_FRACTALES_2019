#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>


#include "gestionTab.h"
#include "rectangle.h"
#include "suite.h"



bool suite::pause=false;



void suite::initialise(){
  pause=false;
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

  glRasterPos2f(-0.05, 1);
  glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '1');
}


void suite::clavier(unsigned char key, int x, int y) // glutKeyboardFunc(clavier);
{
  std::cout << "-> clavier" << std::endl;
  printf(" Touche : %c = %d \n", key, key);
  switch (key) {
    case 32: // touche: [Espace]
      //cout << " [clavier] Rentre dans le case"; plus utile
      pause = !pause;
      break;
    case 13: // touche: [Entrée]
      initialise();   
      break;
  }
}

/*
void divergeS(point c, int a){


  std::cout << "-> diverge" << std::endl;
  //
  double ZnR = 0, ZnI = 0, tmp_ZnR, tmp_ZnI, temporaire;
  float compteur = 0;
  float stop = 300; // nombre d'itération avant l'arrêt
  clock_t depart = clock();
  //

  point Zn(0,0);

  
  if (a == -1) {
    a = rand()%10;
  }

  
  //double module(){
 // return (sqrt(pow(x,2)+pow(y,2)));}
  
  
  
  //while ((c.module()<2) and (compteur < stop)){
  
*/
    



  
