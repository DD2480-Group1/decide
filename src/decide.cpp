#include "decide.h"

Decide::Decide(int NUMPOINTS, const std::vector<COORDINATE> &POINTS,
         const PARAMETERS_T &PARAMETERS,
         const std::array<std::array<CONNECTORS, 15>, 15> &LCM,
         const std::array<bool, 15> &PUV): NUMPOINTS(NUMPOINTS), COORDINATES(POINTS), PARAMETERS(PARAMETERS), LCM(LCM), PUV(PUV) {}

