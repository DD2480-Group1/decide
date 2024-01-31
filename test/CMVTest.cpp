#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "decide.h"

// basic test
TEST(BasicTest, BasicAssertions) {
  EXPECT_EQ(7 * 6, 42);
  EXPECT_EQ(1, 2);
}


TEST(CMV, LIC4_Negative) {
  std::vector<COORDINATE> points = {{0,0},{1,1},{2,2}};

  PARAMETERS_T parameters;
  parameters.Q_PTS = 3;
  parameters.QUADS = 1; // 0.1 and 5.1 >= 5
  

  std::array<std::array<CONNECTORS, 15>, 15> lcm;

  std::array<bool, 15> puv = {0};

  Decide decide2(points.size(), points, parameters, lcm, puv);

  // EXPECT_EQ(decide.Lic11(), false);
  EXPECT_EQ(decide.Lic4(), false);}

 TEST(CMV, LIC4_Positive) {


  std::vector<COORDINATE> points2 = {{0, 0}, {-1, 1}, {-2, 2}};

  PARAMETERS_T parameters;
  parameters.Q_PTS = 3;
  parameters.QUADS = 1; 

  std::array<std::array<CONNECTORS, 15>, 15> lcm2;

  std::array<bool, 15> puv2 = {0};

  Decide decide2(points2.size(), points2, parameters2, lcm2, puv2);

  EXPECT_EQ(decide2.Lic4(), true);
}
TEST(CMV, LIC9_Positive) {
  std::vector<COORDINATE> points = {{0,0},{0,1},{1,1},{1,0},{2,1}};

  PARAMETERS_T parameters;
  parameters.D_PTS = 1;
  parameters.C_PTS = 1;
  parameters.EPSILON = 2;

  std::array<std::array<CONNECTORS, 15>, 15> lcm;

  std::array<bool, 15> puv = {0};

  Decide decide2(points.size(), points, parameters, lcm, puv);

  // EXPECT_EQ(decide.Lic11(), false);
  EXPECT_EQ(decide.Lic9(), true);
}
  TEST(CMV, LIC9_Negative) {

  std::vector<COORDINATE> points2 = { {0,0},{0,1},{1,1},{1,0},{1,-1}};

  PARAMETERS_T parameters;
  parameters.D_PTS = 1;
  parameters.C_PTS = 1;
  parameters.EPSILON = 2;

  std::array<std::array<CONNECTORS, 15>, 15> lcm2;

  std::array<bool, 15> puv2 = {0};

  Decide decide2(points2.size(), points2, parameters2, lcm2, puv2);

  EXPECT_EQ(decide2.Lic9(), false);
}
TEST(CMV, LIC14_Positive) {
  std::vector<COORDINATE> points = {{0,0},{0,4},{3,3},{4,0},{8,0}};

  PARAMETERS_T parameters;
  parameters.E_PTS = 1;
  parameters.F_PTS = 1;
  parameters.AREA1= 8;
  parameters.AREA2= 16;
  std::array<std::array<CONNECTORS, 15>, 15> lcm;

  std::array<bool, 15> puv = {0};

  Decide decide2(points.size(), points, parameters, lcm, puv);

  // EXPECT_EQ(decide.Lic11(), false);
  EXPECT_EQ(decide.Lic14(), true);
}
TEST(CMV,LIC14_Negative){
  std::vector<COORDINATE> points2 = { {0,0},{0,4},{4,4},{4,0},{1,0}};

  PARAMETERS_T parameters;
  parameters.E_PTS = 1;
  parameters.F_PTS = 1;
  parameters.AREA1= 6;
  parameters.AREA2= 16;

  std::array<std::array<CONNECTORS, 15>, 15> lcm2;

  std::array<bool, 15> puv2 = {0};

  Decide decide2(points2.size(), points2, parameters2, lcm2, puv2);

  EXPECT_EQ(decide2.Lic14(), false);
}