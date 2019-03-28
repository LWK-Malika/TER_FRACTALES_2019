#include "rectangle.h"
#include <iostream>

rectangle::rectangle(point min, point max):min(min), max(max){}

rectangle::rectangle(int xmin, int ymin, int xmax, int ymax):
  min(xmin,ymin), max(xmax,ymax){}


int rectangle::getXmin() const{
  return min.getX();
}

int rectangle::getXmax() const{
  return max.getX();
}

int rectangle::getYmin() const{
  return min.getY();
}
int rectangle::getYmax() const{
  return max.getY();
}



void rectangle::setXmin(int x){
  min.setX(x);
}
void rectangle::setXmax(int x){
  max.setX(x);
}
void rectangle::setYmin(int x){
  min.setY(x);
}
void rectangle::setYmax(int x){
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


