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

void Decide::Lic2() {}

void Decide::Lic3() {

  bool found_greater_area = false;

  for (size_t i = 0; i < COORDINATES.size() - 2; ++i) {
    COORDINATE c1 = COORDINATES[i];
    COORDINATE c2 = COORDINATES[i + 1];
    COORDINATE c3 = COORDINATES[i + 2];

    // Formula from:
    // https://www.cuemath.com/geometry/area-of-triangle-in-coordinate-geometry/
    double area = 0.5 * fabs(c1.x * (c2.y - c3.y) + c2.x * (c3.y - c1.y) +
                             c3.x * (c1.y - c2.y));

    COMPTYPE comp = DOUBLECOMPARE(area, PARAMETERS.AREA1);

    if (comp == GT) {
      found_greater_area = true;
      break;
    }
  }

  CMV[3] = found_greater_area;
}

void Decide::Lic4() {}

void Decide::Lic5() {}

void Decide::Lic6() {}

void Decide::Lic7() {}

void Decide::Lic8() {

  if (NUMPOINTS < 5) {
    CMV[8] = false;
    return;
  }

  bool found_larger_triangle = false;

  auto dist_lambda = [](const COORDINATE &a, const COORDINATE &b) -> double {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
  };

  for (int i = 0; i < NUMPOINTS; ++i) {
    if (i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2 >= NUMPOINTS) {
      break;
    }

    COORDINATE c1 = COORDINATES[i];
    COORDINATE c2 = COORDINATES[i + PARAMETERS.A_PTS + 1];
    COORDINATE c3 = COORDINATES[i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2];

    double a = dist_lambda(c1, c2);
    double b = dist_lambda(c1, c3);
    double c = dist_lambda(c2, c3);

    // Based on this formula:
    // https://mathworld.wolfram.com/Circumradius.html
    double circumradius = (a * b * c) / sqrt((a + b + c) * (b + c - a) *
                                             (c + a - b) * (a + b - c));

    COMPTYPE comp = DOUBLECOMPARE(circumradius, PARAMETERS.RADIUS1);

    if (comp == GT) {
      found_larger_triangle = true;
      break;
    }
  }

  CMV[8] = found_larger_triangle;
}

void Decide::Lic9() {}

void Decide::Lic10() {}

void Decide::Lic11() {}

void Decide::Lic12() {}

void Decide::Lic13() {

  if (NUMPOINTS < 5) {
    CMV[13] = false;
    return;
  }

  bool found_larger_triangle = false;
  bool found_smaller_triangle = false;

  auto dist_lambda = [](const COORDINATE &a, const COORDINATE &b) -> double {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
  };

  for (int i = 0; i < NUMPOINTS; ++i) {
    if (i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2 >= NUMPOINTS) {
      break;
    }

    COORDINATE c1 = COORDINATES[i];
    COORDINATE c2 = COORDINATES[i + PARAMETERS.A_PTS + 1];
    COORDINATE c3 = COORDINATES[i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2];

    double a = dist_lambda(c1, c2);
    double b = dist_lambda(c1, c3);
    double c = dist_lambda(c2, c3);

    // Based on this formula:
    // https://mathworld.wolfram.com/Circumradius.html
    double circumradius = (a * b * c) / sqrt((a + b + c) * (b + c - a) *
                                             (c + a - b) * (a + b - c));

    COMPTYPE comp1 = DOUBLECOMPARE(circumradius, PARAMETERS.RADIUS1);
    COMPTYPE comp2 = DOUBLECOMPARE(circumradius, PARAMETERS.RADIUS2);

    if (comp1 == GT) {
      found_larger_triangle = true;
    }

    if (comp2 != GT) {
      found_larger_triangle = true;
    }

    if (found_larger_triangle && found_smaller_triangle) {
      break;
    }
  }

  CMV[13] = found_smaller_triangle && found_larger_triangle;
}

void Decide::Lic14() {}
