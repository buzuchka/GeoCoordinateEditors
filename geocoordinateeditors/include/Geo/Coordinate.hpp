#ifndef GEOCOORDINATEEDITORS_COORDINATE_HPP
#define GEOCOORDINATEEDITORS_COORDINATE_HPP

#include <geocoordinateeditors_export.h>

#include <vector>

namespace Geo {

/*!
 * \brief Простой класс географической координаты.
 */
class GEOCOORDINATEEDITORS_EXPORT Coordinate
{
public:
  Coordinate();
  Coordinate(double latitude, double longitude);
  Coordinate(const Coordinate &other);
  ~Coordinate();

  Coordinate &operator=(const Coordinate &other);

  bool operator==(const Coordinate &other) const;
  inline bool operator!=(const Coordinate &other) const;

  void setLatitude(double latitude);
  double latitude() const;

  void setLongitude(double longitude);
  double longitude() const;

private:
  double mLatitude;
  double mLongitude;
};

typedef std::vector<Coordinate> CoordinateVector;

}

#endif
