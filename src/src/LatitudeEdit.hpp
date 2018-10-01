#ifndef GEOCOORDINATEEDITORS_LATITUDEEDIT_HPP
#define GEOCOORDINATEEDITORS_LATITUDEEDIT_HPP

#include <GEOCOORDINATEEDITORS_EXPORT.h>

#include <DegreeCoordinateEdit.hpp>

namespace Geo {

class GEOCOORDINATEEDITORS_EXPORT LatitudeEdit : public DegreeCoordinateEdit
{
  Q_OBJECT
public:
  explicit LatitudeEdit(QWidget *parent = 0);
};

}

#endif
