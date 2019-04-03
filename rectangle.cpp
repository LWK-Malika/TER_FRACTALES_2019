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
//extern rectangle zoom;

rectangle::rectangle(point min, point max):min(min), max(max){}

rectangle::rectangle(double xmin, double ymin, double xmax, double ymax):
  min(xmin,ymin), max(xmax,ymax){}

rectangle::rectangle(rectangle & aCopier):min(aCopier.getXmin(), aCopier.getXmax()),
					  max(aCopier.getYmin(), aCopier.getYmax()){}


void rectangle::reinitialise(){
  setXmin(-2.15);
  setXmax(0.55);
  setYmin(-1.3);
  setYmax(1.3);
}

void rectangle::resetRepere(){
  reinitialise();
  gluOrtho2D(getXmin(), getXmax(), getYmax(), getYmin());

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


template<typename T>
void rectangle::inverse(T &min, T &max){
  if (max < min) {
    T a = min;
    min = max;
    max = a;   
  }
}

void rectangle::inverse(){
  if (getXmax() < getXmin()) {
    double a = getXmin();
    setXmin(getXmax());
    setXmax(a);   
  }
    if (getYmax() < getYmin()) {
    double a = getYmin();
    setYmin(getYmax());
    setYmax(a);   
  }
}


void rectangle::operator= (rectangle & bis){
  this->setXmin( bis.getXmin() );
  this->setXmax( bis.getXmax() );
  this->setYmin( bis.getYmin() );
  this->setYmax( bis.getYmax() );
}



void rectangle::zoomArriere(){

  ///BBBUUUUGGGG a trouver un meilleur algo svp :(
  rectangle temp(*this);
  
  setXmin(temp.getXmin()+(temp.getTailleX()/10*(temp.getXmin()<0?1:-1)));	 
  setXmax(temp.getXmax()+(temp.getTailleX()/10*(temp.getXmax()<0?-1:1)));
  
  setYmin(temp.getYmin()+(temp.getTailleY()/10*(temp.getYmin()<0?1:-1)));	 
  setYmax(temp.getYmax()+(temp.getTailleY()/10*(temp.getYmax()<0?-1:1)));
  
  glLoadIdentity(); //réinitialise le repère
  
  gluOrtho2D(getXmin(),getXmax(),getYmax(), getYmin());	      	//zoom du repère
}

void rectangle::zoomAvant(){

   rectangle temp(*this);
   
  setXmin(temp.getXmin()+(temp.getTailleX()/10*(temp.getXmin()<0?-1:1)));	 
  setXmax(temp.getXmax()+(temp.getTailleX()/10*(temp.getXmax()<0?1:-1)));
  
  setYmin(temp.getYmin()+(temp.getTailleY()/10*(temp.getYmin()<0?-1:1)));	 
  setYmax(temp.getYmax()+(temp.getTailleY()/10*(temp.getYmax()<0?1:-1)));
  
  
  
  glLoadIdentity();
  gluOrtho2D(getXmin(),getXmax(),getYmax(), getYmin());	      	//zoom du repère
}
