
#ifndef EX4_5__POINT_H_
#define EX4_5__POINT_H_
#include <iostream>
using namespace std;
class Point{
  int x,y;
 public:
  Point(){};
  Point(int,int);
  int getX() const;
  void setX(int x);
  int getY() const;
  void setY(int y);
  bool operator==(const Point &a) const {
    return(x==a.getX()&&y==a.getY());
  }
  bool operator<(const Point &a) const {
    return ((x+y)<(a.getX()+a.getY()));
  }
  friend ostream& operator<<(std::ostream& os, Point const& p);
};
namespace std {
// hash function allow us later to use point inside a hash map
template <>
struct hash<Point>
{
  std::size_t operator()(const Point& p) const
  {
    using std::size_t;
    using std::hash;
    using std::string;

    // Compute individual hash values for first,
    // second and third and combine them using XOR
    // and bit shifting:

    return ((hash<int>()(p.getX())
        ^ (hash<int>()(p.getY()) << 1)) >> 1);
  }
};
}
#endif //EX4_5__POINT_H_
