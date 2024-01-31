#ifndef CMVTEST_H
#define CMVTEST_H

#include "gtest/gtest.h"

#ifndef FRIEND_TEST_SUITE_CMV
#define FRIEND_TEST_SUITE_CMV() \
  FRIEND_TEST(CMV, LIC0);       \
  FRIEND_TEST(CMV, LIC1);       \
  FRIEND_TEST(CMV, LIC2);       \
  FRIEND_TEST(CMV, LIC3);       \
  FRIEND_TEST(CMV, LIC4);       \
  FRIEND_TEST(CMV, LIC5);       \
  FRIEND_TEST(CMV, LIC6);       \
  FRIEND_TEST(CMV, LIC7);       \
  FRIEND_TEST(CMV, LIC8);       \
  FRIEND_TEST(CMV, LIC9);       \
  FRIEND_TEST(CMV, LIC10);      \
  FRIEND_TEST(CMV, LIC11);      \
  FRIEND_TEST(CMV, LIC12);      \
  FRIEND_TEST(CMV, LIC13);      \
  FRIEND_TEST(CMV, LIC14);
#endif

#endif