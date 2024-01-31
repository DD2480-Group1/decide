#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "decide.h"

// Test case for Lic0() returning true
TEST(CMV, LIC0_POSITIVE){
  // Define input points and parameters
  std::vector<COORDINATE> points = {
      {0, 0}, {3, 4}, {8, 10}, {12, 15}  // Ensure distance between consecutive points is greater than LENGTH1
  };

  PARAMETERS_T parameters;
  parameters.LENGTH1 = 5.0;  // LENGTH1 (assuming LENGTH1 is set to 5.0)
      // other parameter values
  
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  // Create Decide object with the provided points and parameters
  Decide decide(points.size(), points, parameters, lcm, puv);

  // Ensure the function returns true since distances are greater than LENGTH1
  EXPECT_TRUE(decide.Lic0());
}

// Test case for Lic0() returning false
TEST(CMV, LIC0_NEGATIVE) {
  // Define input points and parameters
  std::vector<COORDINATE> points = {
      {0, 0}, {1, 1}, {2, 2}, {3, 3}  // Ensure distance between consecutive points is not greater than LENGTH1
  };

  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  PARAMETERS_T parameters;
  parameters.LENGTH1 = 5.0; 

  // Create Decide object with the provided points and parameters
  Decide decide(points.size(), points, parameters, lcm, puv);

  // Ensure the function returns false since distances are not greater than LENGTH1
  EXPECT_FALSE(decide.Lic0());
}

