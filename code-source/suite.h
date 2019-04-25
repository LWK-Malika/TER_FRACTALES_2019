#ifndef suite_h
#define suite_h


#include "Point.h"
#include "rectangle.h"
#include <vector>

extern rectangle cadreSuite;

void initialise();

void clavierS(unsigned char key, int x, int y);

void cliqueS(int button, int state, int x, int y);






#endif
