#ifndef DECIDE_H
#define DECIDE_H

#include <cmath>

namespace Decide {
enum CONNECTORS { NOTUSED, ANDD, ORR };

typedef double *COORDINATE;

typedef CONNECTORS **CMATRIX;

typedef bool **BMATRIX;

typedef bool *VECTOR;

enum COMPTYPE { LT, EQ, GT };

struct PARAMETERS_T {
  double LENGTH1;  // Length in LICs 0, 7, 12
  double RADIUS1;  // Radius in LICs 1, 8, 13
  double EPSILON;  // Deviation from PI in LICs 2, 9
  double AREA1;    // Area in LICs 3, 10, 14
  int Q_PTS;       // No. of consecutive points in LIC 4
  int QUADS;       // No. of quadrants in LIC 4
  double DIST;     // Distance in LIC 6
  int N_PTS;       // No. of consecutive pts. in LIC 6
  int K_PTS;       // No. of int. pts. in LICs 7, 12
  int A_PTS;       // No. of int. pts. in LICs 8, 13
  int B_PTS;       // No. of int. pts. in LICs 8, 13
  int C_PTS;       // No. of int. pts. in LICs 9
  int D_PTS;       // No. of int. pts. in LICs 9
  int E_PTS;       // No. of int. pts. in LICs 10, 14
  int F_PTS;       // No. of int. pts. in LICs 10, 14
  int G_PTS;       // No. of int. pts. in LICs 11
  double LENGHT2;  // Maximum length in LIC 12
  double RADIUS2;  // Maximum radius in LIC 13
  double AREA2;    // Maximum area in LIC 14
};

// Global variable declarations

extern PARAMETERS_T PARAMETERS;
// static PARAMETERS_T PARAMETERS_2;

// X coordinates of data points
extern COORDINATE X;
// static COORDINATE X2;

// Y coordinates of data points
extern COORDINATE Y;
// static COORDINATE Y2;

// Number of data points
extern int NUMPOINTS;
// static int NUMPOINTS2;

// Logical connector matrix
extern CMATRIX LCM;
// static CMATRIX LCM;

// Preliminary unlocking matrix;
extern BMATRIX PUM;
// static BMATRIX PUM2;

// Conditions met vector
extern VECTOR CMV;
// static VECTOR CMV2;

// Final unlocking vector
extern VECTOR FUV;
// static VECTOR FUV2;

// Decision : Launch or No Launch
extern bool LAUNCH;
// static bool LAUNCH2;

// compares floating point numbers
static inline COMPTYPE DOUBLECOMPARE(double A, double B) {
  if (fabs(A - B) < 0.000001) return EQ;
  if (A < B) return LT;
  return GT;
}
void DECIDE(void);
}  // namespace Decide

#endif  // DECIDE
