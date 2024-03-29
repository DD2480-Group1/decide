#ifndef DECIDE_H
#define DECIDE_H

#include "gtest/gtest.h"
#include <array>
#include <vector>

const double PI = 3.1415926535;

enum CONNECTORS { NOTUSED = 777, ORR, ANDD };

// Less than, equal to, greater than
enum COMPTYPE { LT = 1111, EQ, GT };

struct COORDINATE {
  double x;
  double y;
};

struct PARAMETERS_T {
  double LENGTH1; // Length in LICs 0, 7, 12
  double RADIUS1; // Radius in LICs 1, 8, 13
  double EPSILON; // Deviation from PI in LICs 2, 9
  double AREA1;   // Area in LICs 1, 8, 13
  int Q_PTS;      // No. of consecutive points in LIC 4
  int QUADS;      // No. of quadrants in LIC 4
  double DIST;    // Distance in LIC 6
  int N_PTS;      // No. of consecutive pts. in LIC 6
  int K_PTS;      // No. of int. pts. in LICs 7, 12
  int A_PTS;      // No. of int. pts. in LICs 8, 13
  int B_PTS;      // No. of int. pts. in LICs 8, 13
  int C_PTS;      // No. of int. pts. in LIC 9
  int D_PTS;      // No. of int. pts. in LIC 9
  int E_PTS;      // No. of int. pts. in LICS 10, 14
  int F_PTS;      // No. of int. pts. in LICS 10, 14
  int G_PTS;      // No. of int. pts. in LIC 11
  double LENGTH2; // Maximum length in LIC 12
  double RADIUS2; // Maximum radius in LIC 13
  double AREA2;   // Maximum area in LIC 14
};

class Decide {
  // LIC0
  FRIEND_TEST(CMV, LIC0_POSITIVE);
  FRIEND_TEST(CMV, LIC0_NEGATIVE);
  // LIC1
  FRIEND_TEST(CMV, LIC1_POSITIVE);
  FRIEND_TEST(CMV, LIC1_NEGATIVE);
  FRIEND_TEST(CMV, LIC1_BOUNDRARY);
  // LIC2
  FRIEND_TEST(CMV, LIC2_POSITIVE);
  FRIEND_TEST(CMV, LIC2_NEGATIVE_BAD_ANGLE);
  // LIC3
  FRIEND_TEST(CMV, LIC3_POSITIVE);
  FRIEND_TEST(CMV, LIC3_NEGATIVE);
  FRIEND_TEST(CMV, LIC3_BOUNDRARY);
  // LIC4
  FRIEND_TEST(CMV, LIC4_POSITIVE);
  FRIEND_TEST(CMV, LIC4_NEGATIVE);
  // LIC5
  FRIEND_TEST(CMV, LIC5_POSITIVE);
  FRIEND_TEST(CMV, LIC5_NEGATIVE);
  // LIC6
  FRIEND_TEST(CMV, LIC6_POSITIVE);
  FRIEND_TEST(CMV, LIC6_NEGATIVE);
  FRIEND_TEST(CMV, LIC6_BOUNDRARY);
  // LIC7
  FRIEND_TEST(CMV, LIC7_POSITIVE);
  FRIEND_TEST(CMV, LIC7_NEGATIVE_NUMPOINTS);
  FRIEND_TEST(CMV, LIC7_NEGATIVE_LENGHT1);
  // LIC8
  FRIEND_TEST(CMV, LIC8_POSITIVE);
  FRIEND_TEST(CMV, LIC8_NEGATIVE);
  FRIEND_TEST(CMV, LIC8_BOUNDRARY);
  // LIC9
  FRIEND_TEST(CMV, LIC9_POSITIVE);
  FRIEND_TEST(CMV, LIC9_NEGATIVE);
  // LIC10
  FRIEND_TEST(CMV, LIC10_POSITIVE);
  FRIEND_TEST(CMV, LIC10_NEGATIVE);
  // LIC11
  FRIEND_TEST(CMV, LIC11_POSITIVE);
  FRIEND_TEST(CMV, LIC11_NEGATIVE);
  FRIEND_TEST(CMV, LIC11_BOUNDRARY);
  // LIC12
  FRIEND_TEST(CMV, LIC12_POSITIVE);
  FRIEND_TEST(CMV, LIC12_NEGATIVE_NUMPOINTS);
  FRIEND_TEST(CMV, LIC12_NEGATIVE_LENGHT1);
  FRIEND_TEST(CMV, LIC12_NEGATIVE_LENGHT2);
  // LIC13
  FRIEND_TEST(CMV, LIC13_POSITIVE);
  FRIEND_TEST(CMV, LIC13_NEGATIVE);
  FRIEND_TEST(CMV, LIC13_BOUNDRARY);
  // LIC14
  FRIEND_TEST(CMV, LIC14_POSITIVE);
  FRIEND_TEST(CMV, LIC14_NEGATIVE);
  // DUMMY TEST
  FRIEND_TEST(CMV, LIC11);

