#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

/* Améliorations à faire
  - Ajouter une entrée clavier permettant d'arrêter le programme
  - Plus de couleurs (avec le a)
*/

/* Abandonnés car trop compliqué
  - Faire durer les suites intéressantes
  - Mettre en pause
*/

// --- Variables globaux
bool pause = false;

struct Complexe {
  double r, i;
}; typedef struct Complexe Complexe;
// ---


void initialise()
{
  glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique
  
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

// Récupère l'entrée clavier et reset l'affichage
void clavier(unsigned char key, int x, int y) // glutKeyboardFunc(clavier);
{
  cout << "-> clavier" << endl;
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

// Convertir des coordonnées en pixel [0, 800] en coordonnée du repère [-2, 2]
double pixel_to_repere(int i) 
{
  double d = (((double)i) / 200) - 2; 
  return d;
}

void diverge(double r, double i, int a) 
{
  cout << "-> diverge" << endl;
  double ZnR = 0, ZnI = 0, tmp_ZnR, tmp_ZnI, temporaire;
  float compteur = 0;
  float stop = 300; // nombre d'itération avant l'arrêt
  clock_t depart = clock();

  if (a == -1) {
    a = rand()%10;
  }

  // glBegin(GL_LINE_STRIP); // mode affichage de lignes
  
  while ((sqrt(pow(ZnR, 2) + pow(ZnI, 2)) < 2) and (compteur < stop)) {

    // glutKeyboardFunc(clavier);   

    if (!pause && difftime(clock(), depart) >= 8000) { // Vitesse d'affichage
      glBegin(GL_POINTS); // mode affichage de points  
      temporaire = ZnR;
    
      tmp_ZnR = ZnR;
      tmp_ZnI = ZnI;

      ZnR = pow(ZnR, 2) - pow(ZnI, 2) + r;    
      ZnI = 2 * temporaire * ZnI + i;

      // Si pas intéressant
      if (abs(tmp_ZnR - ZnR) < 0.001 && abs(tmp_ZnI - ZnI) < 0.001) { 
        cout << " Arrêt forcé, car peu intéressante." << endl;
        compteur = stop;
      }

      // Si intéressant

      compteur++;
      //cout << " ZnR =" << ZnR << " ZnI =" << ZnI << endl; Affiche les coordonnées du point généré
   
      glColor3f(0.15 * a, 0.7, 1 - 0.15 * a);
    
      glVertex2f(ZnR, ZnI);

      glEnd(); 		        
      glFlush(); 
    
      depart = clock();
    }
  }

  if (compteur < 50) {
    cout << " Diverge à partir de n = "<< compteur;
  } else {
    cout << " Converge";
  }
  cout << endl << endl;
}

// Créer une fonction qui affiche une suite aux coordonnée du clique souris
void clique(int button, int state, int x, int y) // A COMPLETER
{
  if (state == GLUT_UP) {
    cout << "-> clique" << endl;
    double dx = pixel_to_repere(x), dy = -pixel_to_repere(y);

    cout << " Pixel: " << x << ", " << y << endl;
    cout << " Repère: " << dx << ", " << dy << endl;

    if (button == GLUT_RIGHT_BUTTON) { 
      initialise(); 
    }
    diverge(dx, dy, -1);
  }
}

int main(int argc, char** argv) 
{
  cout << "-> main" << endl;
  Complexe c; 
  if (argc == 3) { // Le programme continue avec les paramètre rentrée
    c.r = atof(argv[1]);
    c.i = atof(argv[2]);
    cout << " Le nombre complexe entré est: " << c.r << " + i" << c.i << "" << endl;
  }

	srand(time(NULL));
  int a; 
  int win;
	float xmin = -2, xmax = 2, ymin = -2, ymax = 2;
  float tailleX = xmax - xmin, tailleY = ymax - ymin;

  cout << " Voulez-vous aussi afficher les suites préféfinies ?" << endl 
    << " > [1]: Oui" << endl << " > [0]: Non" << endl;
  cin >> a;

  glutInit(&argc, argv); 
  glutInitWindowSize(800, 800); // Taille de la fenêtre
  glutInitDisplayMode(GLUT_RGB); 	// On travaille en RGB
  win = glutCreateWindow("Fractale: Animations de suites complexes"); // On nomme la fenêtre
  gluOrtho2D(xmin, xmax, ymin, ymax);	// Zoom du repère
  glutKeyboardFunc(clavier);  
  initialise();

  if (c.r == 0 && c.i == 0) // si on a pas rentrer de complexe en paramètre
    diverge(c.r, c.i, 1);

  double tab[8][2] = {  // Suites prédéfinies
    {0, 0.6},
    {0.3,0.5},
    {0.2, 0.5},
    {-0.8,0.156},
    {0.577,0.478},
    {-0.7436,0.661746},
    {-0.55,-0.45},
    {-0.745, 0.055}
  };

  if (a) {
    for (int i=0 ; i < 8 ; i++) {
      diverge(tab[i][0], tab[i][1], i + 1);
    }
  }

  glutMouseFunc(clique);

  cout << " > [Clique Gauche]: Affiche la suite" << endl 
  << " > [Clique Droit]: Efface, puis affiche la suite " << endl 
  << " > [Entrée]: Efface" << endl << endl;

  glutMainLoop(); // Permet un "arrêt sur image"
}
