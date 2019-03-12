
//compiler avec g++ graphique.cpp -o graphique -lglut -lGLU -lGL

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <ctime> //pour calculer le temps du programme
#include <vector>

#include <cmath>

#include <iostream>
using namespace std;



typedef enum {RECTANGLE, TEAPOT, SPHERE} obj_type ;
obj_type obj = TEAPOT ;
void display(void) {
  glClear(GL_COLOR_BUFFER_BIT) ;
  switch (obj) {
  case RECTANGLE: glRectf(-0.3,-0.3,0.3,0.3) ;
      break ;
  case SPHERE: glutSolidSphere(0.5, 64, 64) ;
      break ;
  case TEAPOT: glutSolidTeapot(0.5) ;
      break ;
  }
  glutSwapBuffers() ;
}
void objMenu(int choice) {
  //obj = choice ;
  glutPostRedisplay() ;
}
int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE) ;
  glutCreateWindow(argv[0]) ;
  int m = glutCreateMenu(objMenu) ;
  glutSetMenu(m) ;
  glutAddMenuEntry("rectangle",RECTANGLE) ;
  glutAddMenuEntry("sphere",SPHERE) ;
  glutAddMenuEntry("teapot",TEAPOT) ;
  glutAttachMenu(GLUT_RIGHT_BUTTON) ;
  glClearColor(1.0,1.0,1.0,0.0) ;
  
  
  glutDisplayFunc(display) ;
  glutMainLoop() ;
  return 0 ;
}
