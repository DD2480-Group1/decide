#include "decide.h"
#include <cmath>
#include <cstdio>

COMPTYPE Decide::DOUBLECOMPARE(double a, double b) const {
  if (fabs(a - b) < 0.000001)
    return EQ;
  if (a < b)
    return LT;
  return GT;
}

/// @brief Computes the angle (in degrees) between three points, where the second point is the vertex
/// @param point1 first point
/// @param point2 second point, the vertex
/// @param point3 third point
/// @return returns the angle (in degrees) created by the three points.
double Decide::COMPUTEANLGE(const COORDINATE& point1, const COORDINATE& point2, const COORDINATE& point3) {
  // calculate vectors to form the angle
  COORDINATE v1 = {point2.x - point1.x, point2.y - point1.y};
  COORDINATE v2 = {point3.x - point2.x, point3.y - point2.y};

  // using dot product formula to get the angle:
  // calculate the vector multiplication
  double dot_product = v1.x * v2.x + v1.y * v2.y;

  // calcualte the vectors magnitude
  double magnitude_v1 = std::sqrt(std::pow(v1.x, 2) + std::pow(v1.y, 2)); 
  double magnitude_v2 = std::sqrt(std::pow(v2.x, 2) + std::pow(v2.y, 2)); 

  // get the angle from the dot product formula
  double angle = std::acos(dot_product / (magnitude_v1 * magnitude_v2));

  // convert angle from radians to degrees
  angle = angle * 180.0 / PI;
  return angle;
}

/// @brief Validates that an angle can be made with the three points provided
/// @param point1 first point
/// @param point2 second point, the vertex
/// @param point3 third point
/// @return returns True if an angle can be made, returns False if an angle is undefined
bool Decide::VALIDATEANGLE(const COORDINATE& point1, const COORDINATE& point2, const COORDINATE& point3) {
  return ((point1.x == point2.x && point1.y == point2.y) || (point3.x == point2.x && point3.y == point2.y));
}

Decide::Decide(int NUMPOINTS, const std::vector<COORDINATE> &POINTS,
               const PARAMETERS_T &PARAMETERS,
               const std::array<std::array<CONNECTORS, 15>, 15> &LCM,
               const std::array<bool, 15> &PUV)
    : NUMPOINTS(NUMPOINTS), COORDINATES(POINTS), PARAMETERS(PARAMETERS),
      LCM(LCM), PUV(PUV) {}

void Decide::debugprint() const {
  printf("Coordinates (x, y):\n");
  for (int i = 0; i < NUMPOINTS; ++i) {
    printf("\t(%f, %f)\n", COORDINATES[i].x, COORDINATES[i].y);
  }

  printf("\nParameters:\n");

  printf("\tLENGTH1: %f\n", PARAMETERS.LENGTH1);
  printf("\tRADIUS1: %f\n", PARAMETERS.RADIUS1);
  printf("\tEPSILON: %f\n", PARAMETERS.EPSILON);
  printf("\tAREA1: %f\n", PARAMETERS.AREA1);
  printf("\tQ_PTS: %d\n", PARAMETERS.Q_PTS);
  printf("\tQUADS: %d\n", PARAMETERS.QUADS);
  printf("\tDIST: %f\n", PARAMETERS.DIST);
  printf("\tN_PTS: %d\n", PARAMETERS.N_PTS);
  printf("\tK_PTS: %d\n", PARAMETERS.K_PTS);
  printf("\tB_PTS: %d\n", PARAMETERS.A_PTS);
  printf("\tB_PTS: %d\n", PARAMETERS.B_PTS);
  printf("\tC_PTS: %d\n", PARAMETERS.C_PTS);
  printf("\tD_PTS: %d\n", PARAMETERS.D_PTS);
  printf("\tE_PTS: %d\n", PARAMETERS.E_PTS);
  printf("\tF_PTS: %d\n", PARAMETERS.F_PTS);
  printf("\tG_PTS: %d\n", PARAMETERS.G_PTS);
  printf("\tLENGTH2: %f\n", PARAMETERS.LENGTH2);
  printf("\tRADIUS2: %f\n", PARAMETERS.RADIUS2);
  printf("\tAREA2: %f\n", PARAMETERS.AREA2);

  printf("\nLCM:\n");

  for (int y = 0; y < 15; ++y) {
    printf("\t");
    for (int x = 0; x < 15; ++x) {
      printf("%s ", LCM[y][x] == NOTUSED
                        ? "NOTUSED"
                        : (LCM[y][x] == ANDD ? "ANDD   " : "ORR    "));
    }
    printf("\n");
  }

  printf("\nPUV:\n\t");
  for (int i = 0; i < 15; ++i) {
    printf("%s ", PUV[i] ? "true" : "false");
  }

  printf("\nCMV:\n\t");
  for (int i = 0; i < 15; ++i) {
    printf("%s ", CMV[i] ? "true" : "false");
  }

  printf("\n\nPUM:\n");
  for (int y = 0; y < 15; ++y) {
    printf("\t");
    for (int x = 0; x < 15; ++x) {
      printf("%s ", PUM[y][x] ? "true " : "false");
    }
    printf("\n");
  }

  printf("\nFUV:\n\t");
  for (int i = 0; i < 15; ++i) {
    printf("%s ", FUV[i] ? "true" : "false");
  }

  printf("\n\nLAUNCH:\n\t%s\n", LAUNCH ? "true" : "false");
}

void Decide::Lic0() {}

void Decide::Lic1() {}

void Decide::Lic2() {
  // CONDITION: find three consecutive data points to form an angle with
  //            angle needs to be in range to enable LIC
  bool LIC_confirmed = false;
  // -2 to prevent index error
  for (int i = 0; i < Decide::COORDINATES.size() - 2; ++i) {
    // create reference to coordinates, const to protect changes
    const COORDINATE& point1 = Decide::COORDINATES[i];
    const COORDINATE& point2 = Decide::COORDINATES[i + 1];
    const COORDINATE& point3 = Decide::COORDINATES[i + 2];

    // the second point is the "vertex", if any point coincides with it
    // the angle is undefined, therfore is invalid
    if (VALIDATEANGLE(point1, point2, point3) == false) {
      continue;
    }
    // otherwise...
    const double angle = COMPUTEANLGE(point1, point2, point3);
    if (angle < (PI - Decide::PARAMETERS.EPSILON) || angle > (PI + Decide::PARAMETERS.EPSILON)) {
      // we found a valid angle! set corresponding CMV to true
      LIC_confirmed = true;
      break;
    }
  }

  // set the corresponding Conditions Met Vector
  Decide::CMV[2] = LIC_confirmed;
}

void Decide::Lic3() {}

void Decide::Lic4() {}

void Decide::Lic5() {}

void Decide::Lic6() {}

void Decide::Lic7() {}

void Decide::Lic8() {}

void Decide::Lic9() {}

void Decide::Lic10() {}

void Decide::Lic11() {}

void Decide::Lic12() {}

void Decide::Lic13() {}

void Decide::Lic14() {}
