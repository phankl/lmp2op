#include <vector>
#include <iostream>
#include <string>

#include "io.h"
#include "timestep.h"

#define SIDES 10

using namespace std;
using namespace io;

int main(int argc, char* argv[])
{
  string inputFileName;
  string opFileName;

  if (argc != 3) {
    cout << "Incorrect input format. Please use the following input format:" << endl;
    cout << "lmp2op LMP_FILE_NAME OP_FILE_NAME" << endl;
    return 1;
  }

  inputFileName = argv[1];
  opFileName = argv[2];

  vector<Timestep> timesteps = io::readLMP(inputFileName);

  io::writeOP(timesteps, opFileName);

  return 0;
}
