#ifndef _COORDINATE_H
#define _COORDINATE_H

#include <sstream>

struct Coordinate {
  int r;
  int c;

  Coordinate(int r_in, int c_in);

  bool operator==(const Coordinate &p) const;

  friend std::ostream& operator<<(std::ostream& os, const Coordinate &c);
};

std::ostream& operator<<(std::ostream& os, const Coordinate &c);

struct CoordinateHash {
  std::size_t operator()(const Coordinate& c) const;
};

#endif
