
//compiler avec g++ graphique.cpp -o graphique -lglut -lGLU -lGL


#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

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
  glutInit(&argc,argv);
  glutInitWindowSize(400,200);
  glutInitDisplayMode(GLUT_RGB); 	// On travaille en RGB
  int win = glutCreateWindow("Fractale de Mandelbrot");
    

  glClearColor(0, 1, 0, 0); 
  gluOrtho2D(0,600,0,600);	      	// On garde ces coordonnées
  glutDisplayFunc(Rafraichir); 		// Callback de la fenêtre



  glutMainLoop(); //permet un "arret sur image"
 
}
