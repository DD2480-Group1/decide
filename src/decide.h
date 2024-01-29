#ifndef DECIDE_H
#define DECIDE_H

#include <array>
#include <vector>

const double PI = 3.1415926535

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
private:
  // Inputs
  const int NUMPOINTS; // Number of planar data points.
  const std::vector<COORDINATE>
      COORDINATES; // Array containing the coordinates of data points.
  const PARAMETERS_T PARAMETERS; // Struct holding the parameters for LICs.
  const std::array<std::array<CONNECTORS, 15>, 15>
      LCM; // Logical Connector Matrix. IMPORTANT! LCM[y][x] <-- y first then x.
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

  // Step 2.1 from specification.
  void Calc_CMV();

  void Lic0();
  void Lic1();
  void Lic2();
  void Lic3();
  void Lic4();
  void Lic5();
  void Lic6();
  void Lic7();
  void Lic8();
  void Lic9();
  void Lic10();
  void Lic11();
  void Lic12();
  void Lic13();
  void Lic14();

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
