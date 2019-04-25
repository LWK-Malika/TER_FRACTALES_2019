#ifndef Point_h
#define Point_h

class point
{
 private:
  double x; /*< abscisse */
  double y; /*< ordonnée */
  
 public:
  // Constructeur
  point(double X = 0, double Y = 0);

  // Accesseurs en lecture
  double getX() const;
  double getY() const;

  // Accesseurs en écriture
  void setX(double x);
  void setY(double y);

  // Somme de carré de x et de carré de y
  double module();
      
  // Affiche les points des suites
  void divergeS(int i);
 
  // Calcule la fractale de Julia via le complexe donné
  int julia(double R, double I);
  point julia2(double R, double I);

  // Opérateur d'affectation
  point& operator=(const point &p);
};

// Pour remplir l'affiche des fractales de Mandelbrot
int diverge(double x, double y);
point converge(double x, double y);

#endif