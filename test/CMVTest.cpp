#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "decide.h"

TEST(CMV, LIC1) {
  std::vector<COORDINATE> pointsP = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  PARAMETERS_T paramP;
  paramP.RADIUS1 = 0.5;
  std::array<std::array<CONNECTORS, 15>, 15> lcmP = {NOTUSED};
  std::array<bool, 15> puvP = {0};

  Decide decideP(pointsP.size(), pointsP, paramP, lcmP, puvP);

  EXPECT_EQ(decideP.Lic1(), true);

  std::vector<COORDINATE> pointsN = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  PARAMETERS_T paramN;
  paramN.RADIUS1 = 6;
  std::array<std::array<CONNECTORS, 15>, 15> lcmN;
  std::array<bool, 15> puvN;

  Decide decideN(pointsN.size(), pointsN, paramN, lcmN, puvN);

  EXPECT_EQ(decideN.Lic1(), false);
}

TEST(CMV, LIC6) {
   
}
TEST(CMV, LIC11) {}