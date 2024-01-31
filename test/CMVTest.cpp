#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "decide.h"

TEST(CMV, LIC1_POSITIVE) {
  std::vector<COORDINATE> pointsP = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  PARAMETERS_T paramP;
  paramP.RADIUS1 = 0.5;
  std::array<std::array<CONNECTORS, 15>, 15> lcmP = {NOTUSED};
  std::array<bool, 15> puvP = {0};

  Decide decideP(pointsP.size(), pointsP, paramP, lcmP, puvP);

  EXPECT_EQ(decideP.Lic1(), true);
}
TEST(CMV, LIC1_NEGATIVE) {
  std::vector<COORDINATE> pointsN = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  PARAMETERS_T paramN;
  paramN.RADIUS1 = 6;
  std::array<std::array<CONNECTORS, 15>, 15> lcmN;
  std::array<bool, 15> puvN;

  Decide decideN(pointsN.size(), pointsN, paramN, lcmN, puvN);

  EXPECT_EQ(decideN.Lic1(), false);
}

TEST(CMV, LIC1_BOUNDRARY) {
  std::vector<COORDINATE> pointsB = {{0, 0}, {3, 0}, {0, 4}};
  PARAMETERS_T paramB;
  paramB.RADIUS1 = 5.0;

  std::array<std::array<CONNECTORS, 15>, 15> lcmB;
  std::array<bool, 15> puvB;

  Decide decideB(pointsB.size(), pointsB, paramB, lcmB, puvB);

  EXPECT_EQ(decideB.Lic1(), false);
}

TEST(CMV, LIC6_POSITIVE) {
  std::vector<COORDINATE> pointsP = {{0, 0}, {3, 0}, {0, 4}};
  PARAMETERS_T paramP;
  paramP.DIST = 0.5;
  paramP.N_PTS = 1;
  std::array<std::array<CONNECTORS, 15>, 15> lcmP = {NOTUSED};
  std::array<bool, 15> puvP = {0};

  Decide decideP(pointsP.size(), pointsP, paramP, lcmP, puvP);

  EXPECT_EQ(decideP.Lic6(), true);
}

TEST(CMV, LIC6_NEGATIVE) {
  std::vector<COORDINATE> pointsN = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  PARAMETERS_T paramN;
  paramN.DIST = 50;
  paramN.N_PTS = 3;
  std::array<std::array<CONNECTORS, 15>, 15> lcmN;
  std::array<bool, 15> puvN;

  Decide decideN(pointsN.size(), pointsN, paramN, lcmN, puvN);

  EXPECT_EQ(decideN.Lic6(), false);
}
TEST(CMV, LIC6_BOUNDRARY) {
  std::vector<COORDINATE> pointsB = {{0, 0}, {3, 0}, {0, 4}};
  PARAMETERS_T paramB;
  paramB.DIST = 4;
  paramB.N_PTS = 1;

  std::array<std::array<CONNECTORS, 15>, 15> lcmB;
  std::array<bool, 15> puvB;

  Decide decideB(pointsB.size(), pointsB, paramB, lcmB, puvB);

  EXPECT_EQ(decideB.Lic6(), false);
}

// Tests that LIC2 can calculate angle
// that is greater than PI + EPSILON
TEST(CMV, LIC2_POSITIVE) {
  // points for angle
  std::vector<COORDINATE> points = {{0, 1}, {1, 0}, {1, 2}};

  // create parameters container
  PARAMETERS_T parameters;
  parameters.EPSILON = 0.1;
  int numpoints = points.size();
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic2(), true);
}

// Tests that LIC2 can identify when there is a bad angle
// and reject it
TEST(CMV, LIC2_NEGATIVE_BAD_ANGLE) {
  // points for angle
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {1, 2}};

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  parameters.EPSILON = 0.1;
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic2(), false);
}

