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

  void reinitialise();
  
  double getXmin() const;
  double getYmin() const;
  double getXmax() const;
  double  getYmax() const;
  
   
  void setXmin(double x);
  void setYmin(double x);
  void setXmax(double x);
  void setYmax(double x);

  double getTailleX()const;
  double getTailleY()const;
  
  double pixelToRepereX(int pixel)const; 
  double pixelToRepereY(int pixel)const;
 
  double distPixToRepX(int pixel)const;
  double distPixToRepY(int pixel)const;
  

  double coordRepX(int i) const;
  double coordRepY(int i) const;



  
};







#endif
