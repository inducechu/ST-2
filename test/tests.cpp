// Copyright 2025 UNN-CS Team
#include "circle.h"
#include "task.h"
#include <cmath>
#include <gtest/gtest.h>

const double PI_CONST = 3.14159265358979323846;
const double DELTA_EPS = 1e-10;

TEST(GeometryCircle, InitAndReadMetrics) {
  Circle item(4.5);
  EXPECT_DOUBLE_EQ(item.getRadius(), 4.5);
  EXPECT_DOUBLE_EQ(item.getFerence(), PI_CONST * 2.0 * 4.5);
  EXPECT_DOUBLE_EQ(item.getArea(), PI_CONST * 4.5 * 4.5);
}

TEST(GeometryCircle, ChangeFerenceCorrectly) {
  Circle item(2.0);
  double currentLength = 15.0;
  item.setFerence(currentLength);
  double expectedRadius = currentLength / (PI_CONST * 2.0);
  EXPECT_DOUBLE_EQ(item.getFerence(), currentLength);
  EXPECT_DOUBLE_EQ(item.getRadius(), expectedRadius);
  EXPECT_DOUBLE_EQ(item.getArea(), PI_CONST * expectedRadius * expectedRadius);
}

TEST(GeometryCircle, ChangeAreaCorrectly) {
  Circle item(3.0);
  double currentSpace = 75.0;
  item.setArea(currentSpace);
  double expectedRadius = std::sqrt(currentSpace / PI_CONST);
  EXPECT_NEAR(item.getArea(), currentSpace, DELTA_EPS);
  EXPECT_NEAR(item.getRadius(), expectedRadius, DELTA_EPS);
  EXPECT_NEAR(item.getFerence(), PI_CONST * 2.0 * expectedRadius, DELTA_EPS);
}

TEST(GeometryCircle, ProcessZeroValues) {
  Circle item(0.0);
  EXPECT_DOUBLE_EQ(item.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(item.getFerence(), 0.0);
  EXPECT_DOUBLE_EQ(item.getArea(), 0.0);
}

TEST(GeometryCircle, HandleHugeValues) {
  Circle item(5e8);
  EXPECT_DOUBLE_EQ(item.getFerence(), PI_CONST * 2.0 * 5e8);
  EXPECT_DOUBLE_EQ(item.getArea(), PI_CONST * 2.5e17);
}

TEST(GeometryCircle, ResetFerenceToZero) {
  Circle item(8.2);
  item.setFerence(0.0);
  EXPECT_DOUBLE_EQ(item.getFerence(), 0.0);
  EXPECT_DOUBLE_EQ(item.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(item.getArea(), 0.0);
}

TEST(GeometryCircle, ResetAreaToZero) {
  Circle item(12.4);
  item.setArea(0.0);
  EXPECT_DOUBLE_EQ(item.getArea(), 0.0);
  EXPECT_DOUBLE_EQ(item.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(item.getFerence(), 0.0);
}

TEST(GeometryCircle, ThrowsOnNegativeRadius) {
  Circle item(2.5);
  EXPECT_THROW(item.setRadius(-1.5), std::invalid_argument);
}

TEST(GeometryCircle, ThrowsOnNegativeFerence) {
  Circle item(2.5);
  EXPECT_THROW(item.setFerence(-25.0), std::invalid_argument);
}

TEST(GeometryCircle, ThrowsOnNegativeArea) {
  Circle item(2.5);
  EXPECT_THROW(item.setArea(-35.5), std::invalid_argument);
}

TEST(GeometryCircle, MaintainMathInvariants) {
  Circle item(9.0);
  EXPECT_DOUBLE_EQ(item.getFerence(), PI_CONST * 2.0 * item.getRadius());
  EXPECT_DOUBLE_EQ(item.getArea(),
                   PI_CONST * item.getRadius() * item.getRadius());
}

TEST(PlanetGap, VerifyPositiveGap) {
  double calculatedGap = calculateEarthGap();
  EXPECT_GT(calculatedGap, 0.0);
}

TEST(PlanetGap, VerifyGapPrecision) {
  double calculatedGap = calculateEarthGap();
  double targetGap = 1.0 / (PI_CONST * 2.0);
  EXPECT_NEAR(calculatedGap, targetGap, DELTA_EPS);
}

TEST(SwimmingPool, VerifyPositiveTotalCost) {
  double financialCost = calculatePoolCost();
  EXPECT_GT(financialCost, 0.0);
}

TEST(GeometryCircle, CycleRecalculationWorkflow) {
  Circle item(1.5);
  double sampleFerence = 42.0;
  item.setFerence(sampleFerence);

  double targetRad = sampleFerence / (PI_CONST * 2.0);
  double targetArea = PI_CONST * targetRad * targetRad;

  EXPECT_NEAR(item.getRadius(), targetRad, DELTA_EPS);
  EXPECT_NEAR(item.getArea(), targetArea, DELTA_EPS);
}

TEST(GeometryCircle, DeepConsistencyValidation) {
  Circle item(3.5);
  item.setRadius(5.5);
  double rOld = item.getRadius();
  double fOld = item.getFerence();
  double aOld = item.getArea();

  item.setFerence(fOld);
  EXPECT_NEAR(item.getRadius(), rOld, DELTA_EPS);
  EXPECT_NEAR(item.getArea(), aOld, DELTA_EPS);

  item.setArea(aOld);
  EXPECT_NEAR(item.getRadius(), rOld, DELTA_EPS);
  EXPECT_NEAR(item.getFerence(), fOld, DELTA_EPS);
}

TEST(GeometryCircle, IdentityRecalculationTests) {
  Circle item(6.2);
  double rState = item.getRadius();
  double fState = item.getFerence();
  double aState = item.getArea();

  item.setRadius(rState);
  EXPECT_DOUBLE_EQ(item.getFerence(), fState);
  EXPECT_DOUBLE_EQ(item.getArea(), aState);

  item.setFerence(fState);
  EXPECT_DOUBLE_EQ(item.getRadius(), rState);
  EXPECT_DOUBLE_EQ(item.getArea(), aState);

  item.setArea(aState);
  EXPECT_DOUBLE_EQ(item.getRadius(), rState);
  EXPECT_DOUBLE_EQ(item.getFerence(), fState);
}

TEST(GeometryCircle, MicroscopicRadiusValidation) {
  Circle item(1e-12);
  EXPECT_GT(item.getRadius(), 0.0);
  EXPECT_GT(item.getFerence(), 0.0);
  EXPECT_GT(item.getArea(), 0.0);
}

TEST(SwimmingPool, VerifyCostCalculationFormula) {
  Circle inPool(3.0);
  Circle outPool(4.0);
  double targetPathArea = outPool.getArea() - inPool.getArea();
  double targetCost = targetPathArea * 1000.0 + outPool.getFerence() * 2000.0;
  EXPECT_DOUBLE_EQ(calculatePoolCost(), targetCost);
}

TEST(SwimmingPool, CheckPathAreaSigns) {
  Circle inPool(3.0);
  Circle outPool(4.0);
  EXPECT_GT(outPool.getArea() - inPool.getArea(), 0.0);
}

TEST(SwimmingPool, CheckFenceBoundSigns) {
  Circle outPool(4.0);
  EXPECT_GT(outPool.getFerence(), 0.0);
}
