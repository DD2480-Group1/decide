#include "decide.h"
#include <cstdio>

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

bool Decide::Lic0() {
    // Iterate through consecutive pairs of points
    for (int i = 0; i < NUMPOINTS - 1; ++i){

      // Calculate the distance between consecutive points
      double distance = sqrt(pow(COORDINATES[i + 1].x - COORDINATES[i].x, 2) +
      pow(COORDINATES[i + 1].y - COORDINATES[i].y, 2));
      
      // Check if the distance is greater than LENGTH1
      if (distance > PARAMETERS.LENGTH1) {

      // Set the corresponding CMV element to true
       return true;
      
      }
    }

      return false;
  }
  ;

void Decide::Lic1() {}

void Decide::Lic2() {}

void Decide::Lic3() {}

void Decide::Lic4() {}

bool Decide::Lic5() {

  // Iterate through consecutive pairs of data points
  for (int i = 0; i < NUMPOINTS - 1; i++) {
    //// Check if X[j] - X[i] < 0
    if (COORDINATES[i + 1].x - COORDINATES[i].x < 0){
      
      // The condition is met, set CMV[4] to true
       return true;
    

    }

  }

      return false;
}

void Decide::Lic6() {}

void Decide::Lic7() {}

void Decide::Lic8() {}

void Decide::Lic9() {}

bool Decide::Lic10() {

  if (NUMPOINTS < 5) {
    return  false;

  }

  for (int i = 0; i < NUMPOINTS - 2 - PARAMETERS.E_PTS - PARAMETERS.F_PTS; ++i){
    for (int j = i + PARAMETERS.E_PTS + i; j < i + PARAMETERS.E_PTS + PARAMETERS.F_PTS + 2 && j < NUMPOINTS - 1; ++j) {
      for (int k = j + PARAMETERS.F_PTS + 1; k < NUMPOINTS && k < j + PARAMETERS.F_PTS + 2; ++k) {
        // Calculate the area of the triangle formed by points (i, j, k)
                double area = 0.5 * fabs((COORDINATES[i].x * (COORDINATES[j].y - COORDINATES[k].y)) +
                                         (COORDINATES[j].x * (COORDINATES[k].y - COORDINATES[i].y)) +
                                         (COORDINATES[k].x * (COORDINATES[i].y - COORDINATES[j].y)));

                if (area > PARAMETERS.AREA1) {
                  // Set CMV[9] to true if condition is met
                    return true;
                }
          
        }
    }
  
  }

    return false;
}

void Decide::Lic11() {}

void Decide::Lic12() {}

void Decide::Lic13() {}

void Decide::Lic14() {}
