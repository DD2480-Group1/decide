#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "decide.h"

// Positive test case for LIC0(), 
// check that it can find two consecutive points 
// that are a greater distance of LENGTH1 apart
// Expected value TRUE
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

// Negative test case for LIC0(),
// if no two consecutive points are apart a greater distance
// than LENGTH1, the LIC is not met
// Expected value FALSE 
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

// Positive test case LIC1(),
// if three consecutive data points forms an area
// check that at least one point is outside a circles radius of RADIUS1
// this is done by calculating the area of the triangle, and then the circumcircle of the triangle
// In this case, the radius of the circumcircle should be greater than the RADIUS1
// Expected value TRUE
TEST(CMV, LIC1_POSITIVE) {
  std::vector<COORDINATE> pointsP = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  
  PARAMETERS_T paramP;
  paramP.RADIUS1 = 0.5;
  std::array<std::array<CONNECTORS, 15>, 15> lcmP;
  std::array<bool, 15> puvP = {0};

  Decide decideP(pointsP.size(), pointsP, paramP, lcmP, puvP);
  
  // Ensure the function returns true
  EXPECT_EQ(decideP.Lic1(), true);
}

// Negative test case for LIC1(),
// opposite of the positive case, since the RADIUS1 is now 6,
// the calculated radius of the circumcircle should be less than RADIUS1
// Expected value FALSE
TEST(CMV, LIC1_NEGATIVE) {
  std::vector<COORDINATE> pointsN = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  PARAMETERS_T paramN;
  paramN.RADIUS1 = 6;
  std::array<std::array<CONNECTORS, 15>, 15> lcmN;
  std::array<bool, 15> puvN;

  Decide decideN(pointsN.size(), pointsN, paramN, lcmN, puvN);

  EXPECT_EQ(decideN.Lic1(), false);
}

// Boundary test case for LIC1(),
// Test the special case of a boundrary, when the radius of the circumcircle
// is equal to the RADIUS1, meaning all points are either on or inside the RADIUS1 circle
// This should result in the LIC condition not being met
// Expected value FALSE
TEST(CMV, LIC1_BOUNDRARY) {
  std::vector<COORDINATE> pointsB = {{0, 0}, {3, 0}, {0, 4}};
  PARAMETERS_T paramB;
  paramB.RADIUS1 = 5.0;

  std::array<std::array<CONNECTORS, 15>, 15> lcmB;
  std::array<bool, 15> puvB;

  Decide decideB(pointsB.size(), pointsB, paramB, lcmB, puvB);

  EXPECT_EQ(decideB.Lic1(), false);
}

// Positive test for LIC2(), 
// Test that it can calculate an angle formed by three consecutive points
// where point two is the vertex, that is less than PI + EPSILON
// Expected value TRUE
TEST(CMV, LIC2_POSITIVE) {
  // points for angle, angle should be ~0.785 rads
  std::vector<COORDINATE> points = {{0, 1}, {1, 0}, {1, 2}};

  // create parameters container
  PARAMETERS_T parameters;
  parameters.EPSILON = 0.1; // condition should be pi - 1 = ~2.14
  // 2.14 > 0.785 => CONDITION MET
  int numpoints = points.size();
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(numpoints, points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic2(), true);
}

