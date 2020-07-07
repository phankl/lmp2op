#ifndef timestep_header
#define timestep_header

#include <vector>

#include "atom.h"
#include "xyz.h"

using namespace std;

struct Timestep {
  public:
    int stepNumber;
    int atomNumber;
    int molNumber;

    XYZ xyzMin;
    XYZ xyzMax;

    vector<Atom> atoms;

    Timestep(int, int, int, XYZ, XYZ, vector<Atom>);
};

#endif
