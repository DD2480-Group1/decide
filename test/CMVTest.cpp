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

// Test if lic3 correctly sets CMV[3] when there
// exists a triangle with area == AREA1
TEST(CMV, LIC3_BOUNDRARY) {
    // triangle with area 0.5
    std::vector<COORDINATE> points = {
        {0,0}, {0,1}, {1,0}
    };

    int numpoints = points.size();

    PARAMETERS_T parameters;
    parameters.AREA1 = 0.5;
    
    // these variables dont matter for this test
    std::array<std::array<CONNECTORS, 15>, 15> lcm;
    std::array<bool, 15> puv;
    
    Decide d(numpoints, points, parameters, lcm, puv);
    
    EXPECT_EQ(d.Lic3(), false);
}

TEST(CMV, LIC8_POSITIVE) {
    // triangle {0,0},{0,100},{100,0} cant fit in circle with radius 1  
    std::vector<COORDINATE> points = {
        {0,0}, {0,0}, {0,0}, {0,100}, {0,0}, {0,0}, {100,0}
    };

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
    std::vector<COORDINATE> points = {
        {0,0}, {0,0}, {0,0}, {0,1}, {0,0}, {0,0}, {1,0}
    };

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
    std::vector<COORDINATE> points = {
        {0,0}, {0,0}, {0,0}, {0,1}, {0,0}, {0,0}, {1,0}
    };

    int numpoints = points.size();

    PARAMETERS_T parameters;
    parameters.A_PTS = 2;
    parameters.B_PTS = 2;
    parameters.RADIUS1 = 0.5*sqrt(2.0);

    std::array<std::array<CONNECTORS, 15>, 15> lcm;
    std::array<bool, 15> puv;
 
    Decide d(numpoints, points, parameters, lcm, puv);
    
    // the triangle should fit on the circle
    EXPECT_EQ(d.Lic8(), false);
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

TEST(CMV, LIC13_POSITIVE) {
    // triangle {0,0},{0,100},{100,0} CANT fit in circle with radius 1  
    // triangle {0,0},{0,1},{1,0} CAN fit in circle with radius 100  
    std::vector<COORDINATE> points = {
        {0,0}, {0,0}, {0,0}, {0,100}, {0,1}, {0,0}, {100,0}, {1,0}
    };

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
    std::vector<COORDINATE> points = {
        {0,0}, {0,0}, {0,0}, {0,10}, {0,1}, {0,0}, {10,0}, {1,0}
    };

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

