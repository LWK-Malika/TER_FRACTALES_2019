#ifndef Rectangle_h
#define Rectangle_h
#include "Point.h"


class rectangle{
  private:


  point min;
  point max;
 public:
  rectangle(point min, point max);
  rectangle(double xmin, double ymin, double xmax, double ymax);

  rectangle(rectangle & aCopier);

  void reinitialise();

  void resetRepere();
  
  double getXmin() const;
  double getYmin() const;
  double getXmax() const;
  double getYmax() const;
  
   
  void setXmin(double x);
  void setYmin(double x);
  void setXmax(double x);
  void setYmax(double x);

  double getTailleX()const;
  double getTailleY()const;

  double repereToPixelX(int point);
  double repereToPixelY(int point);
  

  
  double pixelToRepereX(int pixel)const; 
  double pixelToRepereY(int pixel)const;
 
  double distPixToRepX(int pixel)const;
  double distPixToRepY(int pixel)const;
  

  double coordRepX(int i) const;
  double coordRepY(int i) const;
  
  template<typename T>
  void static inverse(T &min, T &max);
  
  void inverse();


  void operator= (rectangle & bis);

  void zoomArriere();

  void zoomAvant();

};



#endif
