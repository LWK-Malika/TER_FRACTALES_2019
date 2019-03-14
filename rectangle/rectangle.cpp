#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


int rectangleElastique[6];

int xmin=-2;
int xmax=2;
int ymin=-2;
int ymax=2;

 int maxFx=800;
 int maxFy=800;


int cliqueX;
int cliqueY;

void dessineFond(){

  glColor3f(1,1,1);
  glBegin(GL_POLYGON);
 
  glVertex2f(xmin,ymin);
  glVertex2f(xmin,ymax);
  glVertex2f(xmax,ymax);
  glVertex2f(xmax,ymin);
  glEnd(); 		       
  glFlush();

}


double conversionX(int x){
  return ((xmax-xmin)/(double)maxFx)*(double)x+xmin;
}
double conversionY(int y){
  return -(((ymax-ymin)/(double)maxFy)*(double)y+ymin);
}


void trace( int x, int y){
  float tailleY=(ymax-ymin);
   float tailleX=(xmax-xmin);

   rectangleElastique[2]=x;
   rectangleElastique[3]=y;


  glutPostRedisplay();
}

void clique(int button, int state, int x, int y){

  for(int i=0; i<6; i++){
  rectangleElastique[i]=x;
  rectangleElastique[++i]=y;
  }

  glutPostRedisplay();
  
}



void affichage(){

  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  dessineFond();

  
   glPointSize(10);
   glBegin(GL_POINTS);
   glColor3f(1,0,0);
   glVertex2f(0,1);

   glColor3f(0,1,0);
   glVertex2f(0,0);
   
   glEnd();

  
   
   glColor3f(0,0,0.8);
  //trace la ligne verticale partant du point de départ
  glBegin(GL_LINES);
  glVertex2f(conversionX(rectangleElastique[0]), conversionY(rectangleElastique[1]));
  glVertex2f(conversionX(rectangleElastique[0]), conversionY(rectangleElastique[3]));
  glEnd(); 		       	// Fermer le polygone

  //ligne horizontale partant du point de départ
  glBegin(GL_LINES);
  glVertex2f(conversionX(rectangleElastique[0]), conversionY(rectangleElastique[1]));
  glVertex2f(conversionX(rectangleElastique[2]), conversionY(rectangleElastique[1]));
  glEnd(); 		       	// Fermer le polygone
  glFlush();


}


int main(int argc, char* argv[]) {
  time_t start, stop;

 
  
  glutInit(&argc, argv); 
  glutInitWindowSize(maxFx, maxFy); // taille fenetre
  glutInitDisplayMode(GLUT_RGB); // On travaille en RGB
  int win = glutCreateWindow("Fractale de Mandelbrot"); // nomme la fenêtre
  
  gluOrtho2D(-2,2,-2,2);

  glutDisplayFunc(affichage);
  
  
    glutMouseFunc(clique);
   glutMotionFunc(trace);
   

   
  


  
  glutMainLoop();


}
