
//compiler avec g++ graphique.cpp -o graphique -lglut -lGLU -lGL


#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>




int main(int argc, char* argv[])
{
  glutInit(&argc,argv);
  glutInitWindowSize(400,200);
  int win = glutCreateWindow("Fractale de Mandelbrot");
    
  
  glutMainLoop(); //permet un "arret sur image"
}
