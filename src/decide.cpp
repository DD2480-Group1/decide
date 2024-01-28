#include "decide.h"
#include "iostream"
namespace Decide {

// Global variable declarations

PARAMETERS_T PARAMETERS;
// static PARAMETERS_T PARAMETERS_2;

// X coordinates of data points
COORDINATE X;
// static COORDINATE X2;

// Y coordinates of data points
COORDINATE Y;
// static COORDINATE Y2;

// Number of data points
int NUMPOINTS;
// static int NUMPOINTS2;

// Logical connector matrix
CMATRIX LCM;
// static CMATRIX LCM;

// Preliminary unlocking matrix;
BMATRIX PUM;
// static BMATRIX PUM2;

// Conditions met vector
VECTOR CMV;
// static VECTOR CMV2;

// Final unlocking vector
VECTOR FUV;
// static VECTOR FUV2;

// Decision : Launch or No Launch
bool LAUNCH;
// static bool LAUNCH2;

void DECIDE(void) { std::cout << "hi from decide.cpp" << std::endl; }

}  // namespace Decide