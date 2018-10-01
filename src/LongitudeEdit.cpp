#include "LongitudeEdit.hpp"

namespace Geo {

LongitudeEdit::LongitudeEdit(QWidget *parent)
  : DegreeCoordinateEdit(parent)
{
  setMaxDegrees(180);
  setDesignationHemisphereType(tr("в.д."), tr("з.д."), Geo::Suffix);
}

}
