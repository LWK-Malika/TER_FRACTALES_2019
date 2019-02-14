#include "Point.h"
#include <iostream>
#include <cmath>

point::point(int X, int Y): x(X), y(Y){}


int point::getX() const {
	return x;}

int point::getY() const {
	return y;}

void point::setX(int x) {
	this->x=x;}

void point::setY(int y) {
	this->y=y;}

bool point::diverge(double r,double i){
  // std::cout<<"le nombre complexe entré est: " <<r<<"+i("<<i<<")"<< std::endl;

  //Zn=0
  //Zn+1=Zn²+c

  int ZnR=0;
  int ZnI=0;

  int temporaire;
  
  int cmp=0;
  while(sqrt(pow(ZnR,2)+pow(ZnI,2))<2 && cmp<50){

    temporaire=ZnR;
    
    ZnR=pow(ZnR,2)-pow(ZnI,2)+r;    
    ZnI=2*temporaire*ZnI+i;
    cmp++;
  }

  return(cmp<50);
}
