#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

/*  TODO LIST
  - Faire durer les suites intéressantes
*/

/* A Améliorer
  - Plus de couleurs (avec le a)
*/

// --- Variables globaux
bool pause = false;

struct Complexe {
  double r, i;
}; typedef struct Complexe Complexe;
// ---

void clavier(unsigned char key, int x, int y) // glutKeyboardFunc(clavier);
{
  printf(" [clavier] Touche : %c = %d \n", key, key);
  switch (key) {
    case 32 :
      //cout << " [clavier] Rentre dans le case"; plus utile
      pause = !pause;
      break;
  }
}

// Convertir des coordonnées en pixel [0, 800] en coordonnée du repère [-2, 2]
double pixel_to_repere(int i) 
{
  double d = (((double)i) / 200) - 2; 
  return d;
}

void diverge(double r, double i, int a) 
{
  double ZnR = 0, ZnI = 0, tmp_ZnR, tmp_ZnI, temporaire;
  float cmp = 0;
  float stop = 130;
  clock_t depart = clock();

  if (a == -1) {
    a = rand()%10;
  }

  // glBegin(GL_LINE_STRIP); // mode affichage de lignes
  
  while ((sqrt(pow(ZnR, 2) + pow(ZnI, 2)) < 2) and (cmp < stop)) {

    // glutKeyboardFunc(clavier);   

    if (!pause && difftime(clock(), depart) >= 10000) {
      glBegin(GL_POINTS); // mode affichage de points  
      temporaire = ZnR;
    
      tmp_ZnR = ZnR;
      tmp_ZnI = ZnI;

      ZnR = pow(ZnR, 2) - pow(ZnI, 2) + r;    
      ZnI = 2 * temporaire * ZnI + i;

      if (abs(tmp_ZnR - ZnR) < 0.000001 && abs(tmp_ZnI - ZnI) < 0.000001) {
        cout << " [diverge] Arrêt forcé, car peu intéressante." << endl;
        cmp = stop;
      }

      cmp++;
      //cout << " ZnR =" << ZnR << " ZnI =" << ZnI << endl; Affiche les coordonnées du point généré
   
      glColor3f(0.15 * a, 0.7, 1 - 0.15 * a);
    
      glVertex2f(ZnR, ZnI);

      glEnd(); 		        
      glFlush(); 
    
      depart = clock();
    }
  }

  if (cmp < 50) {
    cout << " [diverge] Diverge à partir de n = "<< cmp << endl << endl;
  } else {
    cout << " [diverge] Converge" << endl << endl;
  }
}

// Créer une fonction qui affiche une suite aux coordonnée du clique souris
void clique (int button, int state, int x, int y) // A COMPLETER
{
  if (state == GLUT_UP) {
    double dx = pixel_to_repere(x), dy = -pixel_to_repere(y);

    cout << " [clique] Pixel: " << x << ", " << y << endl;
    cout << " [clique] Repère: " << dx << ", " << dy << endl;
    diverge(dx, dy, -1);
  }
}

int main(int argc, char** argv) 
{
  if (argc != 3) { // Le programme s'arrête si on ne rentre pas le bon nombre de paramètres
    cerr << " [main] Nombre de paramètre incorrect." << endl;
    cout << " [main] Rentrez par exemple: ./main -0.74, -0.175" << endl;
    return -1;
  }

  srand (time(NULL));
  int a; 
  int win;

  Complexe c; 
  c.r = atof(argv[1]);
  c.i = atof(argv[2]);

  float xmin = -2, xmax = 2, ymin = -2, ymax = 2;
  float tailleX = xmax - xmin, tailleY = ymax - ymin;

  cout << " [main] Le nombre complexe entré est: " << c.r << " + i" << c.i << "" << endl;
  cout << " [main] Voulez-vous aussi afficher les suites préféfinies ?" << endl 
    << " [main] Tapez '1' pour oui et '0' pour non: " << endl;
  cin >> a;

  glutInit(&argc, argv); 
  glutInitWindowSize(800, 800); // Taille de la fenêtre
  glutInitDisplayMode(GLUT_RGB); 	// On travaille en RGB
  win = glutCreateWindow("Fractale: Animations de suites complexes"); // On nomme la fenêtre
  
  gluOrtho2D(xmin, xmax, ymin, ymax);	// Zoom du repère
  glBegin(GL_LINES); // Création du repère

  glutKeyboardFunc(clavier);  

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

  diverge(c.r, c.i, 1);

  double tab[7][2] = {  // Suites prédéfinies
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

  glutMouseFunc(clique);

  glutMainLoop(); // Permet un "arrêt sur image"
}
