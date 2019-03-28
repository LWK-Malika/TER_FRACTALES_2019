#include "rectangle.h"
#include <iostream>

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


