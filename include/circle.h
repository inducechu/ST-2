// Copyright 2022 UNN-CS
#ifndef GEOMETRY_CIRCLE_CLASS_H_
#define GEOMETRY_CIRCLE_CLASS_H_

#include <stdexcept>

class Circle {
private:
  double radius;
  double ference;
  double area;

public:
  explicit Circle(double radius_val);
  void setRadius(double radius_val);
  void setFerence(double length_val);
  void setArea(double space_val);
  double getRadius() const;
  double getFerence() const;
  double getArea() const;
};

#endif // GEOMETRY_CIRCLE_CLASS_H_