// Negative tests for LIC2(), 
// can identify when there is a bad angle (two points are on eachother)
// and reject it
// expected value FALSE
TEST(CMV, LIC2_NEGATIVE_BAD_ANGLE) {
  // points for angle, p1 and p2 are the same => CONDITION REJECT
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

// Positive test for LIC3(), 
// Tests that it can identify a triangle from three consecutive points
// that has a greater area than PARAMETERS.AREA1
// Expected value TRUE
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

// Negative tests for LIC3(),
// Tests that it can identify when there exists no triangle
// that has greater area than PARAMETERS.AREA1
// Expected value FALSE
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

// Negative tests for LIC3(),
// Test if LIC3 correctly rejects a triangle with area == AREA1,
// since the area must be greater than AREA1
// Expected value FALSE
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

// Positive tests for LIC4(),
// Test that it can correctly identify each consecutive point being in a quadrant
// and check that the amount if different quadrants that the points cover
// is more than QUADS
// Expected value TRUE
TEST(CMV, LIC4_POSITIVE) {
  // these points will result in 2 different quadrants being covered
  std::vector<COORDINATE> points2 = {{0, 0}, {-1, 1}, {-2, 2}};

  PARAMETERS_T parameters;
  parameters.Q_PTS = 3;
  parameters.QUADS = 1; // we check that more than 1 quadrant is covered => 
                        // 2 > 1 => CONDITION MET
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide2(points2.size(), points2, parameters, lcm, puv);
  
  EXPECT_EQ(decide2.Lic4(), true);
}

// Negative test for LIC4(),
// Test that it can identify when there are no three consecutive points
// that cover more than QUADS quadrants
// Expected value FALSE
TEST(CMV, LIC4_NEGATIVE) {
  // all points are in quadrant I
  std::vector<COORDINATE> points = {{0, 0}, {1, 1}, {2, 2}};

  PARAMETERS_T parameters;
  parameters.Q_PTS = 3;
  parameters.QUADS = 1; // 1 == 1 => CONDITION REJECTED
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide2(points.size(), points, parameters, lcm, puv);

  EXPECT_EQ(decide2.Lic4(), false);
}

// Positive test case for LIC5(),
// Test that it can find one set of two consecutive points
// where point2.x - point1.x < 0
// Expected value TRUE
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

// Negative test case for LIC5(),
// Test that LIC5 can identify when no two consecutive points
// have a x-axise distance less than zero
// Expected value FALSE
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

// Positive test case for LIC6(),
// Test whether LIC6 will return true if distance is larger than DIST
// Expected value TRUE
TEST(CMV, LIC6_POSITIVE) {
  std::vector<COORDINATE> pointsP = {{0, 0}, {3, 0}, {12, 4}, {3, 4}, {9, 10}};
  // create parameters container
  PARAMETERS_T paramP;
  paramP.DIST = 0.5;
  paramP.N_PTS = 3;
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcmP;
  std::array<bool, 15> puvP = {0};

  Decide decideP(pointsP.size(), pointsP, paramP, lcmP, puvP);

  EXPECT_EQ(decideP.Lic6(), true);
}

// Negative test case for LIC6(),
// Test whether LIC6 will return true if distance is smaller than DIST
// Expected value FALSE
TEST(CMV, LIC6_NEGATIVE) {
  std::vector<COORDINATE> pointsN = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  // distance=0
  // create parameters container
  
  PARAMETERS_T paramN;
  paramN.DIST = 50;
  paramN.N_PTS = 3;
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcmN;
  std::array<bool, 15> puvN;

  Decide decideN(pointsN.size(), pointsN, paramN, lcmN, puvN);

  EXPECT_EQ(decideN.Lic6(), false);
}

// Boundrary test case for LIC6(),
// Test whether LIC6 will return false if distance is equal to DIST
// Expected value FALSE
TEST(CMV, LIC6_BOUNDRARY) {
  std::vector<COORDINATE> pointsB = {{0, 0}, {3, 0}, {0, 4}, {3, 4}, {3, 4}};
  // 
  // create parameters container
  PARAMETERS_T paramB;
  paramB.DIST = 5;
  paramB.N_PTS = 3;
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcmB;
  std::array<bool, 15> puvB;

  Decide decideB(pointsB.size(), pointsB, paramB, lcmB, puvB);

  EXPECT_EQ(decideB.Lic6(), false);
}

// Positive test case for LIC7(),
// Test that LIC7 can find two points seperated by K_PTS points apart
// and have a greater length between them than LENGTH1
// Expected value TRUE
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

// Negative test case for LIC7(),
// Test that LIC7 can find two points seperated by K_PTS points apart
// but do not have a greater length between them than LENGTH1
// Expected value FALSE
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

// Negative test case for LIC7(),
// Tests that LIC7 can reject when numpoints is less than 3
// Expected value FALSE
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

// Positive test case for LIC8(),
// Test whether the LIC8 will return true when three points can't be included in a circle
// Expected value TRUE
TEST(CMV, LIC8_POSITIVE) {
  // triangle {0,0},{0,100},{100,0} cant fit in circle with radius 1
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0},  {0, 100},
                                    {0, 0}, {0, 0}, {100, 0}};

  int numpoints = points.size();
  // create parameters container
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

// Negative test case for LIC8(),
// Test whether the LIC8 will return false when three points can be included in a circle
// Expected value FALSE
TEST(CMV, LIC8_NEGATIVE) {
  // triangle {0,0},{0,1},{1,0} cant fit in circle with radius 100
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0}, {0, 1},
                                    {0, 0}, {0, 0}, {1, 0}};

  int numpoints = points.size();
  // create parameters container
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

