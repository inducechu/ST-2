// Copyright 2022 UNN-CS
#define _USE_MATH_DEFINES
#include "circle.h"
#include <cmath>
#include <stdexcept>

Circle::Circle(double radius_val) { setRadius(radius_val); }

void Circle::setRadius(double radius_val) {
  if (radius_val < 0.0) {
    throw std::invalid_argument("Radius: negative value prohibited");
  }
  radius = radius_val;
  ference = M_PI * 2.0 * radius;
  area = M_PI * radius * radius;
}

void Circle::setFerence(double length_val) {
  if (length_val < 0.0) {
    throw std::invalid_argument("Circumference: negative value prohibited");
  }
  ference = length_val;
  radius = ference / (M_PI * 2.0);
  area = M_PI * radius * radius;
}

void Circle::setArea(double space_val) {
  if (space_val < 0.0) {
    throw std::invalid_argument("Area: negative value prohibited");
  }
  area = space_val;
  radius = std::sqrt(area / M_PI);
  ference = M_PI * 2.0 * radius;
}

double Circle::getRadius() const { return radius; }

double Circle::getFerence() const { return ference; }

double Circle::getArea() const { return area; }
