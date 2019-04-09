#include "Point.h"
#include <iostream>
#include <cmath>

point::point(double X, double Y): x(X), y(Y){}


double point::getX() const {
	return x;}

double point::getY() const {
	return y;}

void point::setX(double x) {
	this->x=x;}

void point::setY(double y) {
	this->y=y;}

int point::diverge(double r,double i){
  // std::cout<<"le nombre complexe entré est: " <<r<<"+i("<<i<<")"<< std::endl;

  //Zn=0
  //Zn+1=Zn²+c

  double ZnR=0;
  double ZnI=0;

  double temporaire;
  
  int cmp=0;
  while(sqrt(pow(ZnR,2)+pow(ZnI,2))<2 && cmp<100){

    temporaire=ZnR;
    
    ZnR=pow(ZnR,2)-pow(ZnI,2)+r;    
    ZnI=2*temporaire*ZnI+i;
    cmp++;
  }

  if(cmp==100)
    return -1;
  else
    return cmp;
}

point point::converge(double r, double i){

  double ZnR=0;
  double ZnI=0;

  double temporaire;
  
  int cmp=0;
  while(sqrt(pow(ZnR,2)+pow(ZnI,2))<2 && cmp<100){

    temporaire=ZnR;
    
    ZnR=pow(ZnR,2)-pow(ZnI,2)+r;    
    ZnI=2*temporaire*ZnI+i;
    cmp++;
  }
  point dernierPoint = point(ZnR, ZnI);
  return dernierPoint;  
}

point& point::operator=(const point &p)
{
  if (this != &p)
  {
    x = p.x;
    y = p.y;
  }
  return *this;
}