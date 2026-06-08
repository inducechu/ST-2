// Copyright 2025 UNN-CS Team
#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "task.h"

const double PI_CONST = 3.14159265358979323846;
const double DELTA_EPS = 1e-10;

TEST(CircleMetricsSuite, CheckConstructorAndGetters) {
  Circle roundObj(7.2);
  EXPECT_DOUBLE_EQ(roundObj.getRadius(), 7.2);
  EXPECT_DOUBLE_EQ(roundObj.getFerence(), PI_CONST * 2.0 * 7.2);
  EXPECT_DOUBLE_EQ(roundObj.getArea(), PI_CONST * 7.2 * 7.2);
}

TEST(CircleMetricsSuite, UpdatePerimeterAndCheckRadius) {
  Circle roundObj(5.5);
  double newLength = 28.4;
  roundObj.setFerence(newLength);
  double expectedRad = newLength / (PI_CONST * 2.0);
  EXPECT_DOUBLE_EQ(roundObj.getFerence(), newLength);
  EXPECT_DOUBLE_EQ(roundObj.getRadius(), expectedRad);
  EXPECT_DOUBLE_EQ(roundObj.getArea(), PI_CONST * expectedRad * expectedRad);
}

TEST(CircleMetricsSuite, UpdateAreaAndCheckInvariants) {
  Circle roundObj(1.8);
  double newSpace = 113.5;
  roundObj.setArea(newSpace);
  double expectedRad = std::sqrt(newSpace / PI_CONST);
  EXPECT_NEAR(roundObj.getArea(), newSpace, DELTA_EPS);
  EXPECT_NEAR(roundObj.getRadius(), expectedRad, DELTA_EPS);
  EXPECT_NEAR(roundObj.getFerence(), PI_CONST * 2.0 * expectedRad, DELTA_EPS);
}

TEST(CircleBoundarySuite, VerifyNullDimensions) {
  Circle roundObj(0.0);
  EXPECT_DOUBLE_EQ(roundObj.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(roundObj.getFerence(), 0.0);
  EXPECT_DOUBLE_EQ(roundObj.getArea(), 0.0);
}

TEST(CircleBoundarySuite, VerifyMacroDimensions) {
  Circle roundObj(3e6);
  EXPECT_DOUBLE_EQ(roundObj.getFerence(), PI_CONST * 2.0 * 3e6);
  EXPECT_DOUBLE_EQ(roundObj.getArea(), PI_CONST * 9e12);
}

TEST(CircleBoundarySuite, VerifyMicroDimensions) {
  Circle roundObj(2e-9);
  EXPECT_GT(roundObj.getRadius(), 0.0);
  EXPECT_GT(roundObj.getFerence(), 0.0);
  EXPECT_GT(roundObj.getArea(), 0.0);
}

TEST(CircleBoundarySuite, ResetPerimeterToZero) {
  Circle roundObj(14.7);
  roundObj.setFerence(0.0);
  EXPECT_DOUBLE_EQ(roundObj.getFerence(), 0.0);
  EXPECT_DOUBLE_EQ(roundObj.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(roundObj.getArea(), 0.0);
}

TEST(CircleValidationSuite, ExceptionOnNegativeRadius) {
  Circle roundObj(8.1);
  EXPECT_THROW(roundObj.setRadius(-6.4), std::invalid_argument);
}

TEST(CircleValidationSuite, ExceptionOnNegativePerimeter) {
  Circle roundObj(4.3);
  EXPECT_THROW(roundObj.setFerence(-12.8), std::invalid_argument);
}

TEST(CircleValidationSuite, ExceptionOnNegativeArea) {
  Circle roundObj(10.0);
  EXPECT_THROW(roundObj.setArea(-99.9), std::invalid_argument);
}

TEST(CircleWorkflowSuite, MultiStepRecalculation) {
  Circle roundObj(6.6);
  double temporaryLength = 54.2;
  roundObj.setFerence(temporaryLength);

  double nextRad = temporaryLength / (PI_CONST * 2.0);
  double nextArea = PI_CONST * nextRad * nextRad;

  EXPECT_NEAR(roundObj.getRadius(), nextRad, DELTA_EPS);
  EXPECT_NEAR(roundObj.getArea(), nextArea, DELTA_EPS);
}

TEST(CircleWorkflowSuite, IdempotencyOfSetters) {
  Circle roundObj(11.4);
  double baseRadius = roundObj.getRadius();
  double baseFerence = roundObj.getFerence();
  double baseArea = roundObj.getArea();

  roundObj.setRadius(baseRadius);
  EXPECT_DOUBLE_EQ(roundObj.getFerence(), baseFerence);
  EXPECT_DOUBLE_EQ(roundObj.getArea(), baseArea);

  roundObj.setFerence(baseFerence);
  EXPECT_DOUBLE_EQ(roundObj.getRadius(), baseRadius);
  EXPECT_DOUBLE_EQ(roundObj.getArea(), baseArea);
}

TEST(EarthGapTaskSuite, TargetGapSignCheck) {
  double gapResult = calculateEarthGap();
  EXPECT_GT(gapResult, 0.0);
}

TEST(EarthGapTaskSuite, TargetGapValueCheck) {
  double gapResult = calculateEarthGap();
  double expectedGapValue = 1.0 / (PI_CONST * 2.0);
  EXPECT_NEAR(gapResult, expectedGapValue, DELTA_EPS);
}

TEST(PoolCostTaskSuite, PoolTotalCostValidation) {
  double finalCost = calculatePoolCost();
  EXPECT_GT(finalCost, 0.0);

  Circle inside(3.0);
  Circle outside(4.0);
  double expectedPathArea = outside.getArea() - inside.getArea();
  double expectedCost =
      expectedPathArea * 1000.0 + outside.getFerence() * 2000.0;
  EXPECT_DOUBLE_EQ(finalCost, expectedCost);
}
