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

  std::vector<COORDINATE> pointsB = {{0, 0}, {3, 0}, {0, 4}};
  PARAMETERS_T paramB;
  paramB.RADIUS1 = 5.0;

  std::array<std::array<CONNECTORS, 15>, 15> lcmB;
  std::array<bool, 15> puvB;

  Decide decideB(pointsB.size(), pointsB, paramB, lcmB, puvB);

  EXPECT_EQ(decideB.Lic1(), false);
}

TEST(CMV, LIC6) {
  std::vector<COORDINATE> pointsP = {{0, 0}, {3, 0}, {0, 4}};
  PARAMETERS_T paramP;
  paramP.DIST = 0.5;
  paramP.N_PTS = 1;
  std::array<std::array<CONNECTORS, 15>, 15> lcmP = {NOTUSED};
  std::array<bool, 15> puvP = {0};

  Decide decideP(pointsP.size(), pointsP, paramP, lcmP, puvP);

  EXPECT_EQ(decideP.Lic6(), true);

  std::vector<COORDINATE> pointsN = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  PARAMETERS_T paramN;
  paramN.DIST = 50;
  paramN.N_PTS = 3;
  std::array<std::array<CONNECTORS, 15>, 15> lcmN;
  std::array<bool, 15> puvN;

  Decide decideN(pointsN.size(), pointsN, paramN, lcmN, puvN);

  EXPECT_EQ(decideN.Lic6(), false);

  std::vector<COORDINATE> pointsB = {{0, 0}, {3, 0}, {0, 4}};
  PARAMETERS_T paramB;
  paramB.DIST = 4;
  paramB.N_PTS = 1;

  std::array<std::array<CONNECTORS, 15>, 15> lcmB;
  std::array<bool, 15> puvB;

  Decide decideB(pointsB.size(), pointsB, paramB, lcmB, puvB);

  EXPECT_EQ(decideB.Lic6(), false);
}
TEST(CMV, LIC11) {
  std::vector<COORDINATE> pointsP = {{5, 0}, {3, 0}, {4, 4}};
  PARAMETERS_T paramP;
  paramP.G_PTS = 1;
  std::array<std::array<CONNECTORS, 15>, 15> lcmP = {NOTUSED};
  std::array<bool, 15> puvP = {0};

  Decide decideP(pointsP.size(), pointsP, paramP, lcmP, puvP);

  EXPECT_EQ(decideP.Lic11(), true);

  std::vector<COORDINATE> pointsN = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  PARAMETERS_T paramN;
  paramN.G_PTS = 3;
  std::array<std::array<CONNECTORS, 15>, 15> lcmN;
  std::array<bool, 15> puvN;

  Decide decideN(pointsN.size(), pointsN, paramN, lcmN, puvN);

  EXPECT_EQ(decideN.Lic11(), false);

  std::vector<COORDINATE> pointsB = {{0, 0}, {3, 0}, {0, 4}};
  PARAMETERS_T paramB;
  paramB.G_PTS = 1;

  std::array<std::array<CONNECTORS, 15>, 15> lcmB;
  std::array<bool, 15> puvB;

  Decide decideB(pointsB.size(), pointsB, paramB, lcmB, puvB);

  EXPECT_EQ(decideB.Lic11(), false);
}