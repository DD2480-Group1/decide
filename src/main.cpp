#include <iostream>
#include "decide.h"

int main() {
  // dummy values for testing
  std::vector<COORDINATE> points = {{-1, 1}, {2, 2}, {0, 1},  {2, 3},
                                    {1, 4},  {5, 1}, {-5, 3}, {1, 0}};

  const int NUMPOINTS = points.size();

  PARAMETERS_T parameters;
  parameters.LENGTH1 = 5;
  parameters.RADIUS1 = 2.33;
  parameters.EPSILON = 0.12;
  parameters.AREA1 = 4;
  parameters.Q_PTS = 1;
  parameters.QUADS = 2;
  parameters.DIST = 4;
  parameters.N_PTS = 1;
  parameters.K_PTS = 2;
  parameters.A_PTS = 3;
  parameters.B_PTS = 2;
  parameters.C_PTS = 1;
  parameters.D_PTS = 2;
  parameters.E_PTS = 1;
  parameters.F_PTS = 2;
  parameters.G_PTS = 5;
  parameters.LENGTH2 = 5;
  parameters.RADIUS2 = 1;
  parameters.AREA2 = 1;

  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(NUMPOINTS, points, parameters, lcm, puv);

  decide.debugprint();
  decide.decide();
  return 0;
}
