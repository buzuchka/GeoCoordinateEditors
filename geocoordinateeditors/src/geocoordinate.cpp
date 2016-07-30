#include "geocoordinate.h"

GeoCoordinate::GeoCoordinate()
    : m_latitude(0.),
      m_longitude(0.)
{}

GeoCoordinate::GeoCoordinate(double latitude, double longitude)
{
    m_latitude = latitude;
    m_longitude = longitude;
}

GeoCoordinate::GeoCoordinate(const GeoCoordinate &other)
    : m_latitude(other.m_latitude),
      m_longitude(other.m_longitude)
{}

GeoCoordinate &GeoCoordinate::operator=(const GeoCoordinate &other)
{
    if (this == &other)
        return *this;

    m_latitude = other.m_latitude;
    m_longitude = other.m_longitude;

    return (*this);
}

GeoCoordinate::~GeoCoordinate()
{}

bool GeoCoordinate::operator==(const GeoCoordinate &other) const
{
    return ((m_latitude == other.m_latitude) && (m_longitude == other.m_longitude));
}

bool GeoCoordinate::operator!=(const GeoCoordinate &other) const
{
    return !operator==(other);
}

double GeoCoordinate::latitude() const
{
    return m_latitude;
}

void GeoCoordinate::setLatitude(double latitude)
{
    m_latitude = latitude;
}

double GeoCoordinate::longitude() const
{
    return m_longitude;
}

void GeoCoordinate::setLongitude(double longitude)
{
    m_longitude = longitude;
}
