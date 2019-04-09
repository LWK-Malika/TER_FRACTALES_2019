#ifndef suite_h
#define suite_h


#include "Point.h"
#include "rectangle.h"
#include <vector>

extern rectangle cadreSuite;

class suite{
  // private:
  //static bool pause;// = false;


 public:

  static void initialise();

  static void clavier(unsigned char key, int x, int y);

  static void diverge(point c, int a);

  static void clique(int button, int state, int x, int y);




};

#endif