// Boundrary test case for LIC8(),
// Test whether the LIC8 will return false when three points can be exactly on the circle
// Expected value FALSE
TEST(CMV, LIC8_BOUNDRARY) {
  // triangle {0,0},{0,1},{1,0} has a circumradius
  // of (1/2)*sqrt(2)
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0}, {0, 1},
                                    {0, 0}, {0, 0}, {1, 0}};

  int numpoints = points.size();
  // create parameters container
  PARAMETERS_T parameters;
  parameters.A_PTS = 2;
  parameters.B_PTS = 2;
  parameters.RADIUS1 = 0.5 * sqrt(2.0);
  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;
  Decide d(numpoints, points, parameters, lcm, puv);

  // the triangle should fit on the circle
  EXPECT_EQ(d.Lic8(), false);
}

// Positive test case for LIC9(),
// Tests that LIC9 can reject when points the angle is small
// Expected value TRUE
TEST(CMV, LIC9_POSITIVE) {
  std::vector<COORDINATE> points = {{0,0}, {0,1}, {1,1}, {1,0}, {-1,1}};
  //angle=PI/4<PI-2
  // create parameters container
  PARAMETERS_T parameters;
  parameters.D_PTS = 1;
  parameters.C_PTS = 1;
  parameters.EPSILON = 2;
  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide2(points.size(), points, parameters, lcm, puv);

  EXPECT_EQ(decide2.Lic9(), true);
}

// Negative test case for LIC9(),
// Tests that LIC9 can reject when points the angle is large 
// Expected value FALSE
TEST(CMV, LIC9_NEGATIVE) {
  std::vector<COORDINATE> points = { {0,0}, {0,1}, {1,1}, {1,0}, {2,1}};
  //PI>angle=3PI/4>PI-2
  // create parameters container
  PARAMETERS_T parameters;
  parameters.D_PTS = 1;
  parameters.C_PTS = 1;
  parameters.EPSILON = 2;
  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide2(points.size(), points, parameters, lcm, puv);

  EXPECT_EQ(decide2.Lic9(), false);
}

// Positive test case for LIC10(),
// Test case for Decide::Lic10() returning true when 
// at least one triangle has area greater than AREA1
// Expected value TRUE
TEST(CMV, LIC10_POSITIVE) {
  // Define input points and parameters
  std::vector<COORDINATE> points = {
      {0, 0}, {1, 0}, {0, 20}, {3, 1}, {20, 0}  // Ensure area of at least one triangle is greater than AREA1
  };
  // create parameters container
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
  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv = {0};

  Decide decide(points.size(), points, parameters, lcm, puv);

  // Ensure the function returns true since the condition is met for at least one triangle
  EXPECT_TRUE(decide.Lic10());
}

// Negative test case for LIC10(),
// Test case for Decide::Lic10() returning true when all triangles have area within threshold
// Expected value FALSE
TEST(CMV, LIC10_NEGATIVE) {
  // Define input points and parameters
  std::vector<COORDINATE> points = {
      {0, 0}, {1, 0}, {0, 1}, {1, 1}, {2, 2}  // Ensure area of all triangles is within threshold
  };
  // create parameters container
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
  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv = {0};

  Decide decide(points.size(), points, parameters, lcm, puv);

  // Ensure the function returns false since the condition is not met for any triangle
  EXPECT_FALSE(decide.Lic10());
}

// Positive test case for LIC11(),
// Tests that LIC11 can pass when points x[i]>x[j] at some point
// Expected value TRUE
TEST(CMV, LIC11_POSITIVE) {
  std::vector<COORDINATE> pointsP = {{5, 0}, {3, 0}, {4, 4}};
  // create parameters container
  PARAMETERS_T paramP;
  paramP.G_PTS = 1;
  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcmP; //= {NOTUSED};
  std::array<bool, 15> puvP = {0};

  Decide decideP(pointsP.size(), pointsP, paramP, lcmP, puvP);

  EXPECT_EQ(decideP.Lic11(), true);
}

// Negative test case for LIC11(),
// Tests that LIC11 can reject when points x[i]<x[j]
// Expected value FALSE
TEST(CMV, LIC11_NEGATIVE) {
  std::vector<COORDINATE> pointsN = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
  // create parameters container
  PARAMETERS_T paramN;
  paramN.G_PTS = 3;
  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcmN;
  std::array<bool, 15> puvN;

  Decide decideN(pointsN.size(), pointsN, paramN, lcmN, puvN);

  EXPECT_EQ(decideN.Lic11(), false);
}