  FRIEND_TEST(LAUNCH, LAUNCH_POSITIVE);
  FRIEND_TEST(LAUNCH, LAUNCH_POSITIVE2);
  FRIEND_TEST(LAUNCH, LAUNCH_POSITIVE3);
  FRIEND_TEST(LAUNCH, LAUNCH_NEGATIVE);
  FRIEND_TEST(LAUNCH, LAUNCH_NEGATIVE2);

private:
  // Inputs
  const int NUMPOINTS; // Number of planar data points.
  const std::vector<COORDINATE>
      COORDINATES; // Array containing the coordinates of data points.
  const PARAMETERS_T PARAMETERS; // Struct holding the parameters for LICs.
  const std::array<std::array<CONNECTORS, 15>, 15>
      LCM; // Logical Connector Matrix. IMPORTANT! LCM[y][x] <-- y first then
           // x.
  const std::array<bool, 15> PUV; // Preliminary unlocking vector.

  // Outputs
  bool LAUNCH;
  std::array<bool, 15> CMV; // Conditions Met Vector.
  std::array<std::array<bool, 15>, 15>
      PUM; // Preliminary Unlocking Matrix. IMPORTANT! PUM[y][x] <-- y first
           // then x.
  std::array<bool, 15> FUV; // Final Unlocking Vector.

  // Methods
  // Method for comparing doubles.
  COMPTYPE DOUBLECOMPARE(double A, double B) const;
  // Method for calculating the angle formed by three points.
  double COMPUTEANLGE(const COORDINATE &point1, const COORDINATE &point2,
                      const COORDINATE &point3);
  // Method for validating the points forming an angle
  bool VALIDATEANGLE(const COORDINATE &point1, const COORDINATE &point2,
                     const COORDINATE &point3);

  // Step 2.1 from specification.
  void Calc_CMV();

  bool Lic0();
  bool Lic1();
  bool Lic2();
  bool Lic3();
  bool Lic4();
  bool Lic5();
  bool Lic6();
  bool Lic7();
  bool Lic8();
  bool Lic9();
  bool Lic10();
  bool Lic11();
  bool Lic12();
  bool Lic13();
  bool Lic14();

  // Step 2.2 from specification.
  void Calc_PUM();

  // Step 2.3 from specification.
  void Calc_FUV();

  // 2.4 from specification.
  void Calc_LAUNCH();

public:
  Decide(int NUMPOINTS, const std::vector<COORDINATE> &POINTS,
         const PARAMETERS_T &PARAMETERS,
         const std::array<std::array<CONNECTORS, 15>, 15> &LCM,
         const std::array<bool, 15> &PUV);

  // Call functions for 2.1 - 2.4 and print answer to stdout.
  void decide();

  // Debug function that prints all member variables to stdout.
  void debugprint() const;
};

#endif
