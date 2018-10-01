#include "Geo/Coordinate.hpp"

namespace Geo {

Coordinate::Coordinate()
  : mLatitude(0.)
  , mLongitude(0.)
{}

Coordinate::Coordinate(double latitude, double longitude)
{
  mLatitude = latitude;
  mLongitude = longitude;
}

Coordinate::Coordinate(const Coordinate &other)
  : mLatitude(other.mLatitude),
    mLongitude(other.mLongitude)
{}

Coordinate &Coordinate::operator=(const Coordinate &other)
{
  if (this == &other)
    return *this;

  mLatitude = other.mLatitude;
  mLongitude = other.mLongitude;

  return (*this);
}

Coordinate::~Coordinate()
{}

bool Coordinate::operator==(const Coordinate &other) const
{
  return ((mLatitude == other.mLatitude) && (mLongitude == other.mLongitude));
}

bool Coordinate::operator!=(const Coordinate &other) const
{
  return !operator==(other);
}

double Coordinate::latitude() const
{
  return mLatitude;
}

void Coordinate::setLatitude(double latitude)
{
  mLatitude = latitude;
}

double Coordinate::longitude() const
{
  return mLongitude;
}

void Coordinate::setLongitude(double longitude)
{
  mLongitude = longitude;
}

}
