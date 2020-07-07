#include "timestep.h"

Timestep::Timestep(int stepNumberNew, int atomNumberNew, int molNumberNew,
                   XYZ xyzMinNew, XYZ xyzMaxNew, 
                   vector<Atom> atomsNew
                   ) :
  stepNumber(stepNumberNew),
  atomNumber(atomNumberNew),
  molNumber(molNumberNew),
  xyzMin(xyzMinNew),
  xyzMax(xyzMaxNew),
  atoms(atomsNew)
{
}