// Boundrary test case for LIC11(),
// Tests that LIC11 can reject when points x[i]=x[j]
// Expected value FALSE
TEST(CMV, LIC11_BOUNDRARY) {
  std::vector<COORDINATE> pointsB = {{0, 0}, {3, 0}, {0, 4}};
  // create parameters container
  PARAMETERS_T paramB;
  paramB.G_PTS = 1;
  // these variables dont matter for this test
  std::array<std::array<CONNECTORS, 15>, 15> lcmB;
  std::array<bool, 15> puvB;

  Decide decideB(pointsB.size(), pointsB, paramB, lcmB, puvB);

  EXPECT_EQ(decideB.Lic11(), false);
}

// Positive test case for LIC12(),
// Tests that LIC12 can pass when points are satisfied
// Expected value TRUE
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

// Negative test case for LIC12(),
// Tests that LIC12 can reject when numpoints is less than 3
// Expected value FALSE
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

// Negative test case for LIC12(),
// Test that LIC12 can find two points seperated by K_PTS points apart
// but do not have a greater length between them than LENGTH1
// also there are some point that has a distance less than LENGHT2
// Expected value FALSE
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

// Negative test case for LIC12(),
// Test that LIC12 can find two points seperated by K_PTS points apart
// and do have a greater length between them than LENGTH1
// but there are no point that has a distance less than LENGHT2
// Expected value FALSE
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
// Positive test case for LIC13(),
// Test whether LIC13 will return true if points satisfies the requirement
// Expected value TRUE
TEST(CMV, LIC13_POSITIVE) {
  // triangle {0,0},{0,100},{100,0} CANT fit in circle with radius 1
  // triangle {0,0},{0,1},{1,0} CAN fit in circle with radius 100
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0},   {0, 100},
                                    {0, 1}, {0, 0}, {100, 0}, {1, 0}};

  int numpoints = points.size();
  // create parameters container
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

// Negative test case for LIC13(),
// Test whether LIC13 will return false if points dissatisfies the requirement
// Expected value FALSE
TEST(CMV, LIC13_NEGATIVE) {
  // triangle {0,0},{0,10},{10,0} CAN fit in circle with radius 100
  // triangle {0,0},{0,1},{1,0} CAN fit in a circle with radius 100
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0},  {0, 10},
                                    {0, 1}, {0, 0}, {10, 0}, {1, 0}};

  int numpoints = points.size();
  // create parameters container
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

// Boundrary test case for LIC13(),
// Test whether LIC13 will return true if points is exactly on the circle
// Expected value TRUE
TEST(CMV, LIC13_BOUNDRARY) {
  // triangle {0,0},{0,100},{100,0} CANT fit in circle with radius 1
  // triangle {0,0},{0,1},{1,0} fits ON the boundrary of a circle wwith radius
  // 0.5 * sqrt(2)
  std::vector<COORDINATE> points = {{0, 0}, {0, 0}, {0, 0},   {0, 100},
                                    {0, 1}, {0, 0}, {100, 0}, {1, 0}};

  int numpoints = points.size();
  // create parameters container
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

// Positive test case for LIC14(),
// Test whether LIC14 will return true if area is within region
// Expected value TRUE
TEST(CMV, LIC14_POSITIVE) {
  std::vector<COORDINATE> points = {{0,0},{0,4},{3,3},{4,0},{8,0},{5,5}};
  // area=12,12
  // create parameters container
  PARAMETERS_T parameters;
  parameters.E_PTS = 1;
  parameters.F_PTS = 1;
  parameters.AREA1 = 7;
  parameters.AREA2 = 16;
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(points.size(), points, parameters, lcm, puv);

  EXPECT_EQ(decide.Lic14(), true);
}

// Negative test case for LIC14(),
// Test whether LIC14 will return false if area is beyond region
// Expected value FALSE
TEST(CMV, LIC14_NEGATIVE){
  std::vector<COORDINATE> points = { {0,0},{0,4},{4,4},{4,0},{1,0}};
  // area=2
  // create parameters container
  PARAMETERS_T parameters;
  parameters.E_PTS = 1;
  parameters.F_PTS = 1;
  parameters.AREA1= 6;
  parameters.AREA2= 16;
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;

  Decide decide(points.size(), points, parameters, lcm, puv);
  //Compare
  EXPECT_EQ(decide.Lic14(), false);
}

// Test that launch is true given some inputs that should fulfill lic requirements 0, 3 and 6.
TEST(LAUNCH, LAUNCH_POSITIVE) {

  std::vector<COORDINATE> points = {{0,0}, {100,100}, {0, 0}, {20, 0}, {0,20}, {0,0}, {50, 0}, {100, 100}};

  PARAMETERS_T parameters;
  parameters.LENGTH1 = 100;
  parameters.AREA1 = 9.5;
  parameters.DIST = 10;
  parameters.N_PTS = 3;

  std::array<std::array<CONNECTORS, 15>, 15> lcm = 
    {{
      {ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR ,ORR, ORR, ORR, ORR},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR ,ORR, ORR, ORR, ORR},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR, ORR ,ORR, ORR, ORR, ORR},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED}
    }};

  // Lic0, 3 and 6 need to be true.
  std::array<bool, 15> puv = {false};
  puv[0] = puv[3] = puv[6] = true;

  Decide decide(points.size(), points, parameters, lcm, puv);
  decide.decide();

  EXPECT_EQ(decide.CMV[0], true);
  EXPECT_EQ(decide.CMV[3], true);
  EXPECT_EQ(decide.CMV[6], true);

  EXPECT_EQ(decide.LAUNCH, true);
}

