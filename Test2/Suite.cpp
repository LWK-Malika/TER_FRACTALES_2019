#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>


using namespace std;

void diverge(double r, double i,int a){
  
  double ZnR=0;
  double ZnI=0;

  double temporaire;
  
  float cmp=0;
  // glBegin(GL_LINE_STRIP);
  while(sqrt(pow(ZnR,2)+pow(ZnI,2))<2 && cmp<50){
    
    temporaire=ZnR;
    
    ZnR=pow(ZnR,2)-pow(ZnI,2)+r;    
    ZnI=2*temporaire*ZnI+i;
    cmp++;
    cout<<" ZnR ="<<ZnR<<" ZnI ="<<ZnI <<endl;
    
    
     glBegin(GL_POINTS); 	//mode affichage de points

   
    glColor3f(0.1*a,0, 1-0.05*a);
    
    glVertex2f(ZnR,ZnI);
    
     glEnd(); 		        
      glFlush(); 
  }
  //  glEnd(); 		        
  //   glFlush(); 
  if(cmp<50){
    cout<<"la fonction diverge a partir de n= "<<cmp<<endl;
    
  }
  else
    cout<<"la fonction converge"<<endl;
  }


int main(int argc, char** argv){


  
  
  float r;
  cin>>r;
  float i;
  cin>>i;
  std::cout<<"le nombre complexe entré est: "<<r<<"+i("<<i<<")"<<endl;

  cout<<"voulez vous afficher les suite préféfinies ?"<<endl<<"tapez '1' pour oui et '0' pourn non"<<endl;
  int a;
  cin>>a;

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


  glBegin(GL_LINES); // création du repère
  glColor3f(1, 1,1);
  glVertex2f(-2,0);
  glVertex2f(2,0); 

  glVertex2f(0,-2);
  glVertex2f(0,2);

  glEnd();
  glFlush();
  
  glPointSize(2);


  //affiche graduation 
  glRasterPos2f(1,0.05);
  glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'1');

  glRasterPos2f(-0.05,1);
  glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'1');


  
  diverge(r,i,1);

  double tab[5][2]={{0,0.6},{0.3,0.5},{-0.8,0.156},{0.577,0.478},{-0.7436,0.661746}};

  if(a){
    for(int i=0;i<5;i++)
      diverge(tab[i][0],tab[i][1],i+1);
  }
  glutMainLoop(); //permet un "arret sur image"


}
