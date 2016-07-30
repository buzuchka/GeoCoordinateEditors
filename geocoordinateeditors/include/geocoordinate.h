#ifndef GEOCOORDINATE_H
#define GEOCOORDINATE_H

class GeoCoordinate
{
public:
    GeoCoordinate();
    GeoCoordinate(double latitude, double longitude);
    GeoCoordinate(const GeoCoordinate &other);
    ~GeoCoordinate();

    GeoCoordinate &operator=(const GeoCoordinate &other);

    bool operator==(const GeoCoordinate &other) const;
    inline bool operator!=(const GeoCoordinate &other) const;

    void setLatitude(double latitude);
    double latitude() const;

    void setLongitude(double longitude);
    double longitude() const;

private:
    double m_latitude;
    double m_longitude;
};

#endif
