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
