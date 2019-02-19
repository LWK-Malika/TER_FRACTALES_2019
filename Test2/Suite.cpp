#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

using namespace std;

int main(int argc, char** argv){
  
  float r;
  cin>>r;
  float i;
  cin>>i;
  std::cout<<"le nombre complexe entré est: "<<r<<"+i("<<i<<")"<<endl;


  glutInit(&argc,argv); 
  glutInitWindowSize(800,800); //taille fenetre
  glutInitDisplayMode(GLUT_RGB); 	// On travaille en RGB
  int win = glutCreateWindow("Fractale "); //nomme la fenêtre

  float xmin=-2;
  float xmax=2;
  float ymin=-2;
  float ymax=2;
  
  float tailleX=xmax-xmin;
  float tailleY=ymax-ymin;
  
  gluOrtho2D(xmin,xmax,ymin,ymax);	      	//zoom du repère


  glBegin(GL_LINES);
  glColor3f(1, 1,1);
  glVertex2f(-2,0);
  glVertex2f(2,0);

    glVertex2f(0,-2);
  glVertex2f(0,2);

  glEnd();
  glFlush();
  glPointSize(3);


  

  
  double ZnR=0;
  double ZnI=0;

  double temporaire;
  
  int cmp=0;
  while(sqrt(pow(ZnR,2)+pow(ZnI,2))<2 && cmp<50){
    
    temporaire=ZnR;
    
    ZnR=pow(ZnR,2)-pow(ZnI,2)+r;    
    ZnI=2*temporaire*ZnI+i;
    cmp++;
    cout<<" ZnR ="<<ZnR<<" ZnI ="<<ZnI <<endl;
    
    
    glBegin(GL_POINTS); 	//mode affichage de points
    
    glColor3f(0.6, 0, 003);
    glVertex2f(ZnR,ZnI);
    
    glEnd(); 		        
    glFlush(); 
  }

  if(cmp<50){
    cout<<"la fonction diverge a partir de n= "<<cmp<<endl;
    
  }
  else
    cout<<"la fonction converge"<<endl;



  
  glutMainLoop(); //permet un "arret sur image"


}