// Tests that lic3 can identify a triangle
// that is greater than PARAMETERS.AREA1
TEST(CMV, LIC3_POSITIVE) {
  // triangle with area 0.5
  std::vector<COORDINATE> points = {{0, 0}, {0, 1}, {1, 0}};
  int numpoints = points.size();

  PARAMETERS_T parameters;
  parameters.AREA1 = 0.4;

  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide d(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(d.Lic3(), true);
}

// Tests that lic3 can identify a triangle
// that is smaller than PARAMETERS.AREA1
TEST(CMV, LIC3_NEGATIVE) {
  // triangle with area 0.5
  std::vector<COORDINATE> points = {{0, 0}, {0, 1}, {1, 0}};

  int numpoints = points.size();

  PARAMETERS_T parameters;
  parameters.AREA1 = 0.6;

  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide d(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(d.Lic3(), false);
}

// Test if lic3 correctly sets CMV[3] when there
// exists a triangle with area == AREA1
TEST(CMV, LIC3_BOUNDRARY) {
  // triangle with area 0.5
  std::vector<COORDINATE> points = {{0, 0}, {0, 1}, {1, 0}};

  int numpoints = points.size();

  PARAMETERS_T parameters;
  parameters.AREA1 = 0.5;

  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide d(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(d.Lic3(), false);
}

// Test that LIC7 can find two points seperated by K_PTS points apart
// and have a greater length between them than LENGTH1
TEST(CMV, LIC7_POSITIVE) {
  std::vector<COORDINATE> points = {{0, 1}, {0, 2}, {1, 0}, {0, 1}, {0, 4}};

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  parameters.K_PTS = 2;
  parameters.LENGTH1 = 1.5;
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic7(), true);
}

// Test that LIC7 can find two points seperated by K_PTS points apart
// but do not have a greater length between them than LENGTH1
TEST(CMV, LIC7_NEGATIVE_LENGHT1) {
  std::vector<COORDINATE> points = {
      {0, 1},
      {0, 1},
      {1, 0},
      {0, 1},
  };

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  parameters.K_PTS = 2;
  parameters.LENGTH1 = 1.5;
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic7(), false);
}

// Tests that LIC7 can reject when numpoints is less than 3
TEST(CMV, LIC7_NEGATIVE_NUMPOINTS) {
  std::vector<COORDINATE> points = {{1, 1}, {2, 2}};

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic7(), false);
}

TEST(CMV, LIC8_POSITIVE) {
  // triangle {0,0},{0,100},{100,0} cant fit in circle with radius 1
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0},  {0, 100},
                                    {0, 0}, {0, 0}, {100, 0}};

  int numpoints = points.size();

  PARAMETERS_T parameters;
  parameters.A_PTS = 2;
  parameters.B_PTS = 2;
  parameters.RADIUS1 = 1;

  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide d(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(d.Lic8(), true);
}

TEST(CMV, LIC8_NEGATIVE) {
  // triangle {0,0},{0,1},{1,0} cant fit in circle with radius 100
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0}, {0, 1},
                                    {0, 0}, {0, 0}, {1, 0}};

  int numpoints = points.size();

  PARAMETERS_T parameters;
  parameters.A_PTS = 2;
  parameters.B_PTS = 2;
  parameters.RADIUS1 = 100;

  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide d(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(d.Lic8(), false);
}

TEST(CMV, LIC8_BOUNDRARY) {
  // triangle {0,0},{0,1},{1,0} has a circumradius
  // of (1/2)*sqrt(2)
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0}, {0, 1},
                                    {0, 0}, {0, 0}, {1, 0}};

  int numpoints = points.size();

  PARAMETERS_T parameters;
  parameters.A_PTS = 2;
  parameters.B_PTS = 2;
  parameters.RADIUS1 = 0.5 * sqrt(2.0);

  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide d(numpoints, points, parameters, lcm, puv);

  // the triangle should fit on the circle
  EXPECT_EQ(d.Lic8(), false);
}

TEST(CMV, LIC11_POSITIVE) {
  std::vector<COORDINATE> pointsP = {{5, 0}, {3, 0}, {4, 4}};
  PARAMETERS_T paramP;
  paramP.G_PTS = 1;
  std::array<std::array<CONNECTORS, 15>, 15> lcmP = {NOTUSED};
  std::array<bool, 15> puvP = {0};

  Decide decideP(pointsP.size(), pointsP, paramP, lcmP, puvP);

  EXPECT_EQ(decideP.Lic11(), true);
}

TEST(CMV, LIC11_NEGATIVE) {
  std::vector<COORDINATE> pointsN = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  PARAMETERS_T paramN;
  paramN.G_PTS = 3;
  std::array<std::array<CONNECTORS, 15>, 15> lcmN;
  std::array<bool, 15> puvN;

  Decide decideN(pointsN.size(), pointsN, paramN, lcmN, puvN);

  EXPECT_EQ(decideN.Lic11(), false);
}

