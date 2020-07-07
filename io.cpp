#include "io.h"

using namespace std;

namespace io {

vector<Timestep> readLMP(string lmpFileName)
{
  vector<Timestep> allSteps;

  ifstream file(lmpFileName);

  int stepNumber;
  int atomNumber;

  double xMin,yMin,zMin;
  double xMax,yMax,zMax;
  
  string line;
  vector<Atom> stepAtoms;
  vector<int> stepMols;
  bool first = true;
  bool step = true;
  bool number = false;
  bool box = false;
  bool xDimension = true;
  bool yDimension = false;
  bool zDimension = false;

  // iterate over all lines in file

  while (getline(file,line)) {
    stringstream check(line);
    vector<string> words;
    string token;

    // split line into words and parse
    
    while (getline(check,token,' ')) words.push_back(token);

    if (words.size() == 5) {
      int mol = stoi(words[0]);
      double x = stod(words[1]);
      double y = stod(words[2]);
      double z = stod(words[3]);
      double data = stod(words[4]);
      Atom atom(mol,XYZ(x,y,z),data);
      stepAtoms.push_back(atom);
      
      // check if mol is new
      vector<int>::iterator it = find(stepMols.begin(),stepMols.end(),mol);
      if (it == stepMols.end()) stepMols.push_back(mol);
    }
    else if (words.size() == 2 && box) {
      if (xDimension) {
        xMin = stod(words[0]);
        xMax = stod(words[1]);
        xDimension = false;
        yDimension = true;
      }
      else if (yDimension) {
        yMin = stod(words[0]);
        yMax = stod(words[1]);
        yDimension = false;
        zDimension = true;
      }
      else if (zDimension) {
        zMin = stod(words[0]);
        zMax = stod(words[1]);
        zDimension = false;
        xDimension = true;
        box = false;
        step = true;
      }
    }
    else if (words.size() == 1) {
      if (step) {

        // start new timestep unless first
        
        if (!first) {
          int molNumber = stepMols.size();
          Timestep timestep(stepNumber,atomNumber,molNumber,XYZ(xMin,yMin,zMin),XYZ(xMax,yMax,zMax),stepAtoms);
          allSteps.push_back(timestep);
          stepAtoms.clear();
          stepMols.clear();
        }
        else first = false;

        stepNumber = stoi(words[0]);
        step = false;
        number = true;
      }
      else if (number) { 
        atomNumber = stoi(words[0]);
        number = false;
        box = true;
      }
    }
  }

  int molNumber = stepMols.size();
  Timestep timestep(stepNumber,atomNumber,molNumber,XYZ(xMin,yMin,zMin),XYZ(xMax,yMax,zMax),stepAtoms);
  allSteps.push_back(timestep);
  
  file.close();

  cout << "Finished reading LMP file " << lmpFileName << "." << endl;
  cout << "Found total number of " << allSteps.size() << " time steps." << endl;

  return allSteps;
}

void writeOP(const vector<Timestep>& timesteps, string opFileName)
{
  int timestepNumber = timesteps.size();

  vector<vector<double>> data(timestepNumber,vector<double>(4,0.0));

  //#pragma omp parallel for
  for (int i = 0; i < timestepNumber; i++) {
    Timestep timestep = timesteps[i];
    vector<Atom> atoms = timestep.atoms;
    int stepNumber = timestep.stepNumber;
    int atomNumber = timestep.atomNumber;
    int molNumber = timestep.molNumber;
    XYZ xyzMin = timestep.xyzMin;
    XYZ xyzMax = timestep.xyzMax;

    int atomsPerMol = atomNumber / molNumber;

    double sigmaX = 0.0;
    double sigmaY = 0.0;
    double sigmaZ = 0.0;

    for (int j = 0; j < molNumber; j++)
      for (int k = 0; k < atomsPerMol-1; k++) {
        XYZ xyz1 = atoms[j*atomsPerMol + k].xyz;
        XYZ xyz2 = atoms[j*atomsPerMol + k + 1].xyz;

        XYZ delta = xyz2 - xyz1;
        pbc(xyzMin,xyzMax,delta,delta);
 
        delta.normalise();

        sigmaX += 0.5*(3.0*pow(delta.x,2.0) - 1.0);
        sigmaY += 0.5*(3.0*pow(delta.y,2.0) - 1.0);
        sigmaZ += 0.5*(3.0*pow(delta.z,2.0) - 1.0);
      }

    data[i][0] = stepNumber;
    data[i][1] = sigmaX / (atomNumber-molNumber);
    data[i][2] = sigmaY / (atomNumber-molNumber);
    data[i][3] = sigmaZ / (atomNumber-molNumber);
  }

  ofstream file(opFileName);

  for(int i = 0; i < timestepNumber; i++)
    file << data[i][0] << " " << data[i][1] << " " << data[i][2] << " " << data[i][3] << endl;

  file.close();
}

}
