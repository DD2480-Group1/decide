#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "decide.h"

// basic test
TEST(BasicTest, BasicAssertions) {
  EXPECT_EQ(7 * 6, 42);
  EXPECT_EQ(1, 2);
}

// Tests that LIC2 can calculate angle
// that is greater than PI + EPSILON
TEST(CMV, LIC2_POSITIVE) {
    // points for angle
    std::vector<COORDINATE> points = {
        {0,1}, {1,0}, {1,2}
    };

    int numpoints = points.size();

    // create parameters container
    PARAMETERS_T parameters;
    parameters.EPSILON = 0.1;
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
  std::vector<COORDINATE> points = {
      {0,0}, {0,0}, {1,2}
  };

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

// Test that LIC7 can find two points seperated by K_PTS points apart
// and have a greater length between them than LENGTH1
TEST(CMV, LIC7_POSITIVE) {
  std::vector<COORDINATE> points = {
      {0,1}, {0,2}, {1,0}, {0,1}, {0,4}
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
  
  EXPECT_EQ(decide.Lic7(), true);
}

// Test that LIC7 can find two points seperated by K_PTS points apart
// but do not have a greater length between them than LENGTH1
TEST(CMV, LIC7_NEGATIVE_LENGHT1) {
  std::vector<COORDINATE> points = {
      {0,1}, {0,1}, {1,0}, {0,1},
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
  std::vector<COORDINATE> points = {
      {1,1}, {2,2}
  };

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  // dummy variables
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;
  
  Decide decide(numpoints, points, parameters, lcm, puv);
  
  EXPECT_EQ(decide.Lic7(), false);
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

TEST(CMV, LIC12_POSITIVE) {
  std::vector<COORDINATE> points = {
      {1,1}, {2,2}, {0,1}, {2,3}, {0,1}, {5,1}, {5,3}, {1,0}
  };

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  parameters.K_PTS = 2;
  parameters.LENGTH1 = 4.8; // 0.1 and 5.1 >= 5
  parameters.LENGTH2 = 1.6; // 0.1 and 1.0 <= 1.5
  // dummy parameters
  std::array<std::array<CONNECTORS, 15>, 15> lcm;
  std::array<bool, 15> puv;
  
  Decide decide(numpoints, points, parameters, lcm, puv);
  
  EXPECT_EQ(decide.Lic12(), true);
}

// Tests that LIC12 can reject when numpoints is less than 3
TEST(CMV, LIC12_NEGATIVE_NUMPOINTS) {
    std::vector<COORDINATE> points = {
      {1,1}, {2,2}
  };

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
  std::vector<COORDINATE> points = {
      {1,1}, {2,2}, {0,1}, {2,3}, {1,4}, {5,1}, {5,3}, {1,0}
  };

  int numpoints = points.size();

  // create parameters container
  PARAMETERS_T parameters;
  parameters.K_PTS = 2;
  parameters.LENGTH1 = 5; // should be equal and fail
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
  std::vector<COORDINATE> points = {
      {1,1}, {2,2}, {0,1}, {2,3}, {1,4}, {5,1}, {5,3}, {1,0}
  };

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