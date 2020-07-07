#ifndef io_header
#define io_header

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

#include "atom.h"
#include "timestep.h"
#include "xyz.h"

using namespace std;

namespace io {
  vector<Timestep> readLMP(string);
  void writeOP(const vector<Timestep>&, string);
}

#endif
