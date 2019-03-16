#ifndef Rectangle_h
#define Rectangle_h

#include "Point.h"

class rectangle{
  private:


  point min;
  point max;
 public:
  rectangle(point min, point max);
  rectangle(int xmin, int ymin, int xmax, int ymax);
  
  int getXmin() const;
  int getYmin() const;
  int getXmax() const;
  int getYmax() const;
  
   
  void setXmin(int x);
  void setYmin(int x);
  void setXmax(int x);
  void setYmax(int x);

  
};







#endif
