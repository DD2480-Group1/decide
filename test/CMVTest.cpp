#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "decide.h"

// basic test
TEST(BasicTest, BasicAssertions) {
  EXPECT_EQ(7 * 6, 42);
  EXPECT_EQ(1, 2);
}

TEST(CMV, LIC11) {
  std::vector<COORDINATE> points = {
      {0, 0},   {1, 1},   {2, 2},   {3, 3},   {4, 4},
      {5, 5},   {6, 6},   {7, 7},   {8, 8},   {-1, -2},
      {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14},
  };

  PARAMETERS_T parameters = {
      0,  // LENGTH1
      0,  // RADIUS1
      0,  // EPSILON
      0,  // AREA1
      0,  // Q_PTS
      0,  // QUADS
      0,  // DIST
      0,  // N_PTS
      0,  // K_PTS
      0,  // A_PTS
      0,  // B_PTS
      0,  // C_PTS
      0,  // D_PTS
      0,  // E_PTS
      0,  // F_PTS
      1,  // G_PTS
      0,  // LENGTH2
      0,  // RADIUS2
      0,  // AREA2
  };

  std::array<std::array<CONNECTORS, 15>, 15> lcm;

  std::array<bool, 15> puv = {0};

  Decide decide(points.size(), points, parameters, lcm, puv);

  // EXPECT_EQ(decide.Lic11(), false);
  EXPECT_EQ(decide.Lic11(), true);

  std::vector<COORDINATE> points2 = {
      {0, 0}, {1, 1}, {2, 2},   {3, 3},   {4, 4},   {5, 5},   {6, 6},   {7, 7},
      {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14},
  };

  PARAMETERS_T parameters2 = {
      0,  // LENGTH1
      0,  // RADIUS1
      0,  // EPSILON
      0,  // AREA1
      0,  // Q_PTS
      0,  // QUADS
      0,  // DIST
      0,  // N_PTS
      0,  // K_PTS
      0,  // A_PTS
      0,  // B_PTS
      0,  // C_PTS
      0,  // D_PTS
      0,  // E_PTS
      0,  // F_PTS
      1,  // G_PTS
      0,  // LENGTH2
      0,  // RADIUS2
      0,  // AREA2
  };

  std::array<std::array<CONNECTORS, 15>, 15> lcm2;

  std::array<bool, 15> puv2 = {0};

  Decide decide2(points2.size(), points2, parameters2, lcm2, puv2);

  EXPECT_EQ(decide2.Lic11(), false);
}


//Test case for Lic0() returning true

TEST(CMV, lic0Pos){
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
TEST(CMV, lic0Neg) {
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



// Test case for Lic5() returning true

TEST(CMV, lic5Pos) {
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
TEST(CMV, lic5Neg) {

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



// Test case for Decide::Lic10() returning true when at least one triangle has area greater than AREA1
TEST(CMV, lic10Pos) {
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
TEST(CMV, lic10Neg) {
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
