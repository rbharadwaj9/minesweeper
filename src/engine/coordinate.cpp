#include <functional>

#include "coordinate.h"

Coordinate::Coordinate(int r_in, int c_in) : r(r_in), c(c_in) {}

bool Coordinate::operator==(const Coordinate &p) const {
  return r == p.r && c == p.c;
}

std::ostream& operator<<(std::ostream& os, const Coordinate &c) {
  os << "(" << c.r << "," << c.c << ")";
  return os;
}

std::size_t CoordinateHash::operator()(const Coordinate& c) const
{
  std::string rval = "r";
  rval += c.r;
  rval += "c";
  rval += c.c;
  return std::hash<std::string>{}(rval);
}
