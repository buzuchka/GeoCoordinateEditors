#ifndef GEOCOORDINATEEDITORS_LONGITUDEEDIT_HPP
#define GEOCOORDINATEEDITORS_LONGITUDEEDIT_HPP

#include <GEOCOORDINATEEDITORS_EXPORT.h>

#include <DegreeCoordinateEdit.hpp>

namespace Geo {

class GEOCOORDINATEEDITORS_EXPORT LongitudeEdit : public DegreeCoordinateEdit
{
  Q_OBJECT
public:
  explicit LongitudeEdit(QWidget *parent = 0);
};

}

#endif
