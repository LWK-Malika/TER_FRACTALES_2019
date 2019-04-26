#include "Point.h"
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

point::point(double X, double Y) : x(X), y(Y) {}

double point::getX() const 
{ 
  return x; 
}

double point::getY() const 
{ 
  return y; 
}

void point::setX(double x) 
{ 
  this->x = x; 
}

void point::setY(double y) 
{
	this->y = y;
}

void point::divergeS(int a)
{
  float compteur = 0;
  float stop = 300; // nombre d'itération avant l'arrêt
  clock_t depart = clock();

  point Zn(0,0); // suite
  point ZnMoins1(0,0); // suite au rang n-1

  if (a == -1) 
  {
    a = rand()%10;
  }
  
  while ((Zn.module() < 4) and (compteur < stop))
  {
    if (difftime(clock(), depart) >= 8000) // Vitesse d'affichage
    {
      ZnMoins1 = Zn;

      // Partie Réelle
      Zn.setX(pow(ZnMoins1.getX(), 2) - pow(ZnMoins1.getY(), 2) + x);

      // Partie imaginaire
      Zn.setY(2 * ZnMoins1.getX() * ZnMoins1.getY() + y);

      // Si suite tend vers un point
      if (abs(Zn.module() - ZnMoins1.module()) < 0.001)
      {
	      std::cout << " Arrêt forcé,car la suite tend vers un point" << std::endl;
	      compteur = stop;
      }
      compteur++;
	
      glColor3f(0.15 * a, 0.7, 1 - 0.15 * a);

      glBegin(GL_POINTS); // mode affichage de points
      glVertex2f(Zn.getX(), Zn.getY());
	
      glEnd(); 		        
      glFlush(); 
	
      depart = clock();
    }
  }
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

double point::module()
{
  return (pow(x, 2) + pow(y, 2));
} 

int point::julia(double R, double I)
{
  point Zn(x,y); // Suite
  point ZnMoins1(x,y); // Suite au rang n-1

  int compteur = 0;
  
  while ((Zn.module() < 4) and (compteur < 100))
  {
      ZnMoins1 = Zn;

      // Partie réel
      Zn.setX(pow(ZnMoins1.getX(), 2) - pow(ZnMoins1.getY(), 2) + R);

      // Partie imaginaire
      Zn.setY(2 * ZnMoins1.getX() * ZnMoins1.getY() + I);

      compteur++;
  }
  if (compteur == 100)
    return -1;
  else
    return compteur;
}

point point::julia2(double R, double I)
{
  point Zn(x,y); // Suite
  point ZnMoins1(x,y); // Suite au rang n-1

  int compteur = 0;
  
  while ((Zn.module() < 4) and (compteur < 100))
  {
    ZnMoins1 = Zn;

    // Partie réel
    Zn.setX(pow(ZnMoins1.getX(), 2) - pow(ZnMoins1.getY(), 2) + R);

    // Partie imaginaire
    Zn.setY(2 * ZnMoins1.getX() * ZnMoins1.getY() + I);

    compteur++;
  }
  return Zn;
}

int diverge(double r,double i)
{ // Formule de la suite construisant l'ensemble de Mandelbrot
  // Zn = 0
  // Zn + 1 = Zn² + c

  point Zn(0,0); // suite
  point ZnMoins1(0,0); // suite au rang n-1
  

  
  int cmp = 0;


     while (Zn.module() < 4 && cmp < 100)
  {
    ZnMoins1 = Zn;
    
    // Partie Réelle
    Zn.setX(pow(ZnMoins1.getX(), 2) - pow(ZnMoins1.getY(), 2) + r);
    
    // Partie imaginaire
    Zn.setY(2 * ZnMoins1.getX() * ZnMoins1.getY() + i);

    
    cmp++;
  }

  if (cmp == 100)
    return -1;
  else
    return cmp;
}

point converge(double r, double i)
{
  double ZnR = 0;
  double ZnI = 0;

  double temporaire;
  
  int cmp = 0;
  while (pow(ZnR,2) + pow(ZnI,2) < 4 && cmp < 100)
  {
    temporaire = ZnR;
    
    ZnR = pow(ZnR, 2) - pow(ZnI, 2) + r;    
    ZnI = 2 * temporaire * ZnI + i;
    cmp++;
  }
  point dernierPoint = point(ZnR, ZnI);
  return dernierPoint;  
}
