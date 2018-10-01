#include "LatitudeEdit.hpp"

namespace Geo {

LatitudeEdit::LatitudeEdit(QWidget *parent)
  : DegreeCoordinateEdit(parent)
{
  setMaxDegrees(90);
  setDesignationHemisphereType(tr("с.ш."), tr("ю.ш."), Geo::Suffix);
}

}
