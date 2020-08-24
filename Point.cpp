//
// Created by shlomo on 14/01/2020.
//

#include "Point.h"
ostream& operator<<(ostream& os, Point const& p)
{
  os<<"Point("<<p.getX()<<","<<p.getY()<<")";
  return os;
}
int Point:: getX() const {
  return x;
}
void Point:: setX(int xp) {
  Point::x = xp;
}
int Point:: getY() const {
  return y;
}
void Point:: setY(int yp) {
  Point::y = yp;
}
Point::Point(int x1, int y1) {
  this->x=x1;
  this->y=y1;
}