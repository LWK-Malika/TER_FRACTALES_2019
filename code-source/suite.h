#ifndef suite_h
#define suite_h

#include "Point.h"
#include "rectangle.h"
#include <vector>

// Variable global
extern rectangle cadreSuite;

// Efface et réaffiche le repère
void initialise();

// Gère les entrées claviers, pour les suites
void clavierS(unsigned char key, int x, int y);

// Gère les cliques, pour les suites
void cliqueS(int button, int state, int x, int y);

#endif