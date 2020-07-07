#ifndef atom_header
#define atom_header

#include <cmath>

#include "xyz.h"

struct Atom {
  public:
    int mol;
    XYZ xyz;
    double data;

    Atom(int, XYZ, double);
};
    
#endif
