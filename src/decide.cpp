#include "decide.h"
#include <cmath>
#include <cstdio>

COMPTYPE Decide::DOUBLECOMPARE(double a, double b) const {
  if (fabs(a - b) < 0.000001) return EQ;
  if (a < b) return LT;
  return GT;
}

Decide::Decide(int NUMPOINTS, const std::vector<COORDINATE> &POINTS,
               const PARAMETERS_T &PARAMETERS,
               const std::array<std::array<CONNECTORS, 15>, 15> &LCM,
               const std::array<bool, 15> &PUV)
    : NUMPOINTS(NUMPOINTS),
      COORDINATES(POINTS),
      PARAMETERS(PARAMETERS),
      LCM(LCM),
      PUV(PUV) {}

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

/**
 * @brief There exists at least one set of three consecutive data points that
 * cannot all be contained within or on a circle of radius RADIUS1.
 *
 * https://artofproblemsolving.com/wiki/index.php/Circumradius
 */
void Decide::Lic1() {
  for (int i = 0; i < NUMPOINTS - 2; ++i) {
    COORDINATE p1 = COORDINATES[i];
    COORDINATE p2 = COORDINATES[i + 1];
    COORDINATE p3 = COORDINATES[i + 2];

    // find the size of the triangle
    double a = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    double b = sqrt(pow(p2.x - p3.x, 2) + pow(p2.y - p3.y, 2));
    double c = sqrt(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2));

    double s = (a + b + c) / 2;
    double area = sqrt(s * (s - a) * (s - b) * (s - c));  // Heron's formula

    double r = (a * b * c) / (4 * area);  // radius of the circumcircle

    if (DOUBLECOMPARE(r, PARAMETERS.RADIUS1) == GT) {
      CMV[1] = true;
      return;
    }
  }
}

void Decide::Lic2() {}

void Decide::Lic3() {}

void Decide::Lic4() {}

void Decide::Lic5() {}

/**
 * @brief There exists at least one set of N_PTS consecutive data points such
 * that at least one of the points lies a distance greater than DIST from the
 * line joining the first and last of these N_PTS points. If the first and last
 * points of these N_PTS are identical, then the calculated distance to compare
 * with DIST will be the distance from the coincident point to all other points
 * of the N_PTS consecutive points. The condition is not met when NUMPOINTS < 3.
 *
 */
void Decide::Lic6() {
  if (NUMPOINTS < 3) {
    CMV[6] = false;
    return;
  }

  for (int i = 0; i < NUMPOINTS - PARAMETERS.N_PTS + 1; ++i) {
    COORDINATE p1 = COORDINATES[i];
    COORDINATE p2 = COORDINATES[i + PARAMETERS.N_PTS - 1];

    if (DOUBLECOMPARE(p1.x, p2.x) == EQ && DOUBLECOMPARE(p1.y, p2.y) == EQ) {
      // p1 and p2 are the same point
      for (int j = 0; j < NUMPOINTS; ++j) {
        if (j == i) continue;

        COORDINATE p3 = COORDINATES[j];

        double distance = sqrt(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2));

        if (DOUBLECOMPARE(distance, PARAMETERS.DIST) == GT) {
          CMV[6] = true;
          return;
        }
      }
    } else {
      // p1 and p2 are different points
      for (int j = 0; j < NUMPOINTS; ++j) {
        if (j == i || j == i + PARAMETERS.N_PTS - 1) continue;

        COORDINATE p3 = COORDINATES[j];
        // https://math.stackexchange.com/questions/2757318/distance-between-a-point-and-a-line-defined-by-2-points
        double distance = fabs((p2.x - p1.x) * (p3.y - p1.y) -
                               (p3.x - p1.x) * (p2.y - p1.y)) /
                          sqrt(pow(p2.y - p1.y, 2) + pow(p2.x - p1.x, 2));

        if (DOUBLECOMPARE(distance, PARAMETERS.DIST) == GT) {
          CMV[6] = true;
          return;
        }
      }
    }
  }
  CMV[6] = false;
}

void Decide::Lic7() {}

void Decide::Lic8() {}

void Decide::Lic9() {}

void Decide::Lic10() {}

void Decide::Lic11() {}

void Decide::Lic12() {}

void Decide::Lic13() {}

void Decide::Lic14() {}
