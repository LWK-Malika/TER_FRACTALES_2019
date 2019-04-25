#ifndef Rectangle_h
#define Rectangle_h
#include "Point.h"

class rectangle
{
 private:
  point min;
  point max;

 public:
  // Constructeurs
  rectangle(point min, point max);
  rectangle(double xmin, double ymin, double xmax, double ymax);
  rectangle(rectangle & aCopier);

  // Réinitialisation du zoom
  void reinitialise();
  void reinitialiseJulia();

  // Réinitialisation du zoom et du repère
  void resetRepere();
  void resetRepereJulia();
  
  // Teste si on est au repère de base
  bool repereBaseM();
  bool repereBaseJ();

  // Accesseurs en lecture de rectangle
  double getXmin() const;
  double getYmin() const;
  double getXmax() const;
  double getYmax() const;
   
  // Accesseurs en écriture de rectangle
  void setXmin(double x);
  void setYmin(double x);
  void setXmax(double x);
  void setYmax(double x);

  // Récupère la taille de la fenêtre
  double getTailleX()const;
  double getTailleY()const;

  // Converti un nombre complexe (repère) en coordonnée de pixel
  double repereToPixelX(int point);
  double repereToPixelY(int point);
  
  // Converti un pixel en coordonnée de nombre complexe (repère)
  double pixelToRepereX(int pixel)const; 
  double pixelToRepereY(int pixel)const;
 
  // Distance du pixel par rapport 0
  double distPixToRepX(int pixel)const;
  double distPixToRepY(int pixel)const;
  
  // Echange les valeurs xmax et xmin,
  // afin qu'ils correspondent bien à ce qu'ils représentent.
  // (idem pour ymin et ymax)
  void inverse();

  // Operateur d'affectation
  void operator=(rectangle & bis);

  // Zoom roulette arrière et avant
  void zoomArriere();
  void zoomAvant();
};

#endif