// Tests that launch is true if entire LCM is notused
TEST(LAUNCH, LAUNCH_POSITIVE2) {
  std::vector<COORDINATE> points = {{0,0}, {100,100}, {0, 0}, {20, 0}, {0,20}, {0,0}, {50, 0}, {100, 100}};

  PARAMETERS_T parameters;
  
  // A pum of only not used should always give a true launch
  std::array<std::array<CONNECTORS, 15>, 15> lcm = 
    {{
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED},
      {NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED}
    }};

  // Lic0, 3 and 6 need to be true.
  std::array<bool, 15> puv = {true};

  Decide decide(points.size(), points, parameters, lcm, puv);
  decide.decide();

  EXPECT_EQ(decide.LAUNCH, true);
}


// Test case that checks that the function sets launch when it requires all lics 
// to be true at the same time and they are
TEST(LAUNCH, LAUNCH_POSITIVE3) {
  
  std::vector<COORDINATE> points = {{1,2},{3,4}};
  // This lcm should mean every single LIC specified in PUV needs to be true
  std::array<std::array<CONNECTORS, 15>, 15> lcm = 
    {{
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
    }};      
 
  std::array<bool, 15> puv = {true};

  PARAMETERS_T parameters;

  Decide decide(points.size(), points, parameters, lcm, puv);
  
  for(int i = 0; i < 15; ++i) {
    decide.CMV[i]= true;
  }

  decide.Calc_PUM();
  decide.Calc_FUV();
  decide.Calc_LAUNCH();

  EXPECT_EQ(decide.LAUNCH, true);
}

// A really strict test case were every single lic needs to be true for 
// the launch to be true. In this case every single lic isnt true.
TEST(LAUNCH, LAUNCH_NEGATIVE) {

  std::vector<COORDINATE> points = {{0,0}, {100,100}, {0, 0}, {20, 0}, {0,20}, {0,0}, {50, 0}, {100, 100}};

  PARAMETERS_T parameters = {
      10,  // LENGTH1
      10,   // RADIUS1
      10,   // EPSILON
      10,  // AREA1: Set to a value that no triangle formed by the input points will exceed
      10,   // Q_PTS
      10,   // QUADS
      10,   // DIST
      10,   // N_PTS
      10,   // K_PTS
      10,   // A_PTS
      10,   // B_PTS
      10,   // C_PTS
      10,   // D_PTS
      1,   // E_PTS
      1,   // F_PTS
      3,   // G_PTS
      3,   // LENGTH2
      3,   // RADIUS2
      3    // AREA2
  };
  
  // This lcm should mean every single LIC specified in PUV needs to be true
  std::array<std::array<CONNECTORS, 15>, 15> lcm = 
    {{
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
      {ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD, ANDD},
    }};      
  // Lic0, 3 and 6 need to be true.
  std::array<bool, 15> puv = {true};

  Decide decide(points.size(), points, parameters, lcm, puv);
  decide.decide();

  EXPECT_EQ(decide.LAUNCH, false);
}

