#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

//#include <stdio.h>
//#include <string.h>

using namespace std;

bool pause = false;

struct Complexe {
  double r;
  double i;
}; typedef struct Complexe Complexe;

void clavier(unsigned char key, int x, int y)  // glutKeyboardFunc(clavier);
{
  printf("Touche : %c = %d \n", key, key);
  switch (key) {
    case 32 :
      cout << "rentre dans le case";
      pause = !pause;
      break;
  }
}

/* Créer une fonction qui affiche une suite aux coordonnée du clique souris

void clique (int button, int state, int x, int y) {


      cout << "coordonnées en pixel:" << x << ", " << y << endl
	   << "coordonnée en par rapport a l'axe " << (tailleX / 800) * x + xmin
	   << "; " << (tailleY / 800) * y + ymin << endl;

      xmin1=(tailleX/800)*x+xmin;
      ymin1=((tailleY/800)*y+ymin);
    }
  glutMouseFunc(clique);

  */

void diverge(double r, double i, int a) 
{
  double ZnR = 0;
  double tmp_ZnR;
  double ZnI = 0;
  double tmp_ZnI;
  double temporaire;
  float cmp = 0;
  clock_t depart = clock();

  // glBegin(GL_LINE_STRIP); // mode affichage de lignes
  
  while ((sqrt(pow(ZnR, 2) + pow(ZnI, 2)) < 2) and (cmp < 110)) {

    // glutKeyboardFunc(clavier);   

    if (!pause && difftime(clock(), depart) >= 30000) {
      glBegin(GL_POINTS); // mode affichage de points  
      temporaire = ZnR;
    
      tmp_ZnR = ZnR;
      tmp_ZnI = ZnI;

      ZnR = pow(ZnR, 2) - pow(ZnI, 2) + r;    
      ZnI = 2 * temporaire * ZnI + i;

      if (abs(tmp_ZnR - ZnR) < 0.000001 && abs(tmp_ZnI - ZnI) < 0.000001) {
        cout << "rentre dans la boucle d'arrêt" << endl;
        cmp = 110;
      }

      cmp++;
      cout << " ZnR =" << ZnR << " ZnI =" << ZnI << endl;
   
      glColor3f(0.15 * a, 0.7, 1 - 0.15 * a);
    
      glVertex2f(ZnR, ZnI);

      glEnd(); 		        
      glFlush(); 
    
      depart = clock();
    }
  }

  if (cmp < 50) {
    cout << "la fonction diverge à partir de n = "<< cmp << endl;
  } else {
    cout << "la fonction converge" << endl;
  }
}

int main(int argc, char** argv) 
{
  if (argc != 3) { // Le programme s'arrête si on ne rentre pas le bon nombre de paramètres
    cerr << " Nombre de paramètre incorrect." << endl;
    cout << " Rentrez par exemple : ./main 0.1 0.5" << endl;
    return -1;
  }

  int a; 
  int win;

  Complexe c; 
  c.r = atof(argv[1]);
  c.i = atof(argv[2]);

  float xmin = -2;
  float xmax = 2;
  float ymin = -2;
  float ymax = 2;
  
  float tailleX = xmax - xmin;
  float tailleY = ymax - ymin;

  // cout << "Entrez le nombre complexe : ";
  // cin >> r;
  // cin >> i;
  cout << "Le nombre complexe entré est : " << c.r << " + i" << c.i << "" << endl;
  cout << "Voulez-vous aussi afficher les suites préféfinies ?" << endl 
    << "Tapez '1' pour oui et '0' pour non : ";
  cin >> a;

  glutInit(&argc, argv); 
  glutInitWindowSize(800, 800); // Taille de la fenêtre
  glutInitDisplayMode(GLUT_RGB); 	// On travaille en RGB
  win = glutCreateWindow("Fractale "); // On nomme la fenêtre
  
  gluOrtho2D(xmin, xmax, ymin, ymax);	// Zoom du repère

  glBegin(GL_LINES); // Création du repère

  glutKeyboardFunc(clavier);  

  glColor3f(1, 1, 1);
  //création du repère
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

  diverge(c.r, c.i, 1);

  // Suites prédéfinies
  double tab[7][2] = {  
    {0, 0.6},
		{0.3,0.5},
    {0.2, 0.5},
		{-0.8,0.156},
		{0.577,0.478},
		{-0.7436,0.661746},
		{-0.55,-0.45} 
  };

  if (a) {
    for (int i=0 ; i < 6 ; i++) {
      diverge(tab[i][0], tab[i][1], i + 1);
    }
  }

  glutMainLoop(); // Permet un "arrêt sur image"
}
