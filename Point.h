#ifndef Point_h
#define Point_h

class point{
 private:
  int x;
  int y;
 public:
  point(int X=0, int Y=0);
  
  int getX() const;
  int getY() const;

  void setX( int x);
  void setY( int y);
  

  static int diverge(double x, double y);

};

#endif