TEST(CMV, LIC1_POSITIVE) {
  std::vector<COORDINATE> pointsP = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  PARAMETERS_T paramP;
  paramP.RADIUS1 = 0.5;
  std::array<std::array<CONNECTORS, 15>, 15> lcmP; //= {NOTUSED};
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

 TEST(CMV, LIC4_POSITIVE) {
  std::vector<COORDINATE> points2 = {{0, 0}, {-1, 1}, {-2, 2}};

  PARAMETERS_T parameters;
  parameters.Q_PTS = 3;
  parameters.QUADS = 1;
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide2(points2.size(), points2, parameters, lcm, puv);
  
  EXPECT_EQ(decide2.Lic4(), true);
}

TEST(CMV, LIC4_NEGATIVE) {
  std::vector<COORDINATE> points = {{0, 0}, {1, 1}, {2, 2}};

  PARAMETERS_T parameters;
  parameters.Q_PTS = 3;
  parameters.QUADS = 1;
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide2(points.size(), points, parameters, lcm, puv);

  // EXPECT_EQ(decide.Lic11(), false);
  EXPECT_EQ(decide2.Lic4(), false);
}

// Test case for Lic5() returning true
TEST(CMV, LIC5_POSITIVE) {
  // Define input points and parameters
  std::vector<COORDINATE> points = {
      {1, 1},{0, 0},{3, 3},{2, 2},   // Ensure X[j] - X[i] < 0 for at least one pair of consecutive points
  };

  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  PARAMETERS_T parameters;

  Decide decide(points.size(), points, parameters, lcm, puv);

  // Ensure the function returns true since X[j] - X[i] < 0 for at least one pair of consecutive points
  EXPECT_TRUE(decide.Lic5());
}

// Test case for Lic5() returning false
TEST(CMV, LIC5_NEGATIVE) {

  std::vector<COORDINATE> points = {
      {0, 0}, {1, 1}, {2, 2}, {3, 3}  // Ensure X[j] - X[i] >= 0 for all pairs of consecutive points
  };

  PARAMETERS_T parameters;
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;
  // Create Decide object with the provided points
  Decide decide(points.size(), points, parameters, lcm, puv);

  // Ensure the function returns false since X[j] - X[i] >= 0 for all pairs of consecutive points
  EXPECT_FALSE(decide.Lic5());
}

TEST(CMV, LIC6_POSITIVE) {
  std::vector<COORDINATE> pointsP = {{0, 0}, {3, 0}, {0, 4}};
  PARAMETERS_T paramP;
  paramP.DIST = 0.5;
  paramP.N_PTS = 1;
  std::array<std::array<CONNECTORS, 15>, 15> lcmP; //= {NOTUSED};
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

TEST(CMV, LIC9_POSITIVE) {
  std::vector<COORDINATE> points = {{0,0}, {0,1}, {1,1}, {1,0}, {-1,1}};

  PARAMETERS_T parameters;
  parameters.D_PTS = 1;
  parameters.C_PTS = 1;
  parameters.EPSILON = 2;

  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide2(points.size(), points, parameters, lcm, puv);

  EXPECT_EQ(decide2.Lic9(), true);
}

TEST(CMV, LIC9_NEGATIVE) {
  std::vector<COORDINATE> points = { {0,0}, {0,1}, {1,1}, {1,0}, {2,1}};

  PARAMETERS_T parameters;
  parameters.D_PTS = 1;
  parameters.C_PTS = 1;
  parameters.EPSILON = 2;

  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide2(points.size(), points, parameters, lcm, puv);

  EXPECT_EQ(decide2.Lic9(), false);
}

// Test case for Decide::Lic10() returning true when at least one triangle has area greater than AREA1
TEST(CMV, LIC10_POSITIVE) {
  // Define input points and parameters
  std::vector<COORDINATE> points = {
      {0, 0}, {1, 0}, {0, 20}, {3, 1}, {20, 0}  // Ensure area of at least one triangle is greater than AREA1
  };

  PARAMETERS_T parameters = {
      0,  // LENGTH1
      0,  // RADIUS1
      0,  // EPSILON
      5,  // AREA1: Set to a value that the area of at least one triangle formed by the input points will exceed
      0,  // Q_PTS
      0,  // QUADS
      0,  // DIST
      0,  // N_PTS
      0,  // K_PTS
      0,  // A_PTS
      0,  // B_PTS
      0,  // C_PTS
      0,  // D_PTS
      1,  // E_PTS
      1,  // F_PTS
      0,  // G_PTS
      0,  // LENGTH2
      0,  // RADIUS2
      0   // AREA2
  };

  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv = {0};

  Decide decide(points.size(), points, parameters, lcm, puv);

  // Ensure the function returns true since the condition is met for at least one triangle
  EXPECT_TRUE(decide.Lic10());
}

// Test case for Decide::Lic10() returning true when all triangles have area within threshold
TEST(CMV, LIC10_NEGATIVE) {
  // Define input points and parameters
  std::vector<COORDINATE> points = {
      {0, 0}, {1, 0}, {0, 1}, {1, 1}, {2, 2}  // Ensure area of all triangles is within threshold
  };

  PARAMETERS_T parameters = {
      10,  // LENGTH1
      0,   // RADIUS1
      0,   // EPSILON
      10,  // AREA1: Set to a value that no triangle formed by the input points will exceed
      0,   // Q_PTS
      0,   // QUADS
      0,   // DIST
      0,   // N_PTS
      0,   // K_PTS
      0,   // A_PTS
      0,   // B_PTS
      0,   // C_PTS
      0,   // D_PTS
      1,   // E_PTS
      1,   // F_PTS
      0,   // G_PTS
      0,   // LENGTH2
      0,   // RADIUS2
      0    // AREA2
  };

  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv = {0};

  Decide decide(points.size(), points, parameters, lcm, puv);

  // Ensure the function returns false since the condition is not met for any triangle
  EXPECT_FALSE(decide.Lic10());
}

TEST(CMV, LIC11_POSITIVE) {
  std::vector<COORDINATE> pointsP = {{5, 0}, {3, 0}, {4, 4}};
  PARAMETERS_T paramP;
  paramP.G_PTS = 1;
  std::array<std::array<CONNECTORS, 15>, 15> lcmP; //= {NOTUSED};
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

  EXPECT_EQ(d.Lic13(), true);
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

  EXPECT_EQ(d.Lic13(), false);
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

  EXPECT_EQ(d.Lic13(), true);
}

TEST(CMV, LIC14_POSITIVE) {
  std::vector<COORDINATE> points = {{0,0},{0,4},{3,3},{4,0},{8,0},{5,5}};

  PARAMETERS_T parameters;
  parameters.E_PTS = 1;
  parameters.F_PTS = 1;
  parameters.AREA1 = 7;
  parameters.AREA2 = 16;

  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(points.size(), points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic14(), true);
}

TEST(CMV, LIC14_NEGATIVE){
  std::vector<COORDINATE> points = { {0,0},{0,4},{4,4},{4,0},{1,0}};

  PARAMETERS_T parameters;
  parameters.E_PTS = 1;
  parameters.F_PTS = 1;
  parameters.AREA1= 6;
  parameters.AREA2= 16;

  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(points.size(), points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic14(), false);
}