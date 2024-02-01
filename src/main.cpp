#include <iostream>
#include "decide.h"
#include <fstream>

int main(int argc, char *argv[]) {
  // dummy values for testing
  (void)argc;
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <paramfile>" << std::endl;
    return 1;
  }
  std::string paramFileName = argv[1];
  std::ifstream paramFile;
  paramFile.open(paramFileName);
  if (!paramFile.is_open()) {
    std::cout << "Could not open file " << paramFileName << std::endl;
    return 1;
  }

  int NUMPOINTS;
  paramFile >> NUMPOINTS;

  std::vector<COORDINATE> points;
  for (int i = 0; i < NUMPOINTS; i++) {
    COORDINATE point;
    paramFile >> point.x;
    paramFile >> point.y;
    points.push_back(point);
  }

  PARAMETERS_T parameters;
  paramFile >> parameters.LENGTH1;
  paramFile >> parameters.RADIUS1;
  paramFile >> parameters.EPSILON;
  paramFile >> parameters.AREA1;
  paramFile >> parameters.Q_PTS;
  paramFile >> parameters.QUADS;
  paramFile >> parameters.DIST;
  paramFile >> parameters.N_PTS;
  paramFile >> parameters.K_PTS;
  paramFile >> parameters.A_PTS;
  paramFile >> parameters.B_PTS;
  paramFile >> parameters.C_PTS;
  paramFile >> parameters.D_PTS;
  paramFile >> parameters.E_PTS;
  paramFile >> parameters.F_PTS;
  paramFile >> parameters.G_PTS;
  paramFile >> parameters.LENGTH2;
  paramFile >> parameters.RADIUS2;
  paramFile >> parameters.AREA2;

  std::array<std::array<CONNECTORS, 15>, 15> lcm;

  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) {
      std::string temp;
      paramFile >> temp;
      if (temp == "ANDD") {
        lcm[i][j] = ANDD;
      } else if (temp == "ORR") {
        lcm[i][j] = ORR;
      } else if (temp == "NOTUSED") {
        lcm[i][j] = NOTUSED;
      } else {
        std::cout << "Invalid connector in file " << paramFileName << std::endl;
        return 1;
      }
    }
  }

  std::array<bool, 15> puv;
  for (int i = 0; i < 15; i++) {
    std::string temp;
    paramFile >> temp;
    if (temp == "T") {
      puv[i] = true;
    } else if (temp == "F") {
      puv[i] = false;
    } else {
      std::cout << temp << std::endl;
      std::cout << "Invalid PUV in file " << paramFileName << std::endl;
      return 1;
    }
  }

  Decide decide(NUMPOINTS, points, parameters, lcm, puv);
  decide.decide();
  decide.debugprint();

  //   std::vector<COORDINATE> points = {{-1, 1}, {2, 2}, {0, 1},  {2, 3},
  //                                     {1, 4},  {5, 1}, {-5, 3}, {1, 0}};

  //   const int NUMPOINTS = points.size();

  //   PARAMETERS_T parameters;
  //   parameters.LENGTH1 = 5;
  //   parameters.RADIUS1 = 2.33;
  //   parameters.EPSILON = 0.12;
  //   parameters.AREA1 = 4;
  //   parameters.Q_PTS = 1;
  //   parameters.QUADS = 2;
  //   parameters.DIST = 4;
  //   parameters.N_PTS = 1;
  //   parameters.K_PTS = 2;
  //   parameters.A_PTS = 3;
  //   parameters.B_PTS = 2;
  //   parameters.C_PTS = 1;
  //   parameters.D_PTS = 2;
  //   parameters.E_PTS = 1;
  //   parameters.F_PTS = 2;
  //   parameters.G_PTS = 5;
  //   parameters.LENGTH2 = 5;
  //   parameters.RADIUS2 = 1;
  //   parameters.AREA2 = 1;

  //   std::array<std::array<CONNECTORS, 15>, 15> lcm;
  //   std::array<bool, 15> puv;

  //   Decide decide(NUMPOINTS, points, parameters, lcm, puv);

  //   decide.debugprint();
  //   decide.decide();
  return 0;
}
