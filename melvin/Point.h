#ifndef Point_h
#define Point_h

class point{
 private:
  double x;
  double y;
 public:
  point(double X=0, double Y=0);
  
  double getX() const;
  double getY() const;

  void setX( double x);
  void setY( double y);
  

  static int diverge(double x, double y);

};

#endif
