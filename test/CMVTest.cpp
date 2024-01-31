#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "decide.h"

// basic test
TEST(BasicTest, BasicAssertions) {
  EXPECT_EQ(7 * 6, 42);
  EXPECT_EQ(1, 2);
}

// Tests that lic3 can identify a triangle
// that is greater than PARAMETERS.AREA1
TEST(CMV, LIC3_POSITIVE) {
    // triangle with area 0.5
    std::vector<COORDINATE> points = {
        {0,0}, {0,1}, {1,0}
    };

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
    std::vector<COORDINATE> points = {
        {0,0}, {0,1}, {1,0}
    };

    int numpoints = points.size();

    PARAMETERS_T parameters;
    parameters.AREA1 = 0.6;
    
    // these variables dont matter for this test
    std::array<std::array<CONNECTORS, 15>, 15> lcm;
    std::array<bool, 15> puv;
    
    Decide d(numpoints, points, parameters, lcm, puv);
    
    EXPECT_EQ(d.Lic3(), false);
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