TEST(CMV, LIC11_BOUNDRARY) {
  std::vector<COORDINATE> pointsB = {{0, 0}, {3, 0}, {0, 4}};
  PARAMETERS_T paramB;
  paramB.G_PTS = 1;

  std::array<std::array<CONNECTORS, 15>, 15> lcmB;
  std::array<bool, 15> puvB;

  Decide decideB(pointsB.size(), pointsB, paramB, lcmB, puvB);

  EXPECT_EQ(decideB.Lic11(), false);
}

TEST(CMV, LIC12_POSITIVE) {
  std::vector<COORDINATE> points = {{1, 1}, {2, 2}, {0, 1}, {2, 3},
                                    {0, 1}, {5, 1}, {5, 3}, {1, 0}};

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  parameters.K_PTS = 2;
  parameters.LENGTH1 = 4.8;  // 0.1 and 5.1 >= 5
  parameters.LENGTH2 = 1.6;  // 0.1 and 1.0 <= 1.5
  // dummy parameters
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic12(), true);
}

// Tests that LIC12 can reject when numpoints is less than 3
TEST(CMV, LIC12_NEGATIVE_NUMPOINTS) {
  std::vector<COORDINATE> points = {{1, 1}, {2, 2}};

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  // dummy parameters
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic12(), false);
}

// Test that LIC12 can find two points seperated by K_PTS points apart
// but do not have a greater length between them than LENGTH1
// also there are some point that has a distance less than LENGHT2
TEST(CMV, LIC12_NEGATIVE_LENGHT1) {
  std::vector<COORDINATE> points = {{1, 1}, {2, 2}, {0, 1}, {2, 3},
                                    {1, 4}, {5, 1}, {5, 3}, {1, 0}};

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  parameters.K_PTS = 2;
  parameters.LENGTH1 = 5;  // should be equal and fail
  parameters.LENGTH2 = 4;
  // dummy parameters
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic12(), false);
}

// Test that LIC12 can find two points seperated by K_PTS points apart
// and do have a greater length between them than LENGTH1
// but there are no point that has a distance less than LENGHT2
TEST(CMV, LIC12_NEGATIVE_LENGHT2) {
  std::vector<COORDINATE> points = {{1, 1}, {2, 2}, {0, 1}, {2, 3},
                                    {1, 4}, {5, 1}, {5, 3}, {1, 0}};

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  parameters.K_PTS = 2;
  parameters.LENGTH1 = 22;
  parameters.LENGTH2 = 1;
  // dummy parameters
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic12(), false);
}

TEST(CMV, LIC13_POSITIVE) {
  // triangle {0,0},{0,100},{100,0} CANT fit in circle with radius 1
  // triangle {0,0},{0,1},{1,0} CAN fit in circle with radius 100
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0},   {0, 100},
                                    {0, 1}, {0, 0}, {100, 0}, {1, 0}};

  int numpoints = points.size();

  PARAMETERS_T parameters;
  parameters.A_PTS = 2;
  parameters.B_PTS = 2;
  parameters.RADIUS1 = 1.0;
  parameters.RADIUS2 = 100.0;

  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide d(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(d.Lic8(), true);
}

TEST(CMV, LIC13_NEGATIVE) {
  // triangle {0,0},{0,10},{10,0} CAN fit in circle with radius 100
  // triangle {0,0},{0,1},{1,0} CAN fit in a circle with radius 100
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0},  {0, 10},
                                    {0, 1}, {0, 0}, {10, 0}, {1, 0}};

  int numpoints = points.size();

  PARAMETERS_T parameters;
  parameters.A_PTS = 2;
  parameters.B_PTS = 2;
  parameters.RADIUS1 = 100.0;
  parameters.RADIUS2 = 1.0;

  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide d(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(d.Lic8(), false);
}

TEST(CMV, LIC13_BOUNDRARY) {
  // triangle {0,0},{0,100},{100,0} CANT fit in circle with radius 1
  // triangle {0,0},{0,1},{1,0} fits ON the boundrary of a circle wwith radius
  // 0.5 * sqrt(2)
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0},   {0, 100},
                                    {0, 1}, {0, 0}, {100, 0}, {1, 0}};

  int numpoints = points.size();

  PARAMETERS_T parameters;
  parameters.A_PTS = 2;
  parameters.B_PTS = 2;
  parameters.RADIUS1 = 1.0;
  parameters.RADIUS2 = 0.5 * sqrt(2);

  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide d(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(d.Lic8(), true);
}
