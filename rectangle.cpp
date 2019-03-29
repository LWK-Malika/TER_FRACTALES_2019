#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cmath>
#include "rectangle.h"




extern int couleur;
extern std::vector<std::vector<int>> tab;
extern int* tabOcc;

rectangle::rectangle(point min, point max):min(min), max(max){}

rectangle::rectangle(double xmin, double ymin, double xmax, double ymax):
  min(xmin,ymin), max(xmax,ymax){}



void rectangle::reinitialise(){
  setXmin(-2.15);
  setXmax(0.55);
  setXmin(-1.3);
  setXmin(1.3);
}



double rectangle::getXmin() const{
  return min.getX();
}

double rectangle::getXmax() const{
  return max.getX();
}

double rectangle::getYmin() const{
  return min.getY();
}
double rectangle::getYmax() const{
  return max.getY();
}



void rectangle::setXmin(double x){
  min.setX(x);
}
void rectangle::setXmax(double x){
  max.setX(x);
}
void rectangle::setYmin(double x){
  min.setY(x);
}
void rectangle::setYmax(double x){
  max.setY(x);
}


double rectangle::getTailleX()const{
  return abs(getXmax()-getXmin());
}
double rectangle::getTailleY()const{
  return abs(getYmax()-getYmin());
}
  
  
double rectangle::pixelToRepereX(int pixel)const{

  return (getTailleX()/800)*pixel+getXmin();
}

double rectangle::pixelToRepereY(int pixel)const{
  return -((getTailleY()/800)*pixel+getYmin()); 
}

double rectangle::distPixToRepX(int pixel)const{
  return pixelToRepereX(pixel)-pixelToRepereX(0); 
}

double rectangle::distPixToRepY(int pixel)const{
  return pixelToRepereY(pixel)-pixelToRepereY(0); 
}

double rectangle::coordRepX(int i) const{
  (getTailleX()/800)*i+getXmin();
  
}
double rectangle::coordRepY(int i) const{
  (getTailleY()/800)*i+getYmin();
}


void rectangle::dessine(){
    
  glBegin(GL_POINTS); 	//mode affichage de points
    
  for(int i=0;i<800;i++){ //double boucle pour parcourir les points étudié
    for(int  j=0;j<800;j++){

      
      
      if (tab[i][j]==-1)
	glColor3f(0.2, 0.2, 0.2);  
      
      
      else
	switch(couleur){
	case 0:
	  glColor3f(cos(exp(5*(0.01*tab[i][j]))+4),
		    cos(exp(5*(0.01*tab[i][j]))+2),
		    cos(exp(5*(0.01*tab[i][j]))));
	  break;
	case 1:
	  
	  glColor3f(0.00001*tabOcc[tab[i][j]],
		    1-0.0001*tabOcc[tab[i][j]],
		    0.5-0.00001*tabOcc[tab[i][j]]);
	  break;
	case 974:
	  
	  //vert -> bleu -> rouge
	  float tabCouleur[10][3]={
	    {0,1,0}, {0,1,0.85},
	    {0,0.8,1}, {0,0.95,1},
	    {0,0,1}, {0.8,0,1},
	    {1,0,1}, {1,0,0.5},
	    {1,0,0}, {1,0.5,0}};
	    
	  //rouge ->vert->bleu
	  // float tabCouleur[10][3]={{1,0,0}, {1,0.5,0},
	  // 			     {1,1,0}, {0.5,1,0},
	  // 			     {0,1,0}, {0,1,0.5},
	  // 			     {0,1,1}, {0,0.5,1},
	  // 			     {0,0,1}, {1,0,1}};
	    
	  glColor3f(tabCouleur[(tab[i][j]/10)][0] ,
		    tabCouleur[(tab[i][j]/10)][1],
		    tabCouleur[(tab[i][j]/10)][2]  );
	}
      glVertex2f((getTailleX()/800)*i+getXmin(),
		 (getTailleY()/800)*j+getYmin()); 
    }     
    
  
  }
  glEnd(); 		       	// Fermer le polygone
  glFlush(); 
}